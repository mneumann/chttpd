
#line 1 "http_parser.rl"
/**
 * Copyright (c) 2005 Zed A. Shaw
 * You can redistribute it and/or modify it under the same terms as Ruby.
 *
 * Copyright (c) 2012 by Michael Neumann (mneumann@ntecs.de)
 */

// compile with ragel -G2 -C ...

/** Machine **/


#line 72 "http_parser.rl"


/** Data **/

#line 21 "http_parser.c"
static const int http_parser_start = 1;
static const int http_parser_first_final = 127;
static const int http_parser_error = 0;

static const int http_parser_en_main = 1;


#line 76 "http_parser.rl"

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
  INIT_RANGE(request_method);
  INIT_RANGE(http_version);
  INIT_RANGE(request_path);
  INIT_RANGE(query);

  data->content_length = -1;

  INIT_RANGE(header_content_type);
  INIT_RANGE(header_date);
  INIT_RANGE(header_host);
  INIT_RANGE(header_user_agent);
  INIT_RANGE(header_referer);
  INIT_RANGE(header_cookie);
  INIT_RANGE(header_connection);

  data->body_start = -1;

  #undef INIT_RANGE
}

void http_parser_init(struct http_parser *parser) {
  int cs = 0;
  
#line 68 "http_parser.c"
	{
	cs = http_parser_start;
	}

#line 114 "http_parser.rl"
  parser->saved_cs = cs;

  http_parser_data_init(&parser->data);
}

byte_pos http_parser_run(struct http_parser *parser,
                         const char *buffer, byte_pos buffer_length, byte_pos buffer_offset) {
  assert(parser);
  assert(buffer);
  assert(buffer_length > 0);
  assert(buffer_offset < buffer_length);

  // Ragel uses: cs, p, pe
  int cs = parser->saved_cs;               // current ragel machine state
  const char *p = buffer;                  // pointer to start of data
  const char *pe = buffer + buffer_length; // pointer to end of data

  
#line 92 "http_parser.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	switch( (*p) ) {
		case 36: goto tr0;
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
#line 123 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr2;
		case 36: goto st108;
		case 95: goto st108;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st108;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st108;
	} else
		goto st108;
	goto st0;
tr2:
#line 21 "http_parser.rl"
	{ ASSIGN_FIELD(request_method, p); }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 146 "http_parser.c"
	switch( (*p) ) {
		case 42: goto tr4;
		case 43: goto tr5;
		case 47: goto tr6;
		case 58: goto tr7;
	}
	if ( (*p) < 65 ) {
		if ( 45 <= (*p) && (*p) <= 57 )
			goto tr5;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr5;
	} else
		goto tr5;
	goto st0;
tr4:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 170 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr8;
		case 35: goto tr9;
	}
	goto st0;
tr8:
#line 19 "http_parser.rl"
	{ ASSIGN_FIELD(request_uri, p); }
	goto st5;
tr132:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 20 "http_parser.rl"
	{ ASSIGN_FIELD(fragment, p); }
	goto st5;
tr135:
#line 20 "http_parser.rl"
	{ ASSIGN_FIELD(fragment, p); }
	goto st5;
tr143:
#line 23 "http_parser.rl"
	{ ASSIGN_FIELD(request_path, p); }
#line 19 "http_parser.rl"
	{ ASSIGN_FIELD(request_uri, p); }
	goto st5;
tr154:
#line 17 "http_parser.rl"
	{ parser->mark_query = (byte_pos)(p - buffer); }
#line 25 "http_parser.rl"
	{
    parser->data.query.from = parser->mark_query;
    parser->data.query.to = (byte_pos)(p - buffer);
  }
#line 19 "http_parser.rl"
	{ ASSIGN_FIELD(request_uri, p); }
	goto st5;
tr158:
#line 25 "http_parser.rl"
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
#line 220 "http_parser.c"
	if ( (*p) == 72 )
		goto tr10;
	goto st0;
tr10:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 232 "http_parser.c"
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
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st11;
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	if ( (*p) == 46 )
		goto st12;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st11;
	goto st0;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st13;
	goto st0;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	if ( (*p) == 13 )
		goto tr18;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st13;
	goto st0;
tr18:
#line 22 "http_parser.rl"
	{	ASSIGN_FIELD(http_version, p); }
	goto st14;
