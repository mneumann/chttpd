#ifndef __HTTP_PARSER__HEADER__
#define __HTTP_PARSER__HEADER__

#include <stdint.h>
#include <stdbool.h>

typedef int32_t byte_pos;
struct byte_range { byte_pos from, to; };

#define HTTP_REQUEST_METHOD_GET 1
#define HTTP_REQUEST_METHOD_POST 2
#define HTTP_REQUEST_METHOD_HEAD 3
#define HTTP_REQUEST_METHOD_OPTIONS 4
#define HTTP_REQUEST_METHOD_PUT 5
#define HTTP_REQUEST_METHOD_DELETE 6
#define HTTP_REQUEST_METHOD_TRACE 7
#define HTTP_REQUEST_METHOD_CONNECT 8
#define HTTP_REQUEST_METHOD_OTHER 100 

#define HTTP_CONNECTION_CLOSE 1
#define HTTP_CONNECTION_KEEP_ALIVE 2


/*
 * User visible data
 */
struct http_request {
  struct byte_range request_uri;
  struct byte_range fragment;
  struct byte_range request_path;
  struct byte_range query;

  int32_t http_version; // XXX: use signed char?

  int32_t request_method; // XXX: use signed char?
  int32_t header_connection; // XXX: use signed char?

  struct byte_range request_method_other;

  int32_t content_length;
  struct byte_range header_content_type;
  struct byte_range header_date;
  struct byte_range header_host;
  struct byte_range header_user_agent;
  struct byte_range header_referer;
  struct byte_range header_cookie;

  byte_pos body_start;
};

struct http_parser {
  int saved_cs;

  byte_pos mark;
  byte_pos mark_query;
  struct byte_range field_name;
};

void http_parser_init(struct http_parser *parser);

byte_pos http_parser_run(struct http_parser *parser, struct http_request *req,
                         const char *buffer, byte_pos buffer_length, byte_pos buffer_offset);

bool http_parser_has_error(const struct http_parser *parser);


bool http_parser_is_finished(const struct http_parser *parser);

void http_request_init(struct http_request *req);
bool http_request_is_keep_alive(struct http_request *data);

#endif
