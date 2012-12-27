http_parser.o: http_parser.c http_parser.h Makefile
	cc -c http_parser.c

http_parser.c: http_parser.rl Makefile
	ragel -G2 -C http_parser.rl


main: main.c
	gcc -D_GNU_SOURCE -I../../libuv/include -L../../libuv main.c -luv -pthread -lrt
