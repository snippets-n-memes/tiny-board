#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void up(int a) {
  printf("moved UP %d\n", a);
}

void down(int a) {
  printf("moved DOWN %d\n", a);
}

void right(int a) {
  printf("moved RIGHT %d\n", a);
}

void left(int a) {
  printf("moved LEFT %d\n", a);
}

typedef void (*move)(int);
typedef struct Test Test;
typedef struct TestArray TestArray;

struct Test{
  move pressUp;
  move pressDown;
};

struct TestArray{
  move *moves;
};
  
int main() {
  Test *unit = malloc(sizeof(Test));
  unit->pressUp = &up;
  void (*down_ptr)(int) = &down;
  unit->pressDown = down_ptr;

  TestArray *bigUnit = malloc(sizeof(TestArray));
  bigUnit->moves = malloc(4*sizeof(move));

  bigUnit->moves[0] = &up;
  bigUnit->moves[1] = &down;
  bigUnit->moves[2] = &left;
  bigUnit->moves[3] = &right;

  printf("\n------ Small Unit test: ------\n");
  (*unit->pressUp)(10);
  (*unit->pressDown)(10);

  unit->pressUp = &left;
  (*unit->pressUp)(150);

  printf("\n------ Big Unit test: ------\n");
  srand(time(NULL));
  for(int i=0; i<4; i++){
    (*bigUnit->moves[i])(rand()%10);
  }
  return 0;
}