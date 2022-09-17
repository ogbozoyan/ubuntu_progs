#include <signal.h>
#include <stdio.h>

void handler(int sig) {
  printf("Signal %d ignore\nI not wanna die!!!!\n", sig);
}

int main(int argc, char *argv[])
{
  signal(SIGINT, handler);
  signal(SIGTERM, handler);
  signal(SIGKILL, handler);

  while(1){ }
  return 0;
}
