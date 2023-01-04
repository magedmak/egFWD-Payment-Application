CC = gcc
Cfiles := src/card/card.c
Cfiles += src/terminal/terminal.c
Cfiles += src/server/server.c
Cfiles += src/app/app.c
Cfiles += main.c
 
.PHONY: all clean

all:
	@$(CC) $(Cfiles) -o main.exe
	@echo '\nAll files has been built and compiled!\n'

clean:
	@echo '\nmain.exe has been deleted!\n'
	@-rm -f main.exe
