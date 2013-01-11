#include <uv.h>
#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // strlen
#include <assert.h>
#include "dbuf.h"
#include "http_parser.h"

// XXX: We do not support chunked encoding yet.

struct Connection;

static void on_close_cb(uv_handle_t *handle);
static void handle_http_request(Connection *conn);


/*
 * Connection -> start_read
 *
 * we have one buffer per connection. this is stored in the connection object.
 * alloc_buffer returns this buffer. there is an underlying DBuf object, which
 * will be resized on demand. 
 *
 * alloc_buffer returns a 
 * Read -> parse 
 */

static uv_loop_t *loop;

struct Connection
{
  uv_tcp_t client; // NOTE: This HAS to be the first field!!!

  DBuf read_buffer;
  bool read_clear;

  HTTP::BytePos parse_offset; 
  bool in_body;

  HTTP::Parser parser;
  HTTP::Request req;
 
  Connection(size_t read_buf_capa) : read_buffer(read_buf_capa),
                                     read_clear(true), parse_offset(0), in_body(false) { }
};

struct write_req_t {
  uv_write_t req;
  uv_buf_t buf;
  Connection *conn;
  DBuf out; // XXX: use OutputBuffer instead. no need to dyn realloc

  write_req_t() : out(4096) {}
};

/*
 * We have one dynamically sized read_buffer per Connection (DBuf).  Usually
 * this buffer is large enough that it will never get expanded.
 *
 * We give out a pointer here into this read_buffer with enough space to hold
 * suggested_size bytes as uv_buf_t.
 *
 * Note that the uv_buf_t MUST not have to be freed, as it is just a pointer
 * into the read_buffer which itself gets "freed" when the connection closes.
 *
 * As we cannot be sure that suggested_size bytes will be actually used by
 * libuv, and as for HTTP parsing to work we need a continous buffer, we cannot
 * increase the size in alloc_read_buffer(). We have to wait for on_read_cb()
 * to get called. There we know the actual size. 
 *
 * Assumption: on_read_cb is always called after each alloc_read_buffer call.
 * We ensure this by setting read_clear = false and checking for it in
 * alloc_read_buffer again. on_read_cb reset it to true.
 */
static uv_buf_t
alloc_read_buffer(uv_handle_t *handle, size_t suggested_size)
{
  Connection *conn = (Connection*) handle;
  assert(conn->read_clear); // Ensure that the last buffer has been read by on_read_cb.

  conn->read_clear = false;
  conn->read_buffer.reserve_more(suggested_size); 
  
  return uv_buf_init(conn->read_buffer.end_ptr(), suggested_size);
}

static void
on_write_done_cb(uv_write_t *req, int status) {
  write_req_t *wr = (write_req_t*) req;
  Connection *conn = (Connection*) wr->conn;
  delete wr;

  if (!conn->req.is_keep_alive()) {
    uv_close((uv_handle_t*)conn, on_close_cb);
  }
}

static void
on_close_cb(uv_handle_t *handle)
{
  Connection *conn = (Connection*) handle;
  delete conn;
}

static void
handle_http_error(Connection *conn) {
  // XXX: Write back 500 status code, whatever?
  int err = uv_read_stop((uv_stream_t*) conn);
  assert(err == 0);
  uv_close((uv_handle_t*) conn, on_close_cb);
}

//
// call 
//
//   check_http_header(request, response)
//
// this decides wheather we want to abort prematurely
// and also if we want to read in the body.
//

static void
handle_http_header_parsed(Connection *conn)
{
  HTTP::Request &req = conn->req;

  int content_length = req.content_length;
  if (content_length < 0) {
    content_length = 0;
  }

  conn->in_body = true;

  bool keep_alive = req.is_keep_alive();
  int num_bytes_in_buffer = conn->read_buffer.size() - req.body_start;

  //
  // make sure we complete reading in the body
  // XXX: Handle Chunked-Encoding
  //
  if (content_length <= num_bytes_in_buffer) {
    // we have read the body completely into the buffer
    if (!keep_alive) {
      int err = uv_read_stop((uv_stream_t*) conn);
      assert(err == 0);
    }
    handle_http_request(conn);
  }
}

static void
handle_http_body(Connection *conn)
{
  handle_http_header_parsed(conn); // XXX: 
}

