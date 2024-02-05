CC = g++
CFLAGS= -I$(IDIR) -g -O0 -std=c++11

SRCDIR = src
INCDIR = include
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(SOURCES))
EXECUTABLE = main

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.PHONY: clean

clean:
	rm -f $(BINDIR)/*.o $(EXECUTABLE)

