CC = gcc
Cfiles := src/card/card.c
Cfiles += src/terminal/terminal.c
Cfiles += src/server/server.c
Cfiles += src/app/app.c
Cfiles += main.c
 
.PHONY: all clean

all:
	$(CC) $(files) -o main.exe

clean:
	rm -f *.o main.exe
