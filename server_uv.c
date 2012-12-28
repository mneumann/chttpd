#include <uv.h>
#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // strlen

static uv_loop_t *loop;

uv_buf_t alloc_buffer(uv_handle_t *handle, size_t suggested_size) {
  return uv_buf_init((char*) malloc(suggested_size), suggested_size);
}

struct write_req_t {
  uv_write_t req;
  uv_buf_t buf;
  uv_stream_t *stream;
};

void my_close(uv_handle_t *handle) {
  fprintf(stderr, "Closing handle\n");
}

void my_callback(uv_write_t *req, int status) {
  fprintf(stderr, "Write finished\n");
  struct write_req_t *wr = (struct write_req_t*) req;
  free(wr->buf.base);
  free(wr);

  uv_close((uv_handle_t*)wr->stream, my_close);
}

void my_read(uv_stream_t *stream, ssize_t nread, uv_buf_t buf) {
  fprintf(stderr, "My read\n");
  if (nread == -1) {
    uv_close((uv_handle_t*)stream, my_close);
  } else if (nread > 0) {
    const char *str = "HTTP/1.1 OK 200\r\nConnection: Close\r\nContent-Type: text/html\r\nContent-Length: 39\r\n\r\n<html><body><b>Hallo</b></body></html>";
    const int sz = strlen(str);

    struct write_req_t *req = (struct write_req_t*) malloc(sizeof(struct write_req_t));
    req->buf = uv_buf_init((char*) malloc(sz), sz);
    req->stream = stream;
    memcpy(req->buf.base, str, sz);
    uv_write((uv_write_t*) req, stream, &req->buf, 1, my_callback);
  }

  if (buf.base) {
    free(buf.base);
  }
}

void on_new_connection(uv_stream_t *server, int status) {
  if (status == -1) {
    // error!
    return;
  }

  uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
  uv_tcp_init(loop, client);
  if (uv_accept(server, (uv_stream_t*) client) == 0) {
    uv_read_start((uv_stream_t*) client, alloc_buffer, my_read);
  }
  else {
    uv_close((uv_handle_t*) client, NULL);
  }
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
