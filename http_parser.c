
#line 1 "http_parser.rl"
/**
 * Copyright (c) 2005 Zed A. Shaw
 * You can redistribute it and/or modify it under the same terms as Ruby.
 *
 * Copyright (c) 2012 by Michael Neumann (mneumann@ntecs.de)
 */

// compile with ragel -G2 -C ...

/** Machine **/


#line 88 "http_parser.rl"


/** Data **/

#line 21 "http_parser.c"
static const int http_parser_start = 1;
static const int http_parser_first_final = 180;
static const int http_parser_error = 0;

static const int http_parser_en_main = 1;


#line 92 "http_parser.rl"

#include "http_parser.h"
#include <assert.h>

#define ASSIGN_FIELD(field, fpc) \
  parser->data.field.from = parser->mark; \
  parser->data.field.to = (byte_pos)(fpc - buffer);

static void http_parser_data_init(struct http_parser_data *data) {
  #define INIT_RANGE(field) \
    data->field.from = -1;  \
    data->field.to = -1;

  INIT_RANGE(request_uri);
  INIT_RANGE(fragment);
  INIT_RANGE(request_method_other);
  INIT_RANGE(request_path);
  INIT_RANGE(query);

  data->content_length = -1;
  data->http_version = -1;
  data->request_method = -1;
  data->header_connection = -1;

  INIT_RANGE(header_content_type);
  INIT_RANGE(header_date);
  INIT_RANGE(header_host);
  INIT_RANGE(header_user_agent);
  INIT_RANGE(header_referer);
  INIT_RANGE(header_cookie);

  data->body_start = -1;

  #undef INIT_RANGE
}

void http_parser_init(struct http_parser *parser) {
  int cs = 0;
  
#line 69 "http_parser.c"
	{
	cs = http_parser_start;
	}

#line 131 "http_parser.rl"
  parser->saved_cs = cs;

  http_parser_data_init(&parser->data);
}

byte_pos http_parser_run(struct http_parser *parser,
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

  
#line 97 "http_parser.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	switch( (*p) ) {
		case 36: goto tr0;
		case 67: goto tr2;
		case 68: goto tr3;
		case 71: goto tr4;
		case 72: goto tr5;
		case 79: goto tr6;
		case 80: goto tr7;
		case 84: goto tr8;
		case 95: goto tr0;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto tr0;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto tr0;
	} else
		goto tr0;
	goto st0;
st0:
cs = 0;
	goto _out;
tr0:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 135 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st123;
		case 95: goto st123;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st123;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st123;
	} else
		goto st123;
	goto st0;
tr9:
#line 30 "http_parser.rl"
	{
    parser->data.request_method = HTTP_REQUEST_METHOD_OTHER;
    ASSIGN_FIELD(request_method_other, p);
  }
	goto st3;
tr208:
#line 29 "http_parser.rl"
	{ parser->data.request_method = HTTP_REQUEST_METHOD_CONNECT; }
#line 30 "http_parser.rl"
	{
    parser->data.request_method = HTTP_REQUEST_METHOD_OTHER;
    ASSIGN_FIELD(request_method_other, p);
  }
	goto st3;
tr214:
#line 27 "http_parser.rl"
	{ parser->data.request_method = HTTP_REQUEST_METHOD_DELETE; }
#line 30 "http_parser.rl"
	{
    parser->data.request_method = HTTP_REQUEST_METHOD_OTHER;
    ASSIGN_FIELD(request_method_other, p);
  }
	goto st3;
tr217:
#line 22 "http_parser.rl"
	{ parser->data.request_method = HTTP_REQUEST_METHOD_GET; }
#line 30 "http_parser.rl"
	{
    parser->data.request_method = HTTP_REQUEST_METHOD_OTHER;
    ASSIGN_FIELD(request_method_other, p);
  }
	goto st3;
tr221:
#line 24 "http_parser.rl"
	{ parser->data.request_method = HTTP_REQUEST_METHOD_HEAD; }
#line 30 "http_parser.rl"
	{
    parser->data.request_method = HTTP_REQUEST_METHOD_OTHER;
    ASSIGN_FIELD(request_method_other, p);
  }
	goto st3;
tr228:
#line 25 "http_parser.rl"
	{ parser->data.request_method = HTTP_REQUEST_METHOD_OPTIONS; }
#line 30 "http_parser.rl"
	{
    parser->data.request_method = HTTP_REQUEST_METHOD_OTHER;
    ASSIGN_FIELD(request_method_other, p);
  }
	goto st3;
tr233:
#line 23 "http_parser.rl"
	{ parser->data.request_method = HTTP_REQUEST_METHOD_POST; }
#line 30 "http_parser.rl"
	{
    parser->data.request_method = HTTP_REQUEST_METHOD_OTHER;
    ASSIGN_FIELD(request_method_other, p);
  }
	goto st3;
tr235:
#line 26 "http_parser.rl"
	{ parser->data.request_method = HTTP_REQUEST_METHOD_PUT; }
#line 30 "http_parser.rl"
	{
    parser->data.request_method = HTTP_REQUEST_METHOD_OTHER;
    ASSIGN_FIELD(request_method_other, p);
  }
	goto st3;
tr240:
#line 28 "http_parser.rl"
	{ parser->data.request_method = HTTP_REQUEST_METHOD_TRACE; }
#line 30 "http_parser.rl"
	{
    parser->data.request_method = HTTP_REQUEST_METHOD_OTHER;
    ASSIGN_FIELD(request_method_other, p);
  }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 233 "http_parser.c"
	switch( (*p) ) {
		case 42: goto tr11;
		case 43: goto tr12;
		case 47: goto tr13;
		case 58: goto tr14;
	}
	if ( (*p) < 65 ) {
		if ( 45 <= (*p) && (*p) <= 57 )
			goto tr12;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr12;
	} else
		goto tr12;
	goto st0;
