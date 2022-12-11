#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include "enums.h"

typedef struct {
  WINDOW *win; 
  int height;
  int width;
  char *buffer;
  int bufferLength;
  bool xscroll;
  bool yscroll;
} textField;

textField *newTextField(int height, int width, int y, int x);
void initializeBuffer(textField* field, int length);

#endif