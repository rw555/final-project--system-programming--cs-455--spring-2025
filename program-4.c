#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() {
  extern char etext, edata, end;
  char *string = malloc(1024);

  if (NULL == string) {
    printf("failed to allocate memory. Exiting...");

    return errno;
  }

  // Since these addresses are for the byte after the eng of each segment, we subtract 1 byte.
  printf("End of program text : %p\n", ((&etext)-1));
  printf("End of initialized data segment : %p\n", ((&edata)-1));
  printf("End of uninitialized data segment : %p\n", ((&end)-1));

  free(string);
  string = NULL;
}
