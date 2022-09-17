#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  pid_t pid;
  pid = fork();
  printf("my pid: %d, parent pid = %d; var pid = %d\n", getpid(), getppid(), pid);
  return 0;
}
