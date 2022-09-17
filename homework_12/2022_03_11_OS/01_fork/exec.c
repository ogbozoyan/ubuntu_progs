#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char* env[])
{
  pid_t pid;
  char *args[2] = {"PROGRAM", NULL};
  
  if ( argc == 1 ) {
    printf("USE: %s <prog1> <prog2> ....\n", argv[0]);
    return 0;    
  }
  
  for ( int i = 1 ; i < argc ; i++ ) {
    printf("Exec: %s\n", argv[i]);
    args[0] = argv[i];
    if ( 0 == fork() ) {
      execve(argv[i], args, env);
      perror("execve");
      return -1;
    }
    wait(NULL);
  }
  return 0;
}
