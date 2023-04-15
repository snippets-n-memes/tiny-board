#include <stdio.h>

int main(void) {
  typedef struct {
    int x;
    int y;
  } A;

  typedef struct {
    char* name;
    int x;
    int y;
    int count;
  } B;

  typedef union AorB{
    A itsA;
    B itsB;
  } AorB;

  A objectA;
  objectA.x = 0;
  objectA.y = 10; 

  B objectB;
  objectB.x = -100;
  objectB.y = -200;
  objectB.name = "A FANCY TITLE";
  objectB.count = 15;

  union AorB testA;
  testA.itsA = objectA;

  union AorB testB;
  testB.itsB = objectB;

  printf("A.x: %d\n", testA.itsA.x);
  printf("B.x: %d\n", testB.itsB.x);
  printf("B.name: %s\n", testB.itsB.name);
}