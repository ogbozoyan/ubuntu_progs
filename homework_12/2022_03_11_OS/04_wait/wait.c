#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  
  pid_t pid;
  int wstatus;  
  if ( (pid = fork()) > 0) {
    wait(&wstatus);
    printf("Child is dead!!!!(is_exit=%d; status = %d; is_signal = %d; signum = %d)\n",
           WIFEXITED(wstatus),
           WEXITSTATUS(wstatus),
           WIFSIGNALED(wstatus),
           WTERMSIG(wstatus));
    return 0;
  }

  *((char*)0) = 'a';  
  //while( pid == 0 ){}
  return __LINE__-1;
}
