all: server_uv server

server_uv: server_uv.c http_parser.cc http_parser.h Makefile
	g++ -std=c++0x -D_GNU_SOURCE -I../../libuv/include -L../../libuv -o server_uv server_uv.c http_parser.cc -luv -pthread -lrt

#server: server.c http_parser.c http_parser.h Makefile
#	g++ -o server -O2 -D_GNU_SOURCE server.c http_parser.c -pthread 

#http_parser.o: http_parser.c http_parser.h Makefile
#	cc -c http_parser.c

http_parser.cc: http_parser.rl http_parser_common.rl Makefile
	ragel -G2 -o http_parser.cc -C http_parser.rl
