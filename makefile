SRCDIR = src
BINDIR = bin
LIBDIR = lib
INCLUDEDIR = include
CC = gcc
AR = ar

CFLAGS=-Wall -pedantic -I$(INCLUDEDIR)
LDFLAGS=-L$(LIBDIR)

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

all : $(SRCDIR)/reseau.o

clean : 
		rm -rf ./$(BINDIR)/*
		rm -rf ./$(SRCDIR)/*.o
		rm -rf ./$(LIBDIR)/*.a
