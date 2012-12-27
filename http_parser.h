#ifndef __HTTP_PARSER__HEADER__
#define __HTTP_PARSER__HEADER__

#include <stdint.h>
#include <stdbool.h>

typedef int32_t byte_pos;
struct byte_pos_range { byte_pos from, to; };

/*
 * User visible data
 */
struct http_parser_data {
  struct byte_pos_range request_uri;
  struct byte_pos_range fragment;
  struct byte_pos_range request_method;
  struct byte_pos_range http_version;
  struct byte_pos_range request_path;
  struct byte_pos_range query;

  int32_t content_length;
  struct byte_pos_range header_content_type;
  struct byte_pos_range header_date;
  struct byte_pos_range header_host;
  struct byte_pos_range header_user_agent;
  struct byte_pos_range header_referer;
  struct byte_pos_range header_cookie;
  struct byte_pos_range header_connection;

  byte_pos body_start;
};

struct http_parser {
  int saved_cs;

  byte_pos mark;
  byte_pos mark_query;
  struct byte_pos_range field_name;

  struct http_parser_data data;
};

void http_parser_init(struct http_parser *parser);

byte_pos http_parser_run(struct http_parser *parser,
                         const char *buffer, byte_pos buffer_length, byte_pos buffer_offset);

bool http_parser_has_error(const struct http_parser *parser);
bool http_parser_is_finished(const struct http_parser *parser);

#endif
