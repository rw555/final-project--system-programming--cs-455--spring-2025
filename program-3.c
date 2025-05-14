#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define STRING_LENGTH 14

int main() {
  int fd;
  int offset = -1; // we set offset to -1 because the first lseek will iterate it to 0
  char string[STRING_LENGTH] = "             \0";

  if(-1 == (fd = open("./README.md", O_RDWR))) {
    printf("Failed to open README File. Exiting...\n");

    exit(EXIT_FAILURE);
  }

  while (strcmp(string, "### Program 3")) {
    lseek(fd, ++offset, SEEK_SET);

    if (-1 == read(fd, string, 13 * sizeof(char))) {
      printf("Failed to read README file. Exiting...\n");

      exit(EXIT_FAILURE);
    }
  }

  for(int character = 0; string[character] != '\0'; ++character) {
    string[character] = toupper(string[character]);
  }
  lseek(fd, offset, SEEK_SET);

  if(-1 == write(fd, string, 13 * sizeof(char))) {
    printf("Failed to write to README file. Exiting...\n");

    exit(EXIT_FAILURE);
  }

  if(-1 == close(fd)) {
    printf("Failed to close README file. Exiting...\n");

    exit(EXIT_FAILURE);
  }
}