tr11:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 257 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr15;
		case 35: goto tr16;
	}
	goto st0;
tr15:
#line 19 "http_parser.rl"
	{ ASSIGN_FIELD(request_uri, p); }
	goto st5;
tr154:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 20 "http_parser.rl"
	{ ASSIGN_FIELD(fragment, p); }
	goto st5;
tr157:
#line 20 "http_parser.rl"
	{ ASSIGN_FIELD(fragment, p); }
	goto st5;
tr165:
#line 37 "http_parser.rl"
	{ ASSIGN_FIELD(request_path, p); }
#line 19 "http_parser.rl"
	{ ASSIGN_FIELD(request_uri, p); }
	goto st5;
tr176:
#line 17 "http_parser.rl"
	{ parser->mark_query = (byte_pos)(p - buffer); }
#line 39 "http_parser.rl"
	{
    parser->data.query.from = parser->mark_query;
    parser->data.query.to = (byte_pos)(p - buffer);
  }
#line 19 "http_parser.rl"
	{ ASSIGN_FIELD(request_uri, p); }
	goto st5;
tr180:
#line 39 "http_parser.rl"
	{
    parser->data.query.from = parser->mark_query;
    parser->data.query.to = (byte_pos)(p - buffer);
  }
#line 19 "http_parser.rl"
	{ ASSIGN_FIELD(request_uri, p); }
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 307 "http_parser.c"
	if ( (*p) == 72 )
		goto st6;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 84 )
		goto st7;
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 84 )
		goto st8;
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 80 )
		goto st9;
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 47 )
		goto st10;
	goto st0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	if ( (*p) == 49 )
		goto st11;
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	if ( (*p) == 46 )
		goto st12;
	goto st0;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	switch( (*p) ) {
		case 48: goto st13;
		case 49: goto st104;
	}
	goto st0;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	if ( (*p) == 13 )
		goto tr26;
	goto st0;
tr26:
#line 35 "http_parser.rl"
	{	parser->data.http_version = 10; }
	goto st14;
tr39:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr42:
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr62:
#line 68 "http_parser.rl"
	{ parser->data.header_connection = HTTP_CONNECTION_CLOSE; }
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr72:
#line 69 "http_parser.rl"
	{ parser->data.header_connection = HTTP_CONNECTION_KEEP_ALIVE; }
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr87:
#line 56 "http_parser.rl"
	{ }
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr94:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 61 "http_parser.rl"
	{ ASSIGN_FIELD(header_content_type, p); }
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr97:
#line 61 "http_parser.rl"
	{ ASSIGN_FIELD(header_content_type, p); }
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr103:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 66 "http_parser.rl"
	{ ASSIGN_FIELD(header_cookie, p); }
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr106:
#line 66 "http_parser.rl"
	{ ASSIGN_FIELD(header_cookie, p); }
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr112:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 62 "http_parser.rl"
	{ ASSIGN_FIELD(header_date, p); }
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr115:
#line 62 "http_parser.rl"
	{ ASSIGN_FIELD(header_date, p); }
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr121:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 63 "http_parser.rl"
	{ ASSIGN_FIELD(header_host, p); }
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr124:
#line 63 "http_parser.rl"
	{ ASSIGN_FIELD(header_host, p); }
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr133:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 65 "http_parser.rl"
	{ ASSIGN_FIELD(header_referer, p); }
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr136:
#line 65 "http_parser.rl"
	{ ASSIGN_FIELD(header_referer, p); }
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr148:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 64 "http_parser.rl"
	{ ASSIGN_FIELD(header_user_agent, p); }
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr151:
#line 64 "http_parser.rl"
	{ ASSIGN_FIELD(header_user_agent, p); }
#line 76 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr152:
#line 36 "http_parser.rl"
	{	parser->data.http_version = 11; }
	goto st14;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
#line 544 "http_parser.c"
	if ( (*p) == 10 )
		goto st15;
	goto st0;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	switch( (*p) ) {
		case 13: goto st16;
		case 33: goto tr29;
		case 67: goto tr30;
		case 68: goto tr31;
		case 72: goto tr32;
		case 82: goto tr33;
		case 85: goto tr34;
		case 99: goto tr30;
		case 100: goto tr31;
		case 104: goto tr32;
		case 114: goto tr33;
		case 117: goto tr34;
		case 124: goto tr29;
		case 126: goto tr29;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr29;
		} else if ( (*p) >= 35 )
			goto tr29;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr29;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr29;
		} else
			goto tr29;
	} else
		goto tr29;
	goto st0;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	if ( (*p) == 10 )
		goto tr35;
	goto st0;
tr35:
#line 81 "http_parser.rl"
	{
    parser->data.body_start = (byte_pos)(p - buffer + 1);
    {p++; cs = 180; goto _out;}
  }
	goto st180;
st180:
	if ( ++p == pe )
		goto _test_eof180;
case 180:
#line 604 "http_parser.c"
	goto st0;
tr29:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 614 "http_parser.c"
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr40:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st18;
tr37:
#line 71 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 654 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr39;
		case 32: goto tr40;
	}
	goto tr38;
tr38:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 668 "http_parser.c"
	if ( (*p) == 13 )
		goto tr42;
	goto st19;
