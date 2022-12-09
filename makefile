c: main.c main.h ticket.c ticket.h
	gcc main.c ticket.c enums.c -lncurses -DCTEST -DDEBUG -o tiny-board

go: main.go main.c main.h
	go build