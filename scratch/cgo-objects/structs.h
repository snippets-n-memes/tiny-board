#ifndef STRUCT_H
#define STRUCT_H

typedef struct Test Test;
typedef struct TestArray TestArray;

struct Test{
  int Id;
  char *Name;
};


struct TestArray{
  int len;
  TEST *items;
};

Test *getStruct();
#endif
