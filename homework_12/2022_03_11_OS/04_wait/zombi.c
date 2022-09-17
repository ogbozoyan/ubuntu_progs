#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void undead(int none) {
  printf("I`m necromant!!! I not wanna die!!!\n");
}

int main(int argc, char *argv[])
{
   /* fork(); */
   /* while(1) {} */
  
  while( fork() != 0 ) {} 
  return 0;

  
  /* signal(SIGTERM, undead); */
  /* signal(SIGINT, undead); */

  /* while( fork() != 0 ) {} */
  /* return 0; */

    /* signal(SIGTERM, undead); */
  /* signal(SIGINT, undead); */

  /* if ( fork();  > 0 ) { */
  /*    while(1) {} */
  /* } */
  /* while(1) {fork();} */
  /* if ( fork() > 0 ) { */

  /* } */
  /* while(fork() != 0 ) {};    */
  /* return __LINE__; */
}
