#include "text_field.h"

textField *newTextField(int height, int width, int y, int x) {
  textField *ret = malloc(sizeof(textField));
  ret->win = newwin(height, width, y, x);
  ret->width = width;
  ret->index = 0;
  ret->offset = 0;
  ret->chars = 0;
  ret->xscroll = false;
  ret->yscroll = false;
  return ret;
}

void initializeBuffer(textField* field, int length) {
  field->buffer = malloc(sizeof(char) * length);
  field->bufferLength = length;
  for(int i = 0; i < length; i++) field->buffer[i] = ' ';
  field->buffer[length-1] = '\0';
}