tr30:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 680 "http_parser.c"
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 79: goto st21;
		case 111: goto st21;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 78: goto st22;
		case 79: goto st65;
		case 110: goto st22;
		case 111: goto st65;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 78: goto st23;
		case 84: goto st46;
		case 110: goto st23;
		case 116: goto st46;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 69: goto st24;
		case 101: goto st24;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 67: goto st25;
		case 99: goto st25;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 84: goto st26;
		case 116: goto st26;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 73: goto st27;
		case 105: goto st27;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 79: goto st28;
		case 111: goto st28;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 78: goto st29;
		case 110: goto st29;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr54;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr55:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st30;
tr54:
#line 71 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st30;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
#line 994 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr39;
		case 32: goto tr55;
		case 67: goto tr56;
		case 75: goto tr57;
		case 99: goto tr56;
		case 107: goto tr57;
	}
	goto tr38;
tr56:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st31;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
#line 1012 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr42;
		case 76: goto st32;
		case 108: goto st32;
	}
	goto st19;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	switch( (*p) ) {
		case 13: goto tr42;
		case 79: goto st33;
		case 111: goto st33;
	}
	goto st19;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 13: goto tr42;
		case 83: goto st34;
		case 115: goto st34;
	}
	goto st19;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	switch( (*p) ) {
		case 13: goto tr42;
		case 69: goto st35;
		case 101: goto st35;
	}
	goto st19;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	if ( (*p) == 13 )
		goto tr62;
	goto st19;
tr57:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st36;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
#line 1064 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr42;
		case 69: goto st37;
		case 101: goto st37;
	}
	goto st19;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	switch( (*p) ) {
		case 13: goto tr42;
		case 69: goto st38;
		case 101: goto st38;
	}
	goto st19;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	switch( (*p) ) {
		case 13: goto tr42;
		case 80: goto st39;
		case 112: goto st39;
	}
	goto st19;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	switch( (*p) ) {
		case 13: goto tr42;
		case 45: goto st40;
	}
	goto st19;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	switch( (*p) ) {
		case 13: goto tr42;
		case 65: goto st41;
		case 97: goto st41;
	}
	goto st19;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	switch( (*p) ) {
		case 13: goto tr42;
		case 76: goto st42;
		case 108: goto st42;
	}
	goto st19;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	switch( (*p) ) {
		case 13: goto tr42;
		case 73: goto st43;
		case 105: goto st43;
	}
	goto st19;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	switch( (*p) ) {
		case 13: goto tr42;
		case 86: goto st44;
		case 118: goto st44;
	}
	goto st19;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	switch( (*p) ) {
		case 13: goto tr42;
		case 69: goto st45;
		case 101: goto st45;
	}
	goto st19;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	if ( (*p) == 13 )
		goto tr72;
	goto st19;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 69: goto st47;
		case 101: goto st47;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 78: goto st48;
		case 110: goto st48;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 84: goto st49;
		case 116: goto st49;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	switch( (*p) ) {
		case 33: goto st17;
		case 45: goto st50;
		case 46: goto st17;
		case 58: goto tr37;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else if ( (*p) >= 65 )
			goto st17;
	} else
		goto st17;
	goto st0;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 76: goto st51;
		case 84: goto st59;
		case 108: goto st51;
		case 116: goto st59;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 69: goto st52;
		case 101: goto st52;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 78: goto st53;
		case 110: goto st53;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 71: goto st54;
		case 103: goto st54;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 84: goto st55;
		case 116: goto st55;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 72: goto st56;
		case 104: goto st56;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr84;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr85:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st57;
tr84:
#line 71 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st57;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
#line 1499 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr39;
		case 32: goto tr85;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr86;
	goto tr38;
tr86:
#line 48 "http_parser.rl"
	{ parser->data.content_length = 0; }
#line 50 "http_parser.rl"
	{
    parser->data.content_length *= 10;
    parser->data.content_length += ((*p) - '0');
  }
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st58;
tr88:
#line 50 "http_parser.rl"
	{
    parser->data.content_length *= 10;
    parser->data.content_length += ((*p) - '0');
  }
	goto st58;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
#line 1529 "http_parser.c"
	if ( (*p) == 13 )
		goto tr87;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr88;
	goto st19;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 89: goto st60;
		case 121: goto st60;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 80: goto st61;
		case 112: goto st61;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 69: goto st62;
		case 101: goto st62;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr92;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr95:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st63;
tr92:
#line 71 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st63;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
#line 1668 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr94;
		case 32: goto tr95;
	}
	goto tr93;
tr93:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st64;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
#line 1682 "http_parser.c"
	if ( (*p) == 13 )
		goto tr97;
	goto st64;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 75: goto st66;
		case 107: goto st66;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 73: goto st67;
		case 105: goto st67;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 69: goto st68;
		case 101: goto st68;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr101;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr104:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st69;
tr101:
#line 71 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st69;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
#line 1819 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr103;
		case 32: goto tr104;
	}
	goto tr102;
tr102:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st70;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
#line 1833 "http_parser.c"
	if ( (*p) == 13 )
		goto tr106;
	goto st70;
tr31:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st71;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
#line 1845 "http_parser.c"
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 65: goto st72;
		case 97: goto st72;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 66 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 84: goto st73;
		case 116: goto st73;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 69: goto st74;
		case 101: goto st74;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr110;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr113:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st75;
tr110:
#line 71 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st75;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
#line 1975 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr112;
		case 32: goto tr113;
	}
	goto tr111;
tr111:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st76;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
#line 1989 "http_parser.c"
	if ( (*p) == 13 )
		goto tr115;
	goto st76;
