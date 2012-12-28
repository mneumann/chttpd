%%{
  
  machine http_parser_common;

#### HTTP PROTOCOL GRAMMAR
# line endings
  CRLF = "\r\n";

# character types
  CTL = (cntrl | 127);
  safe = ("$" | "-" | "_" | ".");
  extra = ("!" | "*" | "'" | "(" | ")" | ",");
  reserved = (";" | "/" | "?" | ":" | "@" | "&" | "=" | "+");
  unsafe = (CTL | " " | "\"" | "#" | "%" | "<" | ">");
  national = any -- (alpha | digit | reserved | extra | safe | unsafe);
  unreserved = (alpha | digit | safe | extra | national);
  escape = ("%" xdigit xdigit);
  uchar = (unreserved | escape);
  pchar = (uchar | ":" | "@" | "&" | "=" | "+");
  tspecials = ("(" | ")" | "<" | ">" | "@" | "," | ";" | ":" | "\\" | "\"" | "/" | "[" | "]" | "?" | "=" | "{" | "}" | " " | "\t");

# elements
  token = (ascii -- (CTL | tspecials));

# URI schemes and absolute paths
  scheme = ( alpha | digit | "+" | "-" | "." )* ;
  absolute_uri = (scheme ":" (uchar | reserved )*);

  path = ( pchar+ ( "/" pchar* )* ) ;
  query = ( uchar | reserved )* %query;
  param = ( pchar | "/" )* ;
  params = ( param ( ";" param )* ) ;
  rel_path = ( path? %request_path (";" params)? ) ("?" %mark_query query)?;
  absolute_path = ( "/"+ rel_path );

  Request_URI = ( "*" | absolute_uri | absolute_path ) >mark %request_uri;
  Fragment = ( uchar | reserved )* >mark %fragment;

  KnownMethod = 
         # HTTP/1.0
           ("GET" %request_method_get)
         | ("POST" %request_method_post)
         | ("HEAD" %request_method_head)
           
           # HTTP/1.1
         | ("OPTIONS" %request_method_options)
         | ("PUT" %request_method_put)
         | ("DELETE" %request_method_delete)
         | ("TRACE" %request_method_trace)
         | ("CONNECT" %request_method_connect)
         ;

  OtherMethod = (( upper | digit | safe ){1,20} - KnownMethod) >mark %request_method_other;

  Method = KnownMethod | OtherMethod;

  # We only support 1.0 and 1.1, so make it explicit
  HTTP_Version = ("HTTP/1.0" %http_version_10 ) |
                 ("HTTP/1.1" %http_version_11 ) ;

  #http_number = ( digit+ "." digit+ ) ;
  #HTTP_Version = ( "HTTP/" http_number ) >mark %http_version ;

  Request_Line = ( Method " " Request_URI ("#" Fragment){0,1} " " HTTP_Version CRLF ) ;

  field_name = ( token -- ":" )+ >mark %field_name;
  field_value = any* >mark;
  field_delim = ":" " "*;

  content_length = ([0-9]+ $content_length_digit) >content_length_init;

  field = 
          ("Content-Length"i field_delim content_length %header_content_length)

        | ("Content-Type"i field_delim field_value %header_content_type)
        | ("Date"i field_delim field_value %header_date)
        | ("Host"i field_delim field_value %header_host)
        | ("User-Agent"i field_delim field_value %header_user_agent)
        | ("Referer"i field_delim field_value %header_referer)
        | ("Cookie"i field_delim field_value %header_cookie)

        | ("Connection"i field_delim (
               ("Close"i %header_connection_close)
             | ("Keep-Alive"i %header_connection_keep_alive)
             | (field_value - "Close"i - "Keep-Alive"i) # XXX: we ignore all other values here as we are not interested
             )
          )

        | (
            (field_name - "Content-Length"i - "Content-Type"i - "Date"i - "Host"i - "User-Agent"i - "Referer"i
             - "Cookie"i - "Connection"i) 
            field_delim field_value %header);

#        | ("Accept"i field_delim field_value %field_accept)
#        | ("Accept-Charset"i field_delim field_value %field_accept_charset)
#        | ("Accept-Encoding"i field_delim field_value %field_accept_encoding)
#        | ("Accept-Language"i field_delim field_value %field_accept_language)
#        | ("Accept-Datetime"i field_delim field_value %field_accept_datetime)
#        | ("Authorization"i field_delim field_value %field_authorization)
#        | ("Cache-Control"i field_delim field_value %field_cache_control)
#        | ("Content-MD5"i field_delim field_value %field_content_md5)
#        | ("Expect"i field_delim field_value %field_expect)
#        | ("From"i field_delim field_value %field_from)
#        | ("If-Match"i field_delim field_value %field_if_match)
#        | ("If-Modified-Since"i field_delim field_value %field_if_modified_since)
#        | ("If-None-Match"i field_delim field_value %field_if_none_match)
#        | ("If-Range"i field_delim field_value %field_if_range)
#        | ("If-Unmodified-Since"i field_delim field_value %field_if_unmodified_since)
#        | ("Max-Forwards"i field_delim field_value %field_max_forwards)
#        | ("Pragma"i field_delim field_value %field_pragma)
#        | ("Proxy-Authorization"i field_delim field_value %field_proxy_authorization)
#        | ("Range"i field_delim field_value %field_range)
#        | ("TE"i field_delim field_value %field_te)
#        | ("Upgrade"i field_delim field_value %field_upgrade)
#        | ("Via"i field_delim field_value %field_via)
#        | ("Warning"i field_delim field_value %field_warning)


  message_header = field :> CRLF;

  Request = Request_Line ( message_header )* ( CRLF @done );

main := Request;

}%%
