#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "sched.h"

static int process_count;
int sched_init(void)
{
  fprintf(stderr,"Hello, world\n");
  return 0;
}

void sched_clean(void)
{
  process_count = 0;
}

int add_proc(void)
{
  return (process_count++);
}

int sched(int time, int cont)
{
  if (cont == 0) {
    process_count--;
  }
  return process_count;
}

int sched_fin(void)
{
  return 0;
}