tr32:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st77;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
#line 2001 "http_parser.c"
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 79: goto st78;
		case 111: goto st78;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 83: goto st79;
		case 115: goto st79;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 84: goto st80;
		case 116: goto st80;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr119;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr122:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st81;
tr119:
#line 71 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st81;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
#line 2131 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr121;
		case 32: goto tr122;
	}
	goto tr120;
tr120:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st82;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
#line 2145 "http_parser.c"
	if ( (*p) == 13 )
		goto tr124;
	goto st82;
tr33:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st83;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
#line 2157 "http_parser.c"
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 69: goto st84;
		case 101: goto st84;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 70: goto st85;
		case 102: goto st85;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 69: goto st86;
		case 101: goto st86;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 82: goto st87;
		case 114: goto st87;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 69: goto st88;
		case 101: goto st88;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 82: goto st89;
		case 114: goto st89;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr131;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr134:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st90;
tr131:
#line 71 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st90;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
#line 2377 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr133;
		case 32: goto tr134;
	}
	goto tr132;
tr132:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st91;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
#line 2391 "http_parser.c"
	if ( (*p) == 13 )
		goto tr136;
	goto st91;
tr34:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st92;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
#line 2403 "http_parser.c"
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 83: goto st93;
		case 115: goto st93;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 69: goto st94;
		case 101: goto st94;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 82: goto st95;
		case 114: goto st95;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
	switch( (*p) ) {
		case 33: goto st17;
		case 45: goto st96;
		case 46: goto st17;
		case 58: goto tr37;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 48 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else if ( (*p) >= 65 )
			goto st17;
	} else
		goto st17;
	goto st0;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 65: goto st97;
		case 97: goto st97;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 66 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 71: goto st98;
		case 103: goto st98;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 69: goto st99;
		case 101: goto st99;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 78: goto st100;
		case 110: goto st100;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr37;
		case 84: goto st101;
		case 116: goto st101;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr146;
		case 124: goto st17;
		case 126: goto st17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st17;
		} else if ( (*p) >= 35 )
			goto st17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st17;
		} else
			goto st17;
	} else
		goto st17;
	goto st0;
tr149:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st102;
tr146:
#line 71 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st102;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
#line 2710 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr148;
		case 32: goto tr149;
	}
	goto tr147;
tr147:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st103;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
#line 2724 "http_parser.c"
	if ( (*p) == 13 )
		goto tr151;
	goto st103;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
	if ( (*p) == 13 )
		goto tr152;
	goto st0;
tr16:
#line 19 "http_parser.rl"
	{ ASSIGN_FIELD(request_uri, p); }
	goto st105;
tr166:
#line 37 "http_parser.rl"
	{ ASSIGN_FIELD(request_path, p); }
#line 19 "http_parser.rl"
	{ ASSIGN_FIELD(request_uri, p); }
	goto st105;
tr177:
#line 17 "http_parser.rl"
	{ parser->mark_query = (byte_pos)(p - buffer); }
#line 39 "http_parser.rl"
	{
    parser->data.query.from = parser->mark_query;
    parser->data.query.to = (byte_pos)(p - buffer);
  }
#line 19 "http_parser.rl"
	{ ASSIGN_FIELD(request_uri, p); }
	goto st105;
tr181:
#line 39 "http_parser.rl"
	{
    parser->data.query.from = parser->mark_query;
    parser->data.query.to = (byte_pos)(p - buffer);
  }
#line 19 "http_parser.rl"
	{ ASSIGN_FIELD(request_uri, p); }
	goto st105;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
#line 2769 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr154;
		case 37: goto tr155;
		case 60: goto st0;
		case 62: goto st0;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 34 <= (*p) && (*p) <= 35 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto tr153;
tr153:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st106;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
#line 2791 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr157;
		case 37: goto st107;
		case 60: goto st0;
		case 62: goto st0;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 34 <= (*p) && (*p) <= 35 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st106;
tr155:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st107;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
#line 2813 "http_parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st108;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st108;
	} else
		goto st108;
	goto st0;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st106;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st106;
	} else
		goto st106;
	goto st0;
tr12:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st109;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
#line 2844 "http_parser.c"
	switch( (*p) ) {
		case 43: goto st109;
		case 58: goto st110;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st109;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st109;
		} else if ( (*p) >= 65 )
			goto st109;
	} else
		goto st109;
	goto st0;
tr14:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st110;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
#line 2869 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr15;
		case 34: goto st0;
		case 35: goto tr16;
		case 37: goto st111;
		case 60: goto st0;
		case 62: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st110;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st112;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st112;
	} else
		goto st112;
	goto st0;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st110;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st110;
	} else
		goto st110;
	goto st0;
tr13:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st113;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
#line 2916 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr165;
		case 34: goto st0;
		case 35: goto tr166;
		case 37: goto st114;
		case 59: goto tr168;
		case 60: goto st0;
		case 62: goto st0;
		case 63: goto tr169;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st113;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st115;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st115;
	} else
		goto st115;
	goto st0;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st113;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st113;
	} else
		goto st113;
	goto st0;
tr168:
#line 37 "http_parser.rl"
	{ ASSIGN_FIELD(request_path, p); }
	goto st116;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
#line 2965 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr15;
		case 34: goto st0;
		case 35: goto tr16;
		case 37: goto st117;
		case 60: goto st0;
		case 62: goto st0;
		case 63: goto st119;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st116;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st118;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st118;
	} else
		goto st118;
	goto st0;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st116;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st116;
	} else
		goto st116;
	goto st0;
tr169:
#line 37 "http_parser.rl"
	{ ASSIGN_FIELD(request_path, p); }
	goto st119;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