tr31:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr34:
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr48:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 53 "http_parser.rl"
	{ ASSIGN_FIELD(header_connection, p); }
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr51:
#line 53 "http_parser.rl"
	{ ASSIGN_FIELD(header_connection, p); }
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr66:
#line 42 "http_parser.rl"
	{ }
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr73:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 47 "http_parser.rl"
	{ ASSIGN_FIELD(header_content_type, p); }
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr76:
#line 47 "http_parser.rl"
	{ ASSIGN_FIELD(header_content_type, p); }
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr82:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 52 "http_parser.rl"
	{ ASSIGN_FIELD(header_cookie, p); }
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr85:
#line 52 "http_parser.rl"
	{ ASSIGN_FIELD(header_cookie, p); }
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr91:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 48 "http_parser.rl"
	{ ASSIGN_FIELD(header_date, p); }
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr94:
#line 48 "http_parser.rl"
	{ ASSIGN_FIELD(header_date, p); }
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr100:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 49 "http_parser.rl"
	{ ASSIGN_FIELD(header_host, p); }
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr103:
#line 49 "http_parser.rl"
	{ ASSIGN_FIELD(header_host, p); }
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr112:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 51 "http_parser.rl"
	{ ASSIGN_FIELD(header_referer, p); }
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr115:
#line 51 "http_parser.rl"
	{ ASSIGN_FIELD(header_referer, p); }
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr127:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
#line 50 "http_parser.rl"
	{ ASSIGN_FIELD(header_user_agent, p); }
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
tr130:
#line 50 "http_parser.rl"
	{ ASSIGN_FIELD(header_user_agent, p); }
#line 60 "http_parser.rl"
	{
    // XXX: What to do with the other headers? call function?
    //on_field(BytePosRange2(field_name, BytePosRange(mark, cast(BytePos)(fpc - buffer.ptr))));
  }
	goto st14;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
#line 462 "http_parser.c"
	if ( (*p) == 10 )
		goto st15;
	goto st0;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	switch( (*p) ) {
		case 13: goto st16;
		case 33: goto tr21;
		case 67: goto tr22;
		case 68: goto tr23;
		case 72: goto tr24;
		case 82: goto tr25;
		case 85: goto tr26;
		case 99: goto tr22;
		case 100: goto tr23;
		case 104: goto tr24;
		case 114: goto tr25;
		case 117: goto tr26;
		case 124: goto tr21;
		case 126: goto tr21;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr21;
		} else if ( (*p) >= 35 )
			goto tr21;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr21;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr21;
		} else
			goto tr21;
	} else
		goto tr21;
	goto st0;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	if ( (*p) == 10 )
		goto tr27;
	goto st0;
tr27:
#line 65 "http_parser.rl"
	{
    parser->data.body_start = (byte_pos)(p - buffer + 1);
    {p++; cs = 127; goto _out;}
  }
	goto st127;
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
#line 522 "http_parser.c"
	goto st0;
tr21:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 532 "http_parser.c"
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
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
tr32:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st18;
tr29:
#line 55 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 572 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr31;
		case 32: goto tr32;
	}
	goto tr30;
tr30:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 586 "http_parser.c"
	if ( (*p) == 13 )
		goto tr34;
	goto st19;
tr22:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 598 "http_parser.c"
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
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
		case 58: goto tr29;
		case 78: goto st22;
		case 79: goto st51;
		case 110: goto st22;
		case 111: goto st51;
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
		case 58: goto tr29;
		case 78: goto st23;
		case 84: goto st32;
		case 110: goto st23;
		case 116: goto st32;
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
		case 58: goto tr29;
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
		case 58: goto tr29;
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
		case 58: goto tr29;
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
		case 58: goto tr29;
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
		case 58: goto tr29;
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
		case 58: goto tr29;
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
		case 58: goto tr46;
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
tr49:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st30;
tr46:
#line 55 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st30;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
#line 912 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr48;
		case 32: goto tr49;
	}
	goto tr47;
