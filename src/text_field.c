#include "text_field.h"

textField *newTextField(int height, int width, int y, int x) {
  textField *ret = malloc(sizeof(textField));
  ret->win = newwin(height, width, y, x);
  ret->width = width;
  return ret;
}

void initializeBuffer(textField* field, int length) {
  field->buffer = malloc(sizeof(char) * length);
  for(int i = 0; i < length; i++) field->buffer[i] = ' ';
  field->buffer[length-1] = '\0';
}

