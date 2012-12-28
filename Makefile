server: server.c http_parser.c http_parser.h Makefile
	g++ -o server -O2 -D_GNU_SOURCE server.c http_parser.c -pthread 

http_parser.o: http_parser.c http_parser.h Makefile
	cc -c http_parser.c

main: main.c
	gcc  -D_GNU_SOURCE -I../../libuv/include -L../../libuv main.c -luv -pthread -lrt

http_parser.c: http_parser.rl http_parser_common.rl Makefile
	ragel -G2 -C http_parser.rl