tr47:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st31;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
#line 926 "http_parser.c"
	if ( (*p) == 13 )
		goto tr51;
	goto st31;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 69: goto st33;
		case 101: goto st33;
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
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 78: goto st34;
		case 110: goto st34;
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
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 84: goto st35;
		case 116: goto st35;
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
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
	switch( (*p) ) {
		case 33: goto st17;
		case 45: goto st36;
		case 46: goto st17;
		case 58: goto tr29;
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
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 76: goto st37;
		case 84: goto st45;
		case 108: goto st37;
		case 116: goto st45;
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
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 69: goto st38;
		case 101: goto st38;
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
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 78: goto st39;
		case 110: goto st39;
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
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 71: goto st40;
		case 103: goto st40;
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
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 84: goto st41;
		case 116: goto st41;
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
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 72: goto st42;
		case 104: goto st42;
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
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr63;
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
tr64:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st43;
tr63:
#line 55 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st43;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
#line 1272 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr31;
		case 32: goto tr64;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr65;
	goto tr30;
tr65:
#line 34 "http_parser.rl"
	{ parser->data.content_length = 0; }
#line 36 "http_parser.rl"
	{
    parser->data.content_length *= 10;
    parser->data.content_length += ((*p) - '0');
  }
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st44;
tr67:
#line 36 "http_parser.rl"
	{
    parser->data.content_length *= 10;
    parser->data.content_length += ((*p) - '0');
  }
	goto st44;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
#line 1302 "http_parser.c"
	if ( (*p) == 13 )
		goto tr66;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr67;
	goto st19;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 89: goto st46;
		case 121: goto st46;
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
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 80: goto st47;
		case 112: goto st47;
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
		case 58: goto tr29;
		case 69: goto st48;
		case 101: goto st48;
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
		case 58: goto tr71;
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
tr74:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st49;
tr71:
#line 55 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st49;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
#line 1441 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr73;
		case 32: goto tr74;
	}
	goto tr72;
tr72:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st50;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
#line 1455 "http_parser.c"
	if ( (*p) == 13 )
		goto tr76;
	goto st50;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 75: goto st52;
		case 107: goto st52;
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
		case 58: goto tr29;
		case 73: goto st53;
		case 105: goto st53;
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
		case 58: goto tr29;
		case 69: goto st54;
		case 101: goto st54;
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
		case 58: goto tr80;
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
tr83:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st55;
tr80:
#line 55 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st55;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
#line 1592 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr82;
		case 32: goto tr83;
	}
	goto tr81;
tr81:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st56;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
#line 1606 "http_parser.c"
	if ( (*p) == 13 )
		goto tr85;
	goto st56;
tr23:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st57;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
#line 1618 "http_parser.c"
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 65: goto st58;
		case 97: goto st58;
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
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 84: goto st59;
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
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 69: goto st60;
		case 101: goto st60;
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
		case 58: goto tr89;
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
tr92:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st61;
tr89:
#line 55 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st61;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
#line 1748 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr91;
		case 32: goto tr92;
	}
	goto tr90;
tr90:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st62;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
#line 1762 "http_parser.c"
	if ( (*p) == 13 )
		goto tr94;
	goto st62;
tr24:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st63;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
#line 1774 "http_parser.c"
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 79: goto st64;
		case 111: goto st64;
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
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 83: goto st65;
		case 115: goto st65;
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
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 84: goto st66;
		case 116: goto st66;
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
		case 58: goto tr98;
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
tr101:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st67;
tr98:
#line 55 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st67;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
#line 1904 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr100;
		case 32: goto tr101;
	}
	goto tr99;
tr99:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st68;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
#line 1918 "http_parser.c"
	if ( (*p) == 13 )
		goto tr103;
	goto st68;
tr25:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st69;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
#line 1930 "http_parser.c"
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 69: goto st70;
		case 101: goto st70;
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
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 70: goto st71;
		case 102: goto st71;
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
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 69: goto st72;
		case 101: goto st72;
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
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 82: goto st73;
		case 114: goto st73;
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
		case 58: goto tr29;
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
		case 58: goto tr29;
		case 82: goto st75;
		case 114: goto st75;
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
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
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
	goto st76;
tr110:
#line 55 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st76;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
#line 2150 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr112;
		case 32: goto tr113;
	}
	goto tr111;
tr111:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st77;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
#line 2164 "http_parser.c"
	if ( (*p) == 13 )
		goto tr115;
	goto st77;
