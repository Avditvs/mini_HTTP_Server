SRCDIR = src
BINDIR = bin
LIBDIR = lib
INCLUDEDIR = include
CC = gcc
AR = ar
EXEC = server

OFILES = $(SRCDIR)/reseau.o $(SRCDIR)/traitement.o $(SRCDIR)/serveur.o 

CFLAGS=-Wall -pedantic -I$(INCLUDEDIR)
LDFLAGS=-L$(LIBDIR) -I$(INCLUDEDIR)

$(BINDIR)/$(EXEC) : $(OFILES)
	mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) -o $@ $(OFILES)

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

all : clean $(BINDIR)/$(EXEC)

clean : 
		rm -rf ./$(BINDIR)/*
		rm -rf ./$(SRCDIR)/*.o
		rm -rf ./$(LIBDIR)/*.a
