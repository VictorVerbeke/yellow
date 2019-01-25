EXEC = testing
SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)
CC = g++
CFLAGS = -Wall -g -std=c++11
CLIBS = -L/usr/local/include/SFML -lsfml-graphics  -lsfml-window -lsfml-system
INCDIR = -I/usr/local/include/SFML

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(CLIBS) -o $(EXEC)

%.o: %.cc
	$(CC) $(CFLAGS) $(INCDIR)  -c $<

clean:
	rm -f $(OBJECTS) $(EXEC)

.PHONY: all clean
