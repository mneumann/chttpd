#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <assert.h>

#include <strings.h> // bzero
#include <stdlib.h> // exit
#include <stdbool.h> // bool

#include <stdint.h> // 

#include <unistd.h> // read, write

#include <pthread.h>
#include "http_parser.h"

#include <string.h> // memcpy, strlen

#include <sys/uio.h> // writev

static void readn(int fd, char *buf, size_t n) {
  while (n > 0) {
    ssize_t c = read(fd, (void*)buf, n);
    if (c < 0) {
      perror("ERROR reading from socket");
      exit(1);
    }
    assert(c <= n);
    n -= c;
    buf += c;
  }
}

static void print_buffer(char *buffer, int buf_len, int buf_offset) {
  if (buf_len > 0) {
    char c = buffer[buf_len-1];
    buffer[buf_len-1] = '\0';
    printf("<<<%s>>>\noffset: %d\n", buffer, buf_offset);
    buffer[buf_len-1] = c;
  } else {
    printf("empty buffer\noffset: %d\n", buf_offset);
  }
}

static bool is_keep_alive(struct http_parser_data *data) {
  switch (data->http_version) {
    case 10:
      if (data->header_connection != HTTP_CONNECTION_KEEP_ALIVE) return false;
      break;
    case 11:
      if (data->header_connection == HTTP_CONNECTION_CLOSE) return false;
      break;
    default:
      return false;
  };

  switch (data->request_method) {
    case HTTP_REQUEST_METHOD_HEAD:
    case HTTP_REQUEST_METHOD_GET:
      return true;
      break;

    case HTTP_REQUEST_METHOD_POST:
    case HTTP_REQUEST_METHOD_PUT:
      return (data->content_length >= 0);
      break;
    // XXX
  };

  return false;
}

void print_header(const char *header, struct byte_range r, char *buffer) {
  assert(r.from <= r.to);

  if (r.from < 0 || r.to < 0) {
    printf("HEADER %s: NOT FOUND\n", header);
  }
  else {
    int sz = r.to - r.from;
    char *str = (char*) malloc(sz+1);
    assert(str);
    memcpy(str, buffer+r.from, sz); 
    str[sz] = '\0';
    printf("HEADER %s: %s\n", header, str);
    free(str);
  }
}

// returns number of overflow bytes (they) 
// return < 0 for not keep-alive
int parsing_done(struct http_parser_data *data, char *buffer, byte_pos buf_len, int sock) {
  //print_header("request_uri", data->request_uri, buffer);
  //print_header("request_method", data->request_method, buffer);
  //print_header("connection", data->header_connection, buffer);

  //printf("Content-Length: %d\n", data->content_length);

  bool keep_alive = is_keep_alive(data); 

  int content_length = data->content_length;
  if (content_length < 0) {
    content_length = 0;
  }

  assert(data->body_start >= 0);
  assert(buf_len >= data->body_start);

  // [0, 1, 2]
  int num_bytes_in_buffer = buf_len - data->body_start;

  struct iovec out[10];
  int out_n = 0;

  assert(data->http_version == 10 || data->http_version == 11);

  if (data->http_version == 10) {
    out[out_n].iov_base = "HTTP/1.0 OK 200\r\n";
    out[out_n].iov_len = strlen(out[out_n].iov_base);
    ++out_n;

    if (keep_alive) {
      out[out_n].iov_base = "Connection: Keep-Alive\r\n";
      out[out_n].iov_len = strlen(out[out_n].iov_base);
      ++out_n;
    }
  }
  else if (data->http_version == 11) {
    out[out_n].iov_base = "HTTP/1.1 OK 200\r\n";
    out[out_n].iov_len = strlen(out[out_n].iov_base);
    ++out_n;

    if (!keep_alive) {
      out[out_n].iov_base = "Connection: Close\r\n";
      out[out_n].iov_len = strlen(out[out_n].iov_base);
      ++out_n;
    }
  }

  char *body = "123";
  char content_length_header[32];
  int body_sz = strlen(body);
  int err = snprintf(content_length_header, 32, "Content-Length: %d\r\n", body_sz);
  assert(err > 0 && err < 32);

  out[out_n].iov_base = content_length_header; 
  out[out_n].iov_len = err; // should be string length!
  ++out_n;

  out[out_n].iov_base = "Content-Type: text/ascii\r\n\r\n"; 
  out[out_n].iov_len = strlen(out[out_n].iov_base); 
  ++out_n;

  out[out_n].iov_base = body; 
  out[out_n].iov_len = body_sz;
  ++out_n;

  int bytes_needed;

  if (keep_alive) {
    bytes_needed = content_length - num_bytes_in_buffer;

    if (bytes_needed > 0) {
      char *body_buf = (char*) malloc(bytes_needed); // XXX: alloc buf that holds whole body!
      assert(body_buf);
      readn(sock, body_buf, bytes_needed);
      bytes_needed = 0;
      free(body_buf);
    }
    bytes_needed = -bytes_needed;
  } else {
    // means, close connection
    bytes_needed = -1;
  }

  ssize_t res = writev(sock, out, out_n);

  return bytes_needed;
}


