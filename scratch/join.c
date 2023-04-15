#include <string.h>
#include <stdio.h>

int main() {
  char* statuses[] = {"unassigned\0", "in progress\0", "blocked\0", "completed\0"};
  char dest[100];

  puts(dest);
  for(int i = 0; i < 4; i++) {
    strcat(dest, statuses[i]);
    if( i != 3) strcat(dest, " - ");
  }

  puts(dest);

}