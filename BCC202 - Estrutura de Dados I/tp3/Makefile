# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -g
TARGET = exe

# Arquivos objeto
OBJS = filaprocessos.o tp.o

# Alvo principal
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	rm -r *.o

# Regras para objetos (.o)
filaprocessos.o: filaprocessos.c filaprocessos.h
	$(CC) $(CFLAGS) -c filaprocessos.c

tp.o: tp.c
	$(CC) $(CFLAGS) -c tp.c