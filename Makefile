#####################################################################
# Phillip Sime
#
# CS 442 : Symbol Table
#
#####################################################################
#
# Type "make" or "make all" to compile your code
# Type "make clean" to remove the executable (and any object files)
#
#####################################################################

CC=gcc
CFLAGS=-Wall -g

all: SymTab

SymTab: SymTab.c SymTab.h
	$(CC) -o SymTab $(CFLAGS) SymTab.c

clean:
	$(RM) symtab *.o
	$(RM) -rf *.dSYM