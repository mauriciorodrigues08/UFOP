all: pratica.o hash.o
	@gcc pratica.o hash.o -o exe -lm
	@rm -r pratica.o hash.o
hash.o: hash.c
	@gcc hash.c -c -Wall
pratica.o: pratica.c
	@gcc pratica.c -c -Wall
run:
	@./exe
val:
	@gcc -g -o exeval hash.c pratica.c -Wall
valrun: val
	@valgrind --leak-check=full --track-origins=yes -s ./exeval

