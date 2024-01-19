IDIR =../include
CC=g++
CFLAGS= -I$(IDIR) -g -O0

ODIR=.

LIBS=-lncurses

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ1 = fig05_06.o
_OBJ2 = paragraphStats.o

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: fig05_06 paragraphStats

	
fig05_06: $(_OBJ1)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *~ core $(INCDIR)/*~ 
	rm -f fig05_06
	rm -f paragraphStats
	rm -f *.o

etags: 
	find . -type f -iname "*.[ch]" | xargs etags --append 
