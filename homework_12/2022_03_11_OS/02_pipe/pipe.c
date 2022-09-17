#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char* env[])
{
  pid_t pid;
  char *args[2] = {"PROGRAM", NULL};
  int pipefd[2];
  
  if ( argc != 3 ) {
    printf("USE: %s <prog1> <prog2>\n", argv[0]);
    return 0;    
  }

  if ((0) != pipe(pipefd)) {
    perror("pipe");
    return __LINE__;
  }
  
  switch ( fork() ) {
  case -1:
    perror("fork");
    return __LINE__;
  case 0:
    close(pipefd[1]);
    close(0);
    dup2(pipefd[0], 0);
    args[0] = argv[2];
    execve(args[0], args, env);
    break;
  default:
    close(pipefd[0]);
    close(1);
    dup2(pipefd[1], 1);
    args[0] = argv[1];
    execve(args[0], args, env);
  }
  perror("execve");
  return __LINE__;
}
