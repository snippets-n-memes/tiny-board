c: main.c main.h
	gcc main.c -lncurses -DCTEST -DDEBUG -o tiny-board

go: main.go main.c main.h
	go build