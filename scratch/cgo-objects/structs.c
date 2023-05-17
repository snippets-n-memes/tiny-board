#include "structs.h"
#include <stdlib.h>

Test *getStruct(){
  Test *ret = malloc(sizeof(Test));
  ret->id = 100;
  ret->name = "Some Return Value";
  return ret;
}