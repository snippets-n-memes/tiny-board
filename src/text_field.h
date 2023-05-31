#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include "enums.h"

typedef struct {
  WINDOW *win; 
  int height;
  int width;
  int index;
  int offset;
  int chars;
  char *buffer;
  int bufferLength;
  bool xscroll;
  bool yscroll;
} textField;

typedef struct {
  WINDOW *win; 
  int height;
  int width;
  char **options;
  int selection;
} radioButton;

typedef union {
  radioButton button;
  textField text;
} field;

typedef struct {
  field value;
  bool isText;
} menuNode;


void refreshOptions(Options *current);
textField *newTextField(int height, int width, int y, int x);
void initializeBuffer(textField* field, int length);
radioButton *newRadioButton(int height, int width, int y, int x, char **options);

#endif