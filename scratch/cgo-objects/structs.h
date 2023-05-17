#ifndef STRUCT_H
#define STRUCT_H

typedef struct Test Test;

struct Test{
  int id;
  char *name;
};

Test *getStruct();
#endif
