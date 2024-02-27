GC=gcc
GCFLAGS=-Wall -g

all: shell

shell: main.o fonctions.o
	$(GC) $(GCFLAGS) -g -o shell  main.o fonctions.o


fonctions.o: fonctions.c fonctions.h
	$(GC) $(GCFLAGS) -g -c fonctions.c

main.o: main.c fonctions.h
	$(GC) $(GCFLAGS) -g -c main.c


clean:
	rm -f *.o

vclean: clean
	rm -f shell