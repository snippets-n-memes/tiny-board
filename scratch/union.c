#include <stdio.h>
#include <stdbool.h>

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
    A A;
    B B;
  } AorB;

  typedef struct wrapper {
    AorB value;
    bool isA;
  } wrapper;

  A objectA;
  objectA.x = 0;
  objectA.y = 10; 

  B objectB;
  objectB.x = -100;
  objectB.y = -200;
  objectB.name = "A FANCY TITLE";
  objectB.count = 15;

  union AorB testA;
  testA.A = objectA;

  union AorB testB;
  testB.B = objectB;

  wrapper container;
  container.isA = true;
  container.value = testA;

  printf("A.x: %d\n", testA.A.x);
  printf("B.x: %d\n", testB.B.x);
  printf("B.name: %s\n", testB.B.name);
  printf("testA.B.name: ", testA.B.name);
  if (container.isA) printf("isA is true in union container");
}