# Definindo o compilador
CC = gcc

# Definindo as flags de compilação
CFLAGS = -Wall -g

# Definindo os arquivos objeto
OBJ = main.o PQ.o

# Nome do executável
EXEC = trab1

# Regra para compilar o programa
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Regra para compilar main.c
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# Regra para compilar PQ.c
PQ.o: PQ.c
	$(CC) $(CFLAGS) -c PQ.c

# Regra para limpar os arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC)