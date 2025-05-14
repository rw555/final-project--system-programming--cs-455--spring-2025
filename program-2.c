#include <stdio.h>

int compareStr(const char[], const char[]);

int main(int argc, char *argv[], char *env[]) {
  char path[] = "PATH", shell[] = "SHELL", user[] = "USERNAME";

  for (int i = 0; env[i] != NULL; ++i) {

    if (compareStr(env[i],path) || compareStr(env[i],shell) || compareStr(env[i],user)) {
      printf("%s\n",env[i]);
    }
  }
}

int compareStr(const char envAttribute[], const char name[]) {
  int same = 1;

  for(int character = 0 ; name[character] != '\0' ; character++) {

    if(envAttribute[character] != name[character]) {
      same = 0;
    }
  }

  return same;
}