tr26:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st78;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
#line 2176 "http_parser.c"
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
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
		case 58: goto tr29;
		case 69: goto st80;
		case 101: goto st80;
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
		case 58: goto tr29;
		case 82: goto st81;
		case 114: goto st81;
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
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	switch( (*p) ) {
		case 33: goto st17;
		case 45: goto st82;
		case 46: goto st17;
		case 58: goto tr29;
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
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 65: goto st83;
		case 97: goto st83;
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
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	switch( (*p) ) {
		case 33: goto st17;
		case 58: goto tr29;
		case 71: goto st84;
		case 103: goto st84;
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
		case 58: goto tr29;
		case 69: goto st85;
		case 101: goto st85;
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
		case 58: goto tr29;
		case 78: goto st86;
		case 110: goto st86;
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
		case 58: goto tr29;
		case 84: goto st87;
		case 116: goto st87;
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
		case 58: goto tr125;
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
tr128:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st88;
tr125:
#line 55 "http_parser.rl"
	{
    parser->field_name.from = parser->mark;
    parser->field_name.to = (byte_pos)(p - buffer);
  }
	goto st88;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
#line 2483 "http_parser.c"
	switch( (*p) ) {
		case 13: goto tr127;
		case 32: goto tr128;
	}
	goto tr126;
tr126:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st89;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
#line 2497 "http_parser.c"
	if ( (*p) == 13 )
		goto tr130;
	goto st89;
tr9:
#line 19 "http_parser.rl"
	{ ASSIGN_FIELD(request_uri, p); }
	goto st90;
tr144:
#line 23 "http_parser.rl"
	{ ASSIGN_FIELD(request_path, p); }
#line 19 "http_parser.rl"
	{ ASSIGN_FIELD(request_uri, p); }
	goto st90;
tr155:
#line 17 "http_parser.rl"
	{ parser->mark_query = (byte_pos)(p - buffer); }
#line 25 "http_parser.rl"
	{
    parser->data.query.from = parser->mark_query;
    parser->data.query.to = (byte_pos)(p - buffer);
  }
#line 19 "http_parser.rl"
	{ ASSIGN_FIELD(request_uri, p); }
	goto st90;
tr159:
#line 25 "http_parser.rl"
	{
    parser->data.query.from = parser->mark_query;
    parser->data.query.to = (byte_pos)(p - buffer);
  }
#line 19 "http_parser.rl"
	{ ASSIGN_FIELD(request_uri, p); }
	goto st90;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
#line 2535 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr132;
		case 37: goto tr133;
		case 60: goto st0;
		case 62: goto st0;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 34 <= (*p) && (*p) <= 35 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto tr131;
tr131:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st91;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
#line 2557 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr135;
		case 37: goto st92;
		case 60: goto st0;
		case 62: goto st0;
		case 127: goto st0;
	}
	if ( (*p) > 31 ) {
		if ( 34 <= (*p) && (*p) <= 35 )
			goto st0;
	} else if ( (*p) >= 0 )
		goto st0;
	goto st91;
tr133:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st92;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
#line 2579 "http_parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st93;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st93;
	} else
		goto st93;
	goto st0;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st91;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st91;
	} else
		goto st91;
	goto st0;
tr5:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st94;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
#line 2610 "http_parser.c"
	switch( (*p) ) {
		case 43: goto st94;
		case 58: goto st95;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st94;
	} else if ( (*p) > 57 ) {
		if ( (*p) > 90 ) {
			if ( 97 <= (*p) && (*p) <= 122 )
				goto st94;
		} else if ( (*p) >= 65 )
			goto st94;
	} else
		goto st94;
	goto st0;
tr7:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st95;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
#line 2635 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr8;
		case 34: goto st0;
		case 35: goto tr9;
		case 37: goto st96;
		case 60: goto st0;
		case 62: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st95;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st97;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st97;
	} else
		goto st97;
	goto st0;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st95;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st95;
	} else
		goto st95;
	goto st0;
tr6:
#line 16 "http_parser.rl"
	{ parser->mark = (byte_pos)(p - buffer); }
	goto st98;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
#line 2682 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr143;
		case 34: goto st0;
		case 35: goto tr144;
		case 37: goto st99;
		case 59: goto tr146;
		case 60: goto st0;
		case 62: goto st0;
		case 63: goto tr147;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st98;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st100;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st100;
	} else
		goto st100;
	goto st0;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st98;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st98;
	} else
		goto st98;
	goto st0;
tr146:
#line 23 "http_parser.rl"
	{ ASSIGN_FIELD(request_path, p); }
	goto st101;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
#line 2731 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr8;
		case 34: goto st0;
		case 35: goto tr9;
		case 37: goto st102;
		case 60: goto st0;
		case 62: goto st0;
		case 63: goto st104;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st101;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st103;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st103;
	} else
		goto st103;
	goto st0;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st101;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st101;
	} else
		goto st101;
	goto st0;
tr147:
#line 23 "http_parser.rl"
	{ ASSIGN_FIELD(request_path, p); }
	goto st104;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