static void handle_connection(int sock)
{
  struct http_parser parser;
  http_parser_init(&parser);

  byte_pos buf_capacity = 4096;
  char stack_buffer[4096];
  byte_pos buf_len = 0;
  byte_pos buf_offset = 0;
  char *buffer = stack_buffer; //(char*) malloc(buf_capacity);
  assert(buffer);

  for (;;) {
    assert(buf_len <= buf_capacity);

    buf_offset = http_parser_run(&parser, buffer, buf_len, buf_offset); 

    if (http_parser_has_error(&parser)) {
      printf("Invalid HTTP----------------------------------------------\n");
      print_buffer(buffer, buf_len, buf_offset);
      fprintf(stderr, "Invalid HTTP. Aborting\n");
      break;
    }

    if (http_parser_is_finished(&parser)) {
      //printf("HTTP parsing done\n");
      const int read_too_much = parsing_done(&parser.data, buffer, buf_len, sock);
      if (read_too_much < 0) {
        // connection close
        break;
      }
      else {
        if (read_too_much > 0) {
          memmove(buffer, buffer+(buf_len-read_too_much), read_too_much);
        }

        buf_len = read_too_much;
        buf_offset = 0;
        http_parser_init(&parser);
        continue;
 
      }
    }

    if (buf_len == buf_capacity) {
      fprintf(stderr, "realloc\n");
      // should allocate new buffer!
      char *new_buf = NULL;
      if (buffer == stack_buffer) {
        new_buf = malloc(buf_capacity*2);
      }
      else {
        new_buf = realloc(buffer, buf_capacity*2);
      }
      assert(new_buf);
      buffer = new_buf;
      buf_capacity *= 2;
    }

    ssize_t cnt = read(sock, (void*)(buffer+buf_len), buf_capacity-buf_len);
    if (cnt < 0) {
      perror("ERROR reading from socket");
    }

    if (cnt == 0) continue;

    buf_len += cnt;
  }

  if (buffer != stack_buffer) {
    free(buffer);
  }

  //printf("Closing socket\n");
  close(sock);
}

struct thread_args {
  pthread_t thread;
  int accept;
  int fd;
};

static void *start_thread(void *args) {
  struct thread_args *ta = (struct thread_args*) args; 

  if (ta->accept == 1) {
    struct sockaddr_in cli_addr;
    socklen_t clilen;

    for (;;) {

      /* Accept actual connection from the client */
      int newsockfd = accept(ta->fd, (struct sockaddr *)&cli_addr, &clilen);
      if (newsockfd < 0) 
      {
          perror("ERROR on accept");
          exit(1);
      }
      handle_connection(newsockfd);

    }
  }
  else {
    handle_connection(ta->fd);
  }

  return NULL;
}

int main( int argc, char *argv[] )
{
  int sockfd, newsockfd, portno;
  struct sockaddr_in serv_addr, cli_addr;
  socklen_t clilen;

  portno = atoi(argv[1]);

#if 0
  int nthreads = atoi(argv[2]);
#endif

  /* First call to socket() function */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
  {
      perror("ERROR opening socket");
      exit(1);
  }
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    //portno = 5001;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
 
    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
                          sizeof(serv_addr)) < 0)
    {
         perror("ERROR on binding");
         exit(1);
    }

    /* Now start listening for the clients, here process will
    * go in sleep mode and will wait for the incoming connection
    */
    listen(sockfd, 100);
    clilen = sizeof(cli_addr);



#if 0
    fprintf(stderr, "Spawning up %d threads\n", nthreads);
    struct thread_args *threads = (struct thread_args*) malloc(nthreads*sizeof(struct thread_args));

    for (int i = 0; i < nthreads; ++i) {
      threads[i].fd = sockfd; 
      threads[i].accept = 1;
      int ec = pthread_create(&threads[i].thread, NULL, start_thread, &threads[i]);
    }

    fprintf(stderr, "Done\n");
#endif

    for (;;) {
#if 0
      sleep(1);
#endif

#if 1
      /* Accept actual connection from the client */
      newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, 
                                  &clilen);
      if (newsockfd < 0) 
      {
          perror("ERROR on accept");
          exit(1);
      }

      struct thread_args *ta = (struct thread_args*)malloc(sizeof(struct thread_args));
      assert(ta);
      ta->fd = newsockfd;
      ta->accept = 0;
      int ec = pthread_create(&ta->thread, NULL, start_thread, ta);
#endif
    }

    return 0; 
}
