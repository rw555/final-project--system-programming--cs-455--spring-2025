#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

pid_t getTopPid();
pid_t getPPid(pid_t);
int getMaxPid();

int main() {
  pid_t topPid = getTopPid();

  printf("Top's PPID: %i\n", getPPid(topPid));
}

pid_t getTopPid() {
  int foundTopPid = 0; // If top is never found, this will be 0. Otherwise, this will be top's PID
  int statusFileDescriptor;
  char statusFilePath[32];
  char programName[4]; // "top" is only 3 letters, so we only care about the first 3 letters of the program name and the newline to ensure the name ends there
  const int MAX_PID = getMaxPid();

  for (int checkPid = 300; checkPid <= MAX_PID && !foundTopPid ; ++checkPid) {
    sprintf(statusFilePath, "/proc/%i/status", checkPid);

    if ((statusFileDescriptor = open(statusFilePath, O_RDONLY)) >= 0) {
      lseek(statusFileDescriptor, 6, SEEK_SET); // This moves the pointer to where the process name is.

      if (read(statusFileDescriptor, programName, 4*sizeof(char)) == -1) {
        printf("Failure to read: \"%s\", exiting...", statusFilePath);

        exit(EXIT_FAILURE);
      }

      if (close(statusFileDescriptor) == -1) {
        printf("Failure to close: \"%s\", exiting...", statusFilePath);

        exit(EXIT_FAILURE);
      }

      if (('t' == programName[0]) && ('o' == programName[1]) && ('p' == programName[2]) && ('\n' == programName[3])) {
        foundTopPid = checkPid;
      }
    } else {
      // If the error was the nonexistence of a file, that is expected for most PIDs which are unassigned and can be ignored.
      if (ENOENT != errno) {
        printf("Failure to open: \"%s\", exiting...", statusFilePath);

        exit(EXIT_FAILURE);
      }
    }
  }

  if (foundTopPid) {

    return (pid_t) foundTopPid;
  } else {
    // This code will only ever run if top does not have a PID, which means top is not running
    puts("Top is not running. Please run top in another terminal...");

    exit(EXIT_FAILURE);
  }
}

pid_t getPPid(pid_t processPid) {
  int statusFileDescriptor, parentPidOffset = 10, foundParentPid = 0, pidCharIndex = 0; // PPID offset starts at 10 because we know that the name column takes up at least 10 at the start
  char statusFilePath[32], parentPidFinderString[4], parentPidString[16];

  sprintf(statusFilePath, "/proc/%i/status", processPid);

  if (0 > (statusFileDescriptor = open(statusFilePath, O_RDONLY))) {
    printf("Failure to open: \"%s\", exiting...", statusFilePath);

    exit(EXIT_FAILURE);
  }

  // This while loop is for finding the offset of where the PPID exists in the status file
  while (!foundParentPid) {
    lseek(statusFileDescriptor, parentPidOffset++, SEEK_SET); // we iterate the offset variable here after it is used for the pointer

    if (read(statusFileDescriptor, parentPidFinderString, 4*sizeof(char)) == -1) {
      printf("Failure to read: \"%s\", exiting...", statusFilePath);

      exit(EXIT_FAILURE);
    }

    if (('P' == parentPidFinderString[0]) && ('P' == parentPidFinderString[1]) && ('i' == parentPidFinderString[2]) && ('d' == parentPidFinderString[3])) {
      foundParentPid = 1;
      // The offset variable has already been iterated by 1, so we add another five ("Pid:" and the tab character) to bring it to where the number is in the file
      parentPidOffset = parentPidOffset + 5;
    }
  }
  lseek(statusFileDescriptor, parentPidOffset, SEEK_SET);

  do {

    if (read(statusFileDescriptor, parentPidString+pidCharIndex, sizeof(char)) == -1) {
      printf("Failure to read: \"%s\", exiting...", statusFilePath);

      exit(EXIT_FAILURE);
    }
  } while ('\n' != parentPidString[pidCharIndex++]);

  // fill the rest of the string to prevent any garbage
  while (pidCharIndex < 15) {
    parentPidString[pidCharIndex++] = ' ';
  }
  parentPidString[15] = '\0';

  if (close(statusFileDescriptor) == -1) {
    printf("Failure to close: \"%s\", exiting...", statusFilePath);

    exit(EXIT_FAILURE);
  }

  return (pid_t) atoi(parentPidString);
}

int getMaxPid() {
  char maxPidString[16];
  int pidMaxFileDescriptor;

  if ((pidMaxFileDescriptor = open("/proc/sys/kernel/pid_max", O_RDONLY)) >= 0) {

    if (read(pidMaxFileDescriptor, maxPidString, 16*sizeof(char)) == -1) {
      puts("Error reading file: /proc/sys/kernel/pid_max");

      exit(EXIT_FAILURE);
    }

    if (close(pidMaxFileDescriptor) == -1) {
      puts("Error closing file: /proc/sys/kernel/pid_max");

      exit(EXIT_FAILURE);
    }
  } else {
    puts("Error opening file: /proc/sys/kernel/pid_max");

    exit(EXIT_FAILURE);
  }

  return atoi(maxPidString);
}
