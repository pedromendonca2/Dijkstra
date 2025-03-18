# Definindo o compilador
CC = gcc

# Definindo as flags de compilação
CFLAGS = -Wall -g

# Definindo os arquivos objeto
OBJ = main.o PQ.o djikstra.o

# Nome do executável
EXEC = trab1

# Regra para compilar o programa
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) -lm
	gcc  -Wall -g aresta.c djikstrainsertionsort.c no.c trab2.c -o trab2 -lm

# Regra para compilar main.c
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# Regra para compilar PQ.c
PQ.o: PQ.c
	$(CC) $(CFLAGS) -c PQ.c

#Regra para compilar Djikstra.c
Djikstra.o: PQ.c
	$(CC) $(CFLAGS) -c djikstra.c

# Regra para limpar os arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC)

run:
	./trab1 casos_teste_v3/caso_teste_medio_1.txt output.txt

run2:
	./trab2 casos_teste_v3/caso_teste_pequeno_1.txt output2.txt