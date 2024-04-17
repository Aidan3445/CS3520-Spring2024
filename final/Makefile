CC = g++
CFLAGS = -I$(INCDIR) -g -O0 -std=c++17

SRCDIR = src
INCDIR = include
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(SOURCES))
EXECUTABLE = main

# Make sure the $(BINDIR) exists before compiling anything
$(shell mkdir -p $(BINDIR))

all: $(EXECUTABLE)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.PHONY: clean debug

clean:
	rm -rf $(BINDIR) $(EXECUTABLE)

debug: CFLAGS += -DDEBUG 
debug: $(EXECUTABLE)