#line 3013 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr176;
		case 34: goto st0;
		case 35: goto tr177;
		case 37: goto tr178;
		case 60: goto st0;
		case 62: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr175;
tr175:
#line 17 "http_parser.rl"
	{ parser->mark_query = (byte_pos)(p - buffer); }
	goto st120;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
#line 3034 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr180;
		case 34: goto st0;
		case 35: goto tr181;
		case 37: goto st121;
		case 60: goto st0;
		case 62: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st120;
tr178:
#line 17 "http_parser.rl"
	{ parser->mark_query = (byte_pos)(p - buffer); }
	goto st121;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
#line 3055 "http_parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st122;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st122;
	} else
		goto st122;
	goto st0;
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st120;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st120;
	} else
		goto st120;
	goto st0;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st124;
		case 95: goto st124;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st124;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st124;
	} else
		goto st124;
	goto st0;
st124:
	if ( ++p == pe )
		goto _test_eof124;
case 124:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st125;
		case 95: goto st125;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st125;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st125;
	} else
		goto st125;
	goto st0;
st125:
	if ( ++p == pe )
		goto _test_eof125;
case 125:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st126;
		case 95: goto st126;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st126;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st126;
	} else
		goto st126;
	goto st0;
st126:
	if ( ++p == pe )
		goto _test_eof126;
case 126:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st127;
		case 95: goto st127;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st127;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st127;
	} else
		goto st127;
	goto st0;
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st128;
		case 95: goto st128;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st128;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st128;
	} else
		goto st128;
	goto st0;
st128:
	if ( ++p == pe )
		goto _test_eof128;
case 128:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st129;
		case 95: goto st129;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st129;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st129;
	} else
		goto st129;
	goto st0;
st129:
	if ( ++p == pe )
		goto _test_eof129;
case 129:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st130;
		case 95: goto st130;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st130;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st130;
	} else
		goto st130;
	goto st0;
st130:
	if ( ++p == pe )
		goto _test_eof130;
case 130:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st131;
		case 95: goto st131;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st131;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st131;
	} else
		goto st131;
	goto st0;
st131:
	if ( ++p == pe )
		goto _test_eof131;
case 131:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st132;
		case 95: goto st132;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st132;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st132;
	} else
		goto st132;
	goto st0;
st132:
	if ( ++p == pe )
		goto _test_eof132;
case 132:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st133;
		case 95: goto st133;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st133;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st133;
	} else
		goto st133;
	goto st0;
st133:
	if ( ++p == pe )
		goto _test_eof133;
case 133:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st134;
		case 95: goto st134;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st134;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st134;
	} else
		goto st134;
	goto st0;
st134:
	if ( ++p == pe )
		goto _test_eof134;
case 134:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st135;
		case 95: goto st135;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st135;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st135;
	} else
		goto st135;
	goto st0;
st135:
	if ( ++p == pe )
		goto _test_eof135;
case 135:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st136;
		case 95: goto st136;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st136;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st136;
	} else
		goto st136;
	goto st0;
st136:
	if ( ++p == pe )
		goto _test_eof136;
case 136:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st137;
		case 95: goto st137;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st137;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st137;
	} else
		goto st137;
	goto st0;
st137:
	if ( ++p == pe )
		goto _test_eof137;
case 137:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st138;
		case 95: goto st138;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st138;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st138;
	} else
		goto st138;
	goto st0;
st138:
	if ( ++p == pe )
		goto _test_eof138;
case 138:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st139;
		case 95: goto st139;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st139;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st139;
	} else
		goto st139;
	goto st0;
st139:
	if ( ++p == pe )
		goto _test_eof139;
case 139:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st140;
		case 95: goto st140;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st140;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st140;
	} else
		goto st140;
	goto st0;
st140:
	if ( ++p == pe )
		goto _test_eof140;
case 140:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st141;
		case 95: goto st141;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st141;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st141;
	} else
		goto st141;
	goto st0;
st141:
	if ( ++p == pe )
		goto _test_eof141;
case 141:
	if ( (*p) == 32 )
		goto tr9;
	goto st0;
tr2:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st142;
st142:
	if ( ++p == pe )
		goto _test_eof142;
case 142:
#line 3417 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st123;
		case 79: goto st143;
		case 95: goto st123;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st123;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st123;
	} else
		goto st123;
	goto st0;
st143:
	if ( ++p == pe )
		goto _test_eof143;
case 143:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st124;
		case 78: goto st144;
		case 95: goto st124;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st124;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st124;
	} else
		goto st124;
	goto st0;
st144:
	if ( ++p == pe )
		goto _test_eof144;
case 144:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st125;
		case 78: goto st145;
		case 95: goto st125;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st125;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st125;
	} else
		goto st125;
	goto st0;
st145:
	if ( ++p == pe )
		goto _test_eof145;
case 145:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st126;
		case 69: goto st146;
		case 95: goto st126;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st126;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st126;
	} else
		goto st126;
	goto st0;
st146:
	if ( ++p == pe )
		goto _test_eof146;
case 146:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st127;
		case 67: goto st147;
		case 95: goto st127;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st127;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st127;
	} else
		goto st127;
	goto st0;
st147:
	if ( ++p == pe )
		goto _test_eof147;
case 147:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st128;
		case 84: goto st148;
		case 95: goto st128;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st128;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st128;
	} else
		goto st128;
	goto st0;
st148:
	if ( ++p == pe )
		goto _test_eof148;
case 148:
	switch( (*p) ) {
		case 32: goto tr208;
		case 36: goto st129;
		case 95: goto st129;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st129;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st129;
	} else
		goto st129;
	goto st0;
