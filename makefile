SHELL = /usr/bin/env bash -o pipefail
.SHELLFLAGS = -ec

SOURCES = $(wildcard src/*.c)

c: $(SOURCES) 
	gcc $(SOURCES) -lncurses -DCTEST -DDEBUG -o tiny-board

go: src/main.go $(SOURCES)
	(cd src && go build)
	mv src/tiny-board ./