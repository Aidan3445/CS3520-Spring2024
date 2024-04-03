CC = g++
CFLAGS= -I$(IDIR) -g -O0 -std=c++14

SRCDIR = .
INCDIR = include
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(SOURCES))
EXECUTABLE = main

$(shell mkdir -p $(BINDIR))
$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.PHONY: clean

clean:
	rm -rf $(BINDIR) $(EXECUTABLE) DebugT-1 DebugT-2 DebugT-3 DebugT-4 DebugT-5 