tr3:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st149;
st149:
	if ( ++p == pe )
		goto _test_eof149;
case 149:
#line 3554 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st123;
		case 69: goto st150;
		case 95: goto st123;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st123;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st123;
	} else
		goto st123;
	goto st0;
st150:
	if ( ++p == pe )
		goto _test_eof150;
case 150:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st124;
		case 76: goto st151;
		case 95: goto st124;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st124;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st124;
	} else
		goto st124;
	goto st0;
st151:
	if ( ++p == pe )
		goto _test_eof151;
case 151:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st125;
		case 69: goto st152;
		case 95: goto st125;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st125;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st125;
	} else
		goto st125;
	goto st0;
st152:
	if ( ++p == pe )
		goto _test_eof152;
case 152:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st126;
		case 84: goto st153;
		case 95: goto st126;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st126;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st126;
	} else
		goto st126;
	goto st0;
st153:
	if ( ++p == pe )
		goto _test_eof153;
case 153:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st127;
		case 69: goto st154;
		case 95: goto st127;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st127;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st127;
	} else
		goto st127;
	goto st0;
st154:
	if ( ++p == pe )
		goto _test_eof154;
case 154:
	switch( (*p) ) {
		case 32: goto tr214;
		case 36: goto st128;
		case 95: goto st128;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st128;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st128;
	} else
		goto st128;
	goto st0;
tr4:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st155;
st155:
	if ( ++p == pe )
		goto _test_eof155;
case 155:
#line 3672 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st123;
		case 69: goto st156;
		case 95: goto st123;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st123;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st123;
	} else
		goto st123;
	goto st0;
st156:
	if ( ++p == pe )
		goto _test_eof156;
case 156:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st124;
		case 84: goto st157;
		case 95: goto st124;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st124;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st124;
	} else
		goto st124;
	goto st0;
st157:
	if ( ++p == pe )
		goto _test_eof157;
case 157:
	switch( (*p) ) {
		case 32: goto tr217;
		case 36: goto st125;
		case 95: goto st125;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st125;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st125;
	} else
		goto st125;
	goto st0;
tr5:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st158;
st158:
	if ( ++p == pe )
		goto _test_eof158;
case 158:
#line 3733 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st123;
		case 69: goto st159;
		case 95: goto st123;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st123;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st123;
	} else
		goto st123;
	goto st0;
st159:
	if ( ++p == pe )
		goto _test_eof159;
case 159:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st124;
		case 65: goto st160;
		case 95: goto st124;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st124;
	} else if ( (*p) > 57 ) {
		if ( 66 <= (*p) && (*p) <= 90 )
			goto st124;
	} else
		goto st124;
	goto st0;
st160:
	if ( ++p == pe )
		goto _test_eof160;
case 160:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st125;
		case 68: goto st161;
		case 95: goto st125;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st125;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st125;
	} else
		goto st125;
	goto st0;
st161:
	if ( ++p == pe )
		goto _test_eof161;
case 161:
	switch( (*p) ) {
		case 32: goto tr221;
		case 36: goto st126;
		case 95: goto st126;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st126;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st126;
	} else
		goto st126;
	goto st0;
tr6:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st162;
st162:
	if ( ++p == pe )
		goto _test_eof162;
case 162:
#line 3813 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st123;
		case 80: goto st163;
		case 95: goto st123;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st123;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st123;
	} else
		goto st123;
	goto st0;
st163:
	if ( ++p == pe )
		goto _test_eof163;
case 163:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st124;
		case 84: goto st164;
		case 95: goto st124;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st124;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st124;
	} else
		goto st124;
	goto st0;
st164:
	if ( ++p == pe )
		goto _test_eof164;
case 164:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st125;
		case 73: goto st165;
		case 95: goto st125;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st125;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st125;
	} else
		goto st125;
	goto st0;
st165:
	if ( ++p == pe )
		goto _test_eof165;
case 165:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st126;
		case 79: goto st166;
		case 95: goto st126;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st126;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st126;
	} else
		goto st126;
	goto st0;
st166:
	if ( ++p == pe )
		goto _test_eof166;
case 166:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st127;
		case 78: goto st167;
		case 95: goto st127;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st127;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st127;
	} else
		goto st127;
	goto st0;
st167:
	if ( ++p == pe )
		goto _test_eof167;
case 167:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st128;
		case 83: goto st168;
		case 95: goto st128;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st128;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st128;
	} else
		goto st128;
	goto st0;
st168:
	if ( ++p == pe )
		goto _test_eof168;
case 168:
	switch( (*p) ) {
		case 32: goto tr228;
		case 36: goto st129;
		case 95: goto st129;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st129;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st129;
	} else
		goto st129;
	goto st0;
tr7:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st169;
st169:
	if ( ++p == pe )
		goto _test_eof169;
case 169:
#line 3950 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st123;
		case 79: goto st170;
		case 85: goto st173;
		case 95: goto st123;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st123;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st123;
	} else
		goto st123;
	goto st0;
st170:
	if ( ++p == pe )
		goto _test_eof170;
case 170:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st124;
		case 83: goto st171;
		case 95: goto st124;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st124;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st124;
	} else
		goto st124;
	goto st0;
st171:
	if ( ++p == pe )
		goto _test_eof171;
case 171:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st125;
		case 84: goto st172;
		case 95: goto st125;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st125;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st125;
	} else
		goto st125;
	goto st0;
st172:
	if ( ++p == pe )
		goto _test_eof172;
case 172:
	switch( (*p) ) {
		case 32: goto tr233;
		case 36: goto st126;
		case 95: goto st126;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st126;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st126;
	} else
		goto st126;
	goto st0;
st173:
	if ( ++p == pe )
		goto _test_eof173;
case 173:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st124;
		case 84: goto st174;
		case 95: goto st124;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st124;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st124;
	} else
		goto st124;
	goto st0;
st174:
	if ( ++p == pe )
		goto _test_eof174;
case 174:
	switch( (*p) ) {
		case 32: goto tr235;
		case 36: goto st125;
		case 95: goto st125;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st125;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st125;
	} else
		goto st125;
	goto st0;
tr8:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st175;
st175:
	if ( ++p == pe )
		goto _test_eof175;
case 175:
#line 4068 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st123;
		case 82: goto st176;
		case 95: goto st123;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st123;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st123;
	} else
		goto st123;
	goto st0;
st176:
	if ( ++p == pe )
		goto _test_eof176;
case 176:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st124;
		case 65: goto st177;
		case 95: goto st124;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st124;
	} else if ( (*p) > 57 ) {
		if ( 66 <= (*p) && (*p) <= 90 )
			goto st124;
	} else
		goto st124;
	goto st0;
st177:
	if ( ++p == pe )
		goto _test_eof177;
case 177:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st125;
		case 67: goto st178;
		case 95: goto st125;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st125;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st125;
	} else
		goto st125;
	goto st0;
st178:
	if ( ++p == pe )
		goto _test_eof178;
case 178:
	switch( (*p) ) {
		case 32: goto tr9;
		case 36: goto st126;
		case 69: goto st179;
		case 95: goto st126;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st126;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st126;
	} else
		goto st126;
	goto st0;
st179:
	if ( ++p == pe )
		goto _test_eof179;
