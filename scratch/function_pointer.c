#include <stdlib.h>
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

struct Test{
  move pressUp;
  move pressDown;
};
  
int main() {
  Test *unit = malloc(sizeof(Test));
  unit->pressUp = &up;
  void (*down_ptr)(int) = &down;
  unit->pressDown = down_ptr;


  (*unit->pressUp)(10);
  (*unit->pressDown)(10);

  unit->pressUp = &left;
  (*unit->pressUp)(150);
  return 0;
}