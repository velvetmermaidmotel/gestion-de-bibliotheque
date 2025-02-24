CC = gcc
CFLAGS = -Wall -g

# par défaut hash table
USE_HASH_TABLE = 1

# Object files
OBJ = main.o biblioH.o biblioLC.o entreeSortieLC.o entreeSortieH.o

# Executable file
EXEC = main

# program
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ)

# Compilation pour biblioH
biblioH.o: biblioH.c biblioH.h
	$(CC) $(CFLAGS) -c biblioH.c

# Compilation pour biblioLC
biblioLC.o: biblioLC.c biblioLC.h
	$(CC) $(CFLAGS) -c biblioLC.c

# Compilation pour entreeSortieLC
entreeSortieLC.o: entreeSortieLC.c entreeSortieLC.h
	$(CC) $(CFLAGS) -c entreeSortieLC.c

# Compilation pour entreeSortieH
entreeSortieH.o: entreeSortieH.c entreeSortieH.h
	$(CC) $(CFLAGS) -c entreeSortieH.c

# Compilation rule for main
main.o: main.c biblioH.h biblioLC.h entreeSortieH.h
	$(CC) $(CFLAGS) -c main.c

# clean le projet
clean:
	rm -f $(OBJ) $(EXEC)