case 179:
	switch( (*p) ) {
		case 32: goto tr240;
		case 36: goto st127;
		case 95: goto st127;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st127;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st127;
	} else
		goto st127;
	goto st0;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof180: cs = 180; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof25: cs = 25; goto _test_eof; 
	_test_eof26: cs = 26; goto _test_eof; 
	_test_eof27: cs = 27; goto _test_eof; 
	_test_eof28: cs = 28; goto _test_eof; 
	_test_eof29: cs = 29; goto _test_eof; 
	_test_eof30: cs = 30; goto _test_eof; 
	_test_eof31: cs = 31; goto _test_eof; 
	_test_eof32: cs = 32; goto _test_eof; 
	_test_eof33: cs = 33; goto _test_eof; 
	_test_eof34: cs = 34; goto _test_eof; 
	_test_eof35: cs = 35; goto _test_eof; 
	_test_eof36: cs = 36; goto _test_eof; 
	_test_eof37: cs = 37; goto _test_eof; 
	_test_eof38: cs = 38; goto _test_eof; 
	_test_eof39: cs = 39; goto _test_eof; 
	_test_eof40: cs = 40; goto _test_eof; 
	_test_eof41: cs = 41; goto _test_eof; 
	_test_eof42: cs = 42; goto _test_eof; 
	_test_eof43: cs = 43; goto _test_eof; 
	_test_eof44: cs = 44; goto _test_eof; 
	_test_eof45: cs = 45; goto _test_eof; 
	_test_eof46: cs = 46; goto _test_eof; 
	_test_eof47: cs = 47; goto _test_eof; 
	_test_eof48: cs = 48; goto _test_eof; 
	_test_eof49: cs = 49; goto _test_eof; 
	_test_eof50: cs = 50; goto _test_eof; 
	_test_eof51: cs = 51; goto _test_eof; 
	_test_eof52: cs = 52; goto _test_eof; 
	_test_eof53: cs = 53; goto _test_eof; 
	_test_eof54: cs = 54; goto _test_eof; 
	_test_eof55: cs = 55; goto _test_eof; 
	_test_eof56: cs = 56; goto _test_eof; 
	_test_eof57: cs = 57; goto _test_eof; 
	_test_eof58: cs = 58; goto _test_eof; 
	_test_eof59: cs = 59; goto _test_eof; 
	_test_eof60: cs = 60; goto _test_eof; 
	_test_eof61: cs = 61; goto _test_eof; 
	_test_eof62: cs = 62; goto _test_eof; 
	_test_eof63: cs = 63; goto _test_eof; 
	_test_eof64: cs = 64; goto _test_eof; 
	_test_eof65: cs = 65; goto _test_eof; 
	_test_eof66: cs = 66; goto _test_eof; 
	_test_eof67: cs = 67; goto _test_eof; 
	_test_eof68: cs = 68; goto _test_eof; 
	_test_eof69: cs = 69; goto _test_eof; 
	_test_eof70: cs = 70; goto _test_eof; 
	_test_eof71: cs = 71; goto _test_eof; 
	_test_eof72: cs = 72; goto _test_eof; 
	_test_eof73: cs = 73; goto _test_eof; 
	_test_eof74: cs = 74; goto _test_eof; 
	_test_eof75: cs = 75; goto _test_eof; 
	_test_eof76: cs = 76; goto _test_eof; 
	_test_eof77: cs = 77; goto _test_eof; 
	_test_eof78: cs = 78; goto _test_eof; 
	_test_eof79: cs = 79; goto _test_eof; 
	_test_eof80: cs = 80; goto _test_eof; 
	_test_eof81: cs = 81; goto _test_eof; 
	_test_eof82: cs = 82; goto _test_eof; 
	_test_eof83: cs = 83; goto _test_eof; 
	_test_eof84: cs = 84; goto _test_eof; 
	_test_eof85: cs = 85; goto _test_eof; 
	_test_eof86: cs = 86; goto _test_eof; 
	_test_eof87: cs = 87; goto _test_eof; 
	_test_eof88: cs = 88; goto _test_eof; 
	_test_eof89: cs = 89; goto _test_eof; 
	_test_eof90: cs = 90; goto _test_eof; 
	_test_eof91: cs = 91; goto _test_eof; 
	_test_eof92: cs = 92; goto _test_eof; 
	_test_eof93: cs = 93; goto _test_eof; 
	_test_eof94: cs = 94; goto _test_eof; 
	_test_eof95: cs = 95; goto _test_eof; 
	_test_eof96: cs = 96; goto _test_eof; 
	_test_eof97: cs = 97; goto _test_eof; 
	_test_eof98: cs = 98; goto _test_eof; 
	_test_eof99: cs = 99; goto _test_eof; 
	_test_eof100: cs = 100; goto _test_eof; 
	_test_eof101: cs = 101; goto _test_eof; 
	_test_eof102: cs = 102; goto _test_eof; 
	_test_eof103: cs = 103; goto _test_eof; 
	_test_eof104: cs = 104; goto _test_eof; 
	_test_eof105: cs = 105; goto _test_eof; 
	_test_eof106: cs = 106; goto _test_eof; 
	_test_eof107: cs = 107; goto _test_eof; 
	_test_eof108: cs = 108; goto _test_eof; 
	_test_eof109: cs = 109; goto _test_eof; 
	_test_eof110: cs = 110; goto _test_eof; 
	_test_eof111: cs = 111; goto _test_eof; 
	_test_eof112: cs = 112; goto _test_eof; 
	_test_eof113: cs = 113; goto _test_eof; 
	_test_eof114: cs = 114; goto _test_eof; 
	_test_eof115: cs = 115; goto _test_eof; 
	_test_eof116: cs = 116; goto _test_eof; 
	_test_eof117: cs = 117; goto _test_eof; 
	_test_eof118: cs = 118; goto _test_eof; 
	_test_eof119: cs = 119; goto _test_eof; 
	_test_eof120: cs = 120; goto _test_eof; 
	_test_eof121: cs = 121; goto _test_eof; 
	_test_eof122: cs = 122; goto _test_eof; 
	_test_eof123: cs = 123; goto _test_eof; 
	_test_eof124: cs = 124; goto _test_eof; 
	_test_eof125: cs = 125; goto _test_eof; 
	_test_eof126: cs = 126; goto _test_eof; 
	_test_eof127: cs = 127; goto _test_eof; 
	_test_eof128: cs = 128; goto _test_eof; 
	_test_eof129: cs = 129; goto _test_eof; 
	_test_eof130: cs = 130; goto _test_eof; 
	_test_eof131: cs = 131; goto _test_eof; 
	_test_eof132: cs = 132; goto _test_eof; 
	_test_eof133: cs = 133; goto _test_eof; 
	_test_eof134: cs = 134; goto _test_eof; 
	_test_eof135: cs = 135; goto _test_eof; 
	_test_eof136: cs = 136; goto _test_eof; 
	_test_eof137: cs = 137; goto _test_eof; 
	_test_eof138: cs = 138; goto _test_eof; 
	_test_eof139: cs = 139; goto _test_eof; 
	_test_eof140: cs = 140; goto _test_eof; 
	_test_eof141: cs = 141; goto _test_eof; 
	_test_eof142: cs = 142; goto _test_eof; 
	_test_eof143: cs = 143; goto _test_eof; 
	_test_eof144: cs = 144; goto _test_eof; 
	_test_eof145: cs = 145; goto _test_eof; 
	_test_eof146: cs = 146; goto _test_eof; 
	_test_eof147: cs = 147; goto _test_eof; 
	_test_eof148: cs = 148; goto _test_eof; 
	_test_eof149: cs = 149; goto _test_eof; 
	_test_eof150: cs = 150; goto _test_eof; 
	_test_eof151: cs = 151; goto _test_eof; 
	_test_eof152: cs = 152; goto _test_eof; 
	_test_eof153: cs = 153; goto _test_eof; 
	_test_eof154: cs = 154; goto _test_eof; 
	_test_eof155: cs = 155; goto _test_eof; 
	_test_eof156: cs = 156; goto _test_eof; 
	_test_eof157: cs = 157; goto _test_eof; 
	_test_eof158: cs = 158; goto _test_eof; 
	_test_eof159: cs = 159; goto _test_eof; 
	_test_eof160: cs = 160; goto _test_eof; 
	_test_eof161: cs = 161; goto _test_eof; 
	_test_eof162: cs = 162; goto _test_eof; 
	_test_eof163: cs = 163; goto _test_eof; 
	_test_eof164: cs = 164; goto _test_eof; 
	_test_eof165: cs = 165; goto _test_eof; 
	_test_eof166: cs = 166; goto _test_eof; 
	_test_eof167: cs = 167; goto _test_eof; 
	_test_eof168: cs = 168; goto _test_eof; 
	_test_eof169: cs = 169; goto _test_eof; 
	_test_eof170: cs = 170; goto _test_eof; 
	_test_eof171: cs = 171; goto _test_eof; 
	_test_eof172: cs = 172; goto _test_eof; 
	_test_eof173: cs = 173; goto _test_eof; 
	_test_eof174: cs = 174; goto _test_eof; 
	_test_eof175: cs = 175; goto _test_eof; 
	_test_eof176: cs = 176; goto _test_eof; 
	_test_eof177: cs = 177; goto _test_eof; 
	_test_eof178: cs = 178; goto _test_eof; 
	_test_eof179: cs = 179; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 153 "http_parser.rl"

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
