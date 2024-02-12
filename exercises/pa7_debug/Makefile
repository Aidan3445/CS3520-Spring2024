IDIR =../include
CC=g++ -std=c++11
CFLAGS= -I$(IDIR) -g -O0

ODIR=.

LIBS=-lncurses

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ1 = 2d_dynamic.o
_OBJ2 = 3dmatrix.o
_OBJ3 = charptr.o
_OBJ4 = practice_1.o
_OBJ5 = practice_2.o
_OBJ6 = struct.o

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: 2d_dynamic 3dmatrix charptr practice_1 practice_2 struct

	
2d_dynamic: $(_OBJ1)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

3dmatrix: $(_OBJ2)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

charptr: $(_OBJ3)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

practice_1: $(_OBJ4)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

practice_2: $(_OBJ5)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

struct: $(_OBJ6)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *~ core $(INCDIR)/*~ 
	rm -f 2d_dynamic
	rm -f 3dmatrix
	rm -f charptr
	rm -f practice_1
	rm -f practice_2
	rm -f struct
	rm -f *.o

etags: 
	find . -type f -iname "*.[ch]" | xargs etags --append 