#line 2779 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr154;
		case 34: goto st0;
		case 35: goto tr155;
		case 37: goto tr156;
		case 60: goto st0;
		case 62: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto tr153;
tr153:
#line 17 "http_parser.rl"
	{ parser->mark_query = (byte_pos)(p - buffer); }
	goto st105;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
#line 2800 "http_parser.c"
	switch( (*p) ) {
		case 32: goto tr158;
		case 34: goto st0;
		case 35: goto tr159;
		case 37: goto st106;
		case 60: goto st0;
		case 62: goto st0;
		case 127: goto st0;
	}
	if ( 0 <= (*p) && (*p) <= 31 )
		goto st0;
	goto st105;
tr156:
#line 17 "http_parser.rl"
	{ parser->mark_query = (byte_pos)(p - buffer); }
	goto st106;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
#line 2821 "http_parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st107;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st107;
	} else
		goto st107;
	goto st0;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st105;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto st105;
	} else
		goto st105;
	goto st0;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
	switch( (*p) ) {
		case 32: goto tr2;
		case 36: goto st109;
		case 95: goto st109;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st109;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st109;
	} else
		goto st109;
	goto st0;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
	switch( (*p) ) {
		case 32: goto tr2;
		case 36: goto st110;
		case 95: goto st110;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st110;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st110;
	} else
		goto st110;
	goto st0;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
	switch( (*p) ) {
		case 32: goto tr2;
		case 36: goto st111;
		case 95: goto st111;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st111;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st111;
	} else
		goto st111;
	goto st0;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
	switch( (*p) ) {
		case 32: goto tr2;
		case 36: goto st112;
		case 95: goto st112;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st112;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st112;
	} else
		goto st112;
	goto st0;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
	switch( (*p) ) {
		case 32: goto tr2;
		case 36: goto st113;
		case 95: goto st113;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st113;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st113;
	} else
		goto st113;
	goto st0;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
	switch( (*p) ) {
		case 32: goto tr2;
		case 36: goto st114;
		case 95: goto st114;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st114;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st114;
	} else
		goto st114;
	goto st0;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
	switch( (*p) ) {
		case 32: goto tr2;
		case 36: goto st115;
		case 95: goto st115;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st115;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st115;
	} else
		goto st115;
	goto st0;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
	switch( (*p) ) {
		case 32: goto tr2;
		case 36: goto st116;
		case 95: goto st116;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st116;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st116;
	} else
		goto st116;
	goto st0;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
	switch( (*p) ) {
		case 32: goto tr2;
		case 36: goto st117;
		case 95: goto st117;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st117;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st117;
	} else
		goto st117;
	goto st0;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
	switch( (*p) ) {
		case 32: goto tr2;
		case 36: goto st118;
		case 95: goto st118;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st118;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st118;
	} else
		goto st118;
	goto st0;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
	switch( (*p) ) {
		case 32: goto tr2;
		case 36: goto st119;
		case 95: goto st119;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st119;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st119;
	} else
		goto st119;
	goto st0;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
	switch( (*p) ) {
		case 32: goto tr2;
		case 36: goto st120;
		case 95: goto st120;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st120;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st120;
	} else
		goto st120;
	goto st0;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
	switch( (*p) ) {
		case 32: goto tr2;
		case 36: goto st121;
		case 95: goto st121;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st121;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st121;
	} else
		goto st121;
	goto st0;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
	switch( (*p) ) {
		case 32: goto tr2;
		case 36: goto st122;
		case 95: goto st122;
	}
	if ( (*p) < 48 ) {
		if ( 45 <= (*p) && (*p) <= 46 )
			goto st122;
	} else if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 90 )
			goto st122;
	} else
		goto st122;
	goto st0;
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
	switch( (*p) ) {
		case 32: goto tr2;
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
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
	switch( (*p) ) {
		case 32: goto tr2;
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
		case 32: goto tr2;
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
		case 32: goto tr2;
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
	if ( (*p) == 32 )
		goto tr2;
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
	_test_eof127: cs = 127; goto _test_eof; 
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

	_test_eof: {}
	_out: {}
	}

#line 132 "http_parser.rl"

  assert(p <= pe); // buffer overflow after parsing execute

  parser->saved_cs = cs;

  return (p - buffer); // returns the number of bytes consumed
}

bool http_parser_has_error(const struct http_parser *parser) {
  return (parser->saved_cs == http_parser_error);
}

bool http_parser_is_finished(const struct http_parser *parser) {
  return (parser->saved_cs >= http_parser_first_final);
}
