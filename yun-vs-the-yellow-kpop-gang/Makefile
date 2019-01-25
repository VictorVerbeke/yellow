EXEC = yun
SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)
CC = g++
CFLAGS = -Wall -g -std=c++11
CLIBS = -L/usr/local/include/SFML -lsfml-graphics  -lsfml-window -lsfml-system -lsfml-audio
INCDIR = -I/usr/local/include/SFML

all: $(EXEC)

install: $(EXEC)
	echo "Installing 'Yun vs The Yellow K-Pop Gang...'"
	cp $(EXEC) /usr/local/bin/
	mkdir /usr/local/lib/yun-vs-the-yellow-kpop-gang/
	mkdir /usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/
	cp -r fonts/ /usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/fonts/
	cp -r images/ /usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/images/
	cp -r sounds/ /usr/local/lib/yun-vs-the-yellow-kpop-gang/assets/sounds/
	echo "Done! You can now run it by running '$ yun' from anywhere inside your system."

uninstall:
	echo "Uninstalling 'Yun vs The Yellow K-Pop Gang...'"
	rm -rf /usr/local/bin/$(EXEC)
	rm -rf /usr/local/lib/yun-vs-the-yellow-kpop-gang/
	echo "Done! The game is now uninstalled from your computer."

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(CLIBS) -o $(EXEC)

%.o: %.cc
	$(CC) $(CFLAGS) $(INCDIR)  -c $<

clean:
	rm -f $(OBJECTS) $(EXEC)

.PHONY: all clean
