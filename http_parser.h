#ifndef __HTTP_PARSER__HEADER__
#define __HTTP_PARSER__HEADER__

#include <stdint.h>

namespace HTTP
{

  enum class REQUEST_METHOD {
    NONE = 0,
    GET = 1,
    POST,
    HEAD,
    OPTIONS,
    PUT,
    DELETE,
    TRACE,
    CONNECT,
    OTHER = 100 
  };

  enum class CONNECTION {
    NONE = 0,
    CLOSE = 1,
    KEEP_ALIVE = 2
  };

  typedef int32_t BytePos;

  struct ByteSlice
  {
    BytePos from;
    BytePos to;
    ByteSlice() : from(-1), to(-1) {}
  };

  struct Request
  {
    ByteSlice request_uri;
    ByteSlice fragment;
    ByteSlice request_path;
    ByteSlice query;

    int32_t   http_version; // XXX: use signed char?

    REQUEST_METHOD request_method;
    CONNECTION     header_connection;

    ByteSlice request_method_other;
    int32_t   content_length;

    ByteSlice header_content_type;
    ByteSlice header_date;
    ByteSlice header_host;
    ByteSlice header_user_agent;
    ByteSlice header_referer;
    ByteSlice header_cookie;

    BytePos   body_start;

    Request() : request_method(REQUEST_METHOD::NONE),
                header_connection(CONNECTION::NONE),
                content_length(-1),
                http_version(-1),
                body_start(-1) {}

    bool is_keep_alive();
  };

  class Parser
  {
    private:

    int saved_cs;
    BytePos   mark;
    BytePos   mark_query;
    ByteSlice field_name;

    public:

    Parser();

    BytePos run(Request &request, const char *buffer, BytePos buffer_length, BytePos buffer_offset);

    bool has_error();
    bool is_finished();
  };

}; /* namespace HTTP */

#endif
