SHELL:=/bin/bash
EXEC = yun
SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)
CC = g++
CFLAGS = -Wall -g -std=c++11
CLIBS = -L/usr/local/include/SFML -lsfml-graphics  -lsfml-window -lsfml-system -lsfml-audio
INCDIR = -I/usr/local/include/SFML

UNINSTALLING_STRING =

all: install

install: $(EXEC)
	echo -e "\x1b[33mInstalling 'Yun vs The Yellow K-Pop Gang...'\x1b[0m"
	cp $(EXEC) /usr/local/bin/
	mkdir /usr/local/lib/yun-vs-the-yellow-kpop-gang/
	mkdir /usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/
	cp -r fonts/ /usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/fonts/
	cp -r images/ /usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/
	cp -r sounds/ /usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/sounds/
	echo -e "\x1b[33mDone! You can now run it by running '$$ yun' from anywhere inside your system.\x1b[0m"

uninstall:
	@echo -e "\x1b[33mUninstalling 'Yun vs The Yellow K-Pop Gang...'\x1b[0m"
	rm -rf /usr/local/bin/$(EXEC)
	rm -rf /usr/local/lib/yun-vs-the-yellow-kpop-gang/
	echo -e "\x1b[33mDone! The game is now uninstalled from your computer.\x1b[0m"

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(CLIBS) -o $(EXEC)

%.o: %.cc
	$(CC) $(CFLAGS) $(INCDIR)  -c $<

clean:
	rm -f $(OBJECTS) $(EXEC)

.PHONY: all clean install uninstall
