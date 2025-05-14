# Spring 2025 System Programming — Final Project

## Written Portion

### 1. Describe what happens to memory released by the OS with regard to virtual memory

REPLACE THIS CONTENT WITH YOUR ANSWER

---

### 2. In a C program, why does `argv[argv]` return `NULL`?

The program is attempting to read the contents of memory at the memory address of argv with an offset of the memory address of argv, which does not hold anything.

---

### 3. When a system call is made the CPU changes from user mode to kernel mode. Why?

Certain operations cannot be carried out in user mode, but kernel mode can act in both the user and kernel spaces. As such, the kernel mode carries out the operation that user mode cannot.

---

### 4. Explain the relationship between the return value of a system call and the global variable `errno`

REPLACE THIS CONTENT WITH YOUR ANSWER

---

### 5. Consider the following C program. The variables and functions get allocated to which memory segments? Write your answers in comments to the right of each item

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX 128

char my_string[MAX];
char class_name[] = "System Programming";
int global_integer = 3;

void print_global() {
  printf("%d\n", global_integer);
}

int square(int x) {
  int result = x * x;

  return result;
}

int main (int argc, char *argv[]) {
  char *dynamic_memory;
  dynamic_memory = malloc(MAX);
  free(dynamic_memory);
  dynamic_memory = NULL;

  return 0;
}
```

---

### 6. Explain the difference between `malloc`, `calloc`, `realloc`

REPLACE THIS CONTENT WITH YOUR ANSWER

---

### 7. Explain the difference between `brk` and `sbrk`. Why is `malloc` a better option of `brk`, and `sbrk`?

REPLACE THIS CONTENT WITH YOUR ANSWER

---

### 8. Explain why a shadow password file is needed

REPLACE THIS CONTENT WITH YOUR ANSWER

---

### 9. What is the numeric equivalent of the `README.md` file’s permission bits below, and what is the command to give the file full access, across the board?

```sh
-rw-r--r-- 1  johnnythunders  staff  3476 May  1 11:57 README.md
```

The numeric equivalent is '644'.
The command to give fill access is
```sh
chmod README.md 777
```

---

### 10. What does `kill -9 1` do? Explain in detail

This command force kills the "init" process, which exists for the entirety of the session when a computer is on and has PID 1. The -9 forces the kill operation. Killing PID 1 results in the computer shutting down.
