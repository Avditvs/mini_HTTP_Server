SRCDIR = src
BINDIR = bin
LIBDIR = lib
INCLUDEDIR = include
CC = gcc
AR = ar

CFLAGS=-Wall -pedantic -I$(INCLUDEDIR)
LDFLAGS=-L$(LIBDIR)



clean : 
		rm -rf ./$(BINDIR)/*
		rm -rf ./$(SRCDIR)/*.o
		rm -rf ./$(LIBDIR)/*.a
