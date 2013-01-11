/**
 * Copyright (c) 2005 Zed A. Shaw
 * You can redistribute it and/or modify it under the same terms as Ruby.
 *
 * Copyright (c) 2012, 2013 by Michael Neumann (mneumann@ntecs.de)
 */

// compile with ragel -G2 -C ...

/** Machine **/

%%{
  
  machine http_parser;

  action mark { this->mark = (BytePos)(fpc - buffer); }
  action mark_query { this->mark_query = (BytePos)(fpc - buffer); }

  action request_uri { ASSIGN_FIELD(request_uri, fpc); }
  action fragment { ASSIGN_FIELD(fragment, fpc); }

  action request_method_get { request.request_method = REQUEST_METHOD::GET; }
  action request_method_post { request.request_method = REQUEST_METHOD::POST; }
  action request_method_head { request.request_method = REQUEST_METHOD::HEAD; }
  action request_method_options { request.request_method = REQUEST_METHOD::OPTIONS; }
  action request_method_put { request.request_method = REQUEST_METHOD::PUT; }
  action request_method_delete { request.request_method = REQUEST_METHOD::DELETE; }
  action request_method_trace { request.request_method = REQUEST_METHOD::TRACE; }
  action request_method_connect { request.request_method = REQUEST_METHOD::CONNECT; }
  action request_method_other {
    request.request_method = REQUEST_METHOD::OTHER;
    ASSIGN_FIELD(request_method_other, fpc);
  }

  action http_version_10 {	request.http_version = 10; }
  action http_version_11 {	request.http_version = 11; }
  action request_path { ASSIGN_FIELD(request_path, fpc); }

  action query {
    request.query.from = this->mark_query;
    request.query.to = (BytePos)(fpc - buffer);
  }

  #
  # headers
  #

  action content_length_init { request.content_length = 0; }

  action content_length_digit {
    request.content_length *= 10;
    request.content_length += (fc - '0');
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

  action header_connection_close { request.header_connection = CONNECTION::CLOSE; }
  action header_connection_keep_alive { request.header_connection = CONNECTION::KEEP_ALIVE; }

  action field_name {
    this->field_name.from = this->mark;
    this->field_name.to = (BytePos)(fpc - buffer);
  }

  action header {
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }

  action done {
    request.body_start = (BytePos)(fpc - buffer + 1);
    fbreak;
  }

  include http_parser_common "http_parser_common.rl";

}%%

#include "http_parser.h"
#include <assert.h>

namespace HTTP
{

/** Data **/
%% write data;

#define ASSIGN_FIELD(field, fpc) \
  request.field.from = this->mark; \
  request.field.to = (BytePos)(fpc - buffer);

Parser::Parser()
{
  int cs = 0;
  %% write init;
  this->saved_cs = cs;
}

BytePos
Parser::run(Request &request, const char *buffer, BytePos buffer_length, BytePos buffer_offset)
{
  if (buffer_length == 0) return 0;

  assert(buffer);
  assert(buffer_length > 0);
  assert(buffer_offset < buffer_length);

  // Ragel uses: cs, p, pe
  int cs = this->saved_cs;                 // current ragel machine state
  const char *p = buffer + buffer_offset;  // pointer to start of data
  const char *pe = buffer + buffer_length; // pointer to end of data

  %% write exec;

  assert(p <= pe); // buffer overflow after parsing execute

  this->saved_cs = cs;

  return (p - buffer); // returns the new buffer offset
}

bool
Parser::has_error()
{
  return (this->saved_cs == http_parser_error);
}

bool
Parser::is_finished()
{
  return (this->saved_cs >= http_parser_first_final);
}

bool
Request::is_keep_alive()
{
  switch (this->http_version) {
    case 10:
      if (this->header_connection != CONNECTION::KEEP_ALIVE) return false;
      break;
    case 11:
      if (this->header_connection == CONNECTION::CLOSE) return false;
      break;
    default:
      assert(false);
      return false;
  };

  switch (this->request_method) {
    case REQUEST_METHOD::HEAD:
    case REQUEST_METHOD::GET:
      return true;
      break;

    case REQUEST_METHOD::POST:
    case REQUEST_METHOD::PUT:
      return (this->content_length >= 0);
      break;
    // XXX
  };

  return false;
}

}; // namespace HTTP