static void
handle_response(const HTTP::Request &req, DBuf &out, bool keep_alive)
{
  // Produce output
  if (req.http_version == 10) {
    out << "HTTP/1.0 200 OK\r\n";

    if (keep_alive) {
      out << "Connection: Keep-Alive\r\n";
    }
  }
  else if (req.http_version == 11) {
    out << "HTTP/1.1 200 OK\r\n";

    if (!keep_alive) {
      out << "Connection: Close\r\n";
    }
  }

  const char *body = "<html><body>Blaaaaaah</body></html>";
  int body_sz = strlen(body);

  out << "Content-Length: ";
  out.append_num(body_sz);
  out << "\r\n";

  out << "Content-Type: text/html\r\n\r\n";
  out.append(body, body_sz);
}


/*
 * Here we have to update the buffer in case of keep-alive
 *
 * This is called only when the whole body has been read in!
 *
 * Read has been stopped for keep_alive == false.
 *
 * It can be, that the next request (keep_alive == true) will arrive before the
 * on_write_done_cb is called. That is why we have to allocate a new
 * write_req_t for every write request we do.
 */
static void
handle_http_request(Connection *conn)
{
  HTTP::Request &request = conn->req;
  bool keep_alive = request.is_keep_alive();

  int content_length = request.content_length;
  if (content_length < 0) { content_length = 0; }

  write_req_t *req = new write_req_t();
  req->conn = conn;

  handle_response(request, req->out, keep_alive); 
  req->buf = uv_buf_init(req->out.data(), req->out.size());

  if (keep_alive) {
    // how many bytes in our buffer belong to the next request?
    size_t request_bytes = request.body_start + content_length;
    if (conn->read_buffer.size() > request_bytes) {
      conn->read_buffer.shift_left(request_bytes);
    }
    else {
      conn->read_buffer.reset();
    }
  }

  int err = uv_write((uv_write_t*) req, (uv_stream_t*)req->conn, &req->buf, 1, on_write_done_cb);
  assert(err == 0);
}

static void
on_read_cb(uv_stream_t *stream, ssize_t nread, uv_buf_t buf)
{
  Connection *conn = (Connection*) stream;

  assert(conn->read_clear == false);

  if (nread < 0) {
    //
    // XXX: Do we have to call uv_read_stop(), or is it implicit?
    //
    // on_read_cb will never be called again for this connection, so we don't
    // have to reset anything.
    //
    uv_close((uv_handle_t*) conn, on_close_cb);
  }
  else if (nread > 0) {
    conn->read_buffer.increase_size(nread);
    conn->read_clear = true;

    if (conn->in_body) {
      // We are reading in the body. No need to call the parser!
      handle_http_body(conn);
    }
    else {
      conn->parse_offset = conn->parser.run(conn->req, conn->read_buffer.data(), conn->read_buffer.size(), conn->parse_offset);

      if (conn->parser.is_finished()) {
        handle_http_header_parsed(conn);
      }
      else if (conn->parser.has_error()) {
        handle_http_error(conn);
      }
    }
  }
  else {
    //
    // This happens when libuv calls alloc_read_buffer, but does not need the buffer.
    // We don't have to free the buffer, as it is part of the connection.
    //
    assert(nread == 0);
    conn->read_clear = true;
  }
}

void on_new_connection(uv_stream_t *server, int status) {
  if (status == -1) {
    printf("on_new_connection: ERROR\n");
    // error!
    return;
  }

  Connection *conn = new Connection(10000);

  int err;

  err = uv_tcp_init(loop, (uv_tcp_t*) conn);
  assert(err == 0);
  err = uv_tcp_nodelay((uv_tcp_t*) conn, 1);
  assert(err == 0);

  if (uv_accept(server, (uv_stream_t*) conn) == 0) {
    err = uv_read_start((uv_stream_t*) conn, alloc_read_buffer, on_read_cb);
    assert(err == 0);
  } else {
    printf("ACCEPT failed\n");
    delete conn;
  }
  /*else {
    uv_close((uv_handle_t*) client, NULL);
  }*/
}

int main(int argc, char **argv) {
  loop = uv_loop_new(); //uv_default_loop();

  uv_tcp_t server;
  uv_tcp_init(loop, &server);

  struct sockaddr_in bind_addr = uv_ip4_addr("0.0.0.0", 7000);
  uv_tcp_bind(&server, bind_addr);
  int r = uv_listen((uv_stream_t*) &server, 128, on_new_connection);
  if (r) {
    fprintf(stderr, "Listen error %s\n", uv_err_name(uv_last_error(loop)));
    return 1;
  }

  return uv_run(loop);
}
