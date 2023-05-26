#include "structs.h"
#include <stdlib.h>

Test *getStruct(){
  Test *ret = malloc(sizeof(Test));
  ret->Id = 100;
  ret->Name = "Some Return Value";
  return ret;
}