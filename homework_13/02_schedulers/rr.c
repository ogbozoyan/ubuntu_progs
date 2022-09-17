#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "sched.h"

static int process_count;
static int *active_process = NULL;
static int current_process = 0;
int sched_init(void)
{
  return 0;
}

void sched_clean(void)
{
  if ( active_process ) {
    free(active_process);
    active_process = NULL;
  }
  process_count = current_process = 0;
}

int add_proc(void)
{
  return (process_count++);
}

int sched(int time, int cont)
{
  int i;
  if ( !active_process ) {
    if ( NULL == (active_process = malloc(process_count * sizeof(int)))) {
      perror("malloc");
      return -1;
    }
    for (  i = 0 ; i < process_count ; i++ )
      active_process[i] = 1;
    return  current_process;
  }

  active_process[current_process] = cont;
  for (  i = 0 ; i < process_count ; i++ ) {
    current_process = ( current_process + 1 ) % process_count;
    if (active_process[current_process]) break;
  }
  return ( i == process_count) ? (-1) : (current_process);
}

int sched_fin(void)
{
  sched_clean();
  return 0;
}
