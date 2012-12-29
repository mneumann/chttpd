/**
 * Copyright (c) 2005 Zed A. Shaw
 * You can redistribute it and/or modify it under the same terms as Ruby.
 *
 * Copyright (c) 2012 by Michael Neumann (mneumann@ntecs.de)
 */

// compile with ragel -G2 -C ...

/** Machine **/

%%{
  
  machine http_parser;

  action mark { parser->mark = (byte_pos)(fpc - buffer); }
  action mark_query { parser->mark_query = (byte_pos)(fpc - buffer); }

  action request_uri { ASSIGN_FIELD(request_uri, fpc); }
  action fragment { ASSIGN_FIELD(fragment, fpc); }

  action request_method_get { req->request_method = HTTP_REQUEST_METHOD_GET; }
  action request_method_post { req->request_method = HTTP_REQUEST_METHOD_POST; }
  action request_method_head { req->request_method = HTTP_REQUEST_METHOD_HEAD; }
  action request_method_options { req->request_method = HTTP_REQUEST_METHOD_OPTIONS; }
  action request_method_put { req->request_method = HTTP_REQUEST_METHOD_PUT; }
  action request_method_delete { req->request_method = HTTP_REQUEST_METHOD_DELETE; }
  action request_method_trace { req->request_method = HTTP_REQUEST_METHOD_TRACE; }
  action request_method_connect { req->request_method = HTTP_REQUEST_METHOD_CONNECT; }
  action request_method_other {
    req->request_method = HTTP_REQUEST_METHOD_OTHER;
    ASSIGN_FIELD(request_method_other, fpc);
  }

  action http_version_10 {	req->http_version = 10; }
  action http_version_11 {	req->http_version = 11; }
  action request_path { ASSIGN_FIELD(request_path, fpc); }

  action query {
    req->query.from = parser->mark_query;
    req->query.to = (byte_pos)(fpc - buffer);
  }

  #
  # headers
  #

  action content_length_init { req->content_length = 0; }

  action content_length_digit {
    req->content_length *= 10;
    req->content_length += (fc - '0');
  }


  action header_content_length { }

  #
  # Optimize some common headers
  #
  action header_content_type { ASSIGN_FIELD(header_content_type, fpc); }
  action header_date { ASSIGN_FIELD(header_date, fpc); }
  action header_host { ASSIGN_FIELD(header_host, fpc); }
  action header_user_agent { ASSIGN_FIELD(header_user_agent, fpc); }
  action header_referer { ASSIGN_FIELD(header_referer, fpc); }
  action header_cookie { ASSIGN_FIELD(header_cookie, fpc); }

  action header_connection_close { req->header_connection = HTTP_CONNECTION_CLOSE; }
  action header_connection_keep_alive { req->header_connection = HTTP_CONNECTION_KEEP_ALIVE; }

  action field_name {
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(fpc - buffer);
  }

  action header {
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }

  action done {
    req->body_start = (byte_pos)(fpc - buffer + 1);
    fbreak;
  }

  include http_parser_common "http_parser_common.rl";

}%%

/** Data **/
%% write data;

#include "http_parser.h"
#include <assert.h>

#define ASSIGN_FIELD(field, fpc) \
  req->field.from = parser->mark; \
  req->field.to = (byte_pos)(fpc - buffer);

void http_request_init(struct http_request *req) {
  #define INIT_RANGE(field) \
    req->field.from = -1;  \
    req->field.to = -1;

  INIT_RANGE(request_uri);
  INIT_RANGE(fragment);
  INIT_RANGE(request_method_other);
  INIT_RANGE(request_path);
  INIT_RANGE(query);

  req->content_length = -1;
  req->http_version = -1;
  req->request_method = -1;
  req->header_connection = -1;

  INIT_RANGE(header_content_type);
  INIT_RANGE(header_date);
  INIT_RANGE(header_host);
  INIT_RANGE(header_user_agent);
  INIT_RANGE(header_referer);
  INIT_RANGE(header_cookie);

  req->body_start = -1;

  #undef INIT_RANGE
}

void http_parser_init(struct http_parser *parser) {
  int cs = 0;
  %% write init;
  parser->saved_cs = cs;
}

byte_pos http_parser_run(struct http_parser *parser, struct http_request *req,
                         const char *buffer, byte_pos buffer_length, byte_pos buffer_offset) {

  assert(parser);
  assert(buffer);

  if (buffer_length == 0) return 0;

  assert(buffer_length > 0);
  assert(buffer_offset < buffer_length);

  // Ragel uses: cs, p, pe
  int cs = parser->saved_cs;               // current ragel machine state
  const char *p = buffer + buffer_offset;  // pointer to start of data
  const char *pe = buffer + buffer_length; // pointer to end of data

  %% write exec;

  assert(p <= pe); // buffer overflow after parsing execute

  parser->saved_cs = cs;

  return (p - buffer); // returns the new buffer offset
}

bool http_parser_has_error(const struct http_parser *parser) {
  return (parser->saved_cs == http_parser_error);
}

bool http_parser_is_finished(const struct http_parser *parser) {
  return (parser->saved_cs >= http_parser_first_final);
}

bool http_request_is_keep_alive(struct http_request *req) {
  switch (req->http_version) {
    case 10:
      if (req->header_connection != HTTP_CONNECTION_KEEP_ALIVE) return false;
      break;
    case 11:
      if (req->header_connection == HTTP_CONNECTION_CLOSE) return false;
      break;
    default:
      assert(false);
      return false;
  };

  switch (req->request_method) {
    case HTTP_REQUEST_METHOD_HEAD:
    case HTTP_REQUEST_METHOD_GET:
      return true;
      break;

    case HTTP_REQUEST_METHOD_POST:
    case HTTP_REQUEST_METHOD_PUT:
      return (req->content_length >= 0);
      break;
    // XXX
  };

  return false;
}
