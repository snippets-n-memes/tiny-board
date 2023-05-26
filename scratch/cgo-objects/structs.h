#ifndef STRUCT_H
#define STRUCT_H

typedef struct Test Test;

struct Test{
  int Id;
  char *Name;
};

Test *getStruct();
#endif
