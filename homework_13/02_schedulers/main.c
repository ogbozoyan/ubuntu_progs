#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include <errno.h>
#include <string.h>

#define SAFE_DLSYM(name) do {						\
    if ( NULL == (name = (typeof(name)) dlsym(handle, #name))) {	\
      fprintf(stderr,"Could not get symbol " #name ": %s\n", dlerror()); \
      dlclose(handle);							\
      return __LINE__;							\
    }									\
  }while(0)

#ifndef DYNAMIC_PROCESS_COUNT
#define PROCESS_COUNT (10)
#endif

#define TEST_COUNT (100)
#define MINIMUM_WORK_TIME 100
#define MAXIMUM_WORK_TIME 300
#define MAXIMUM_KVANT (MINIMUM_WORK_TIME/10)

struct process {
  int id;
  int work_time;
  int life_time;
  struct {
    int min;
    int max;
  } kvant;
  int full_time;
};

typedef int (*type1_f)(void);
typedef int (*type2_f)(int,int);

int main(int argc, char *argv[])
{
  void* handle;
  char* library_name;
  int i, j, test_count, kvant, end, id;
  float average = 0.0;
  type1_f sched_init, sched_clean, add_proc, sched_fin;
  type2_f sched;
  
#ifdef DYNAMIC_PROCESS_COUNT
  int PROCESS_COUNT = 0;
  struct process *process;
#else
  struct process process[PROCESS_COUNT];
#endif

  if ( argc != 2 ) {
    fprintf(stderr,"Usage: %s <sched_lib>\n",argv[0]);
    return __LINE__;
  }
  
  library_name = realpath(argv[1],NULL);
  if ( library_name == NULL )  {
    perror("realpath");
    return __LINE__;
  }

  handle = dlopen(library_name,RTLD_NOW);
  free(library_name);
  if ( handle == NULL ) {
    fprintf(stderr, "Could not load %s: %s\n",argv[1], dlerror());
    return __LINE__;
  }

  SAFE_DLSYM(sched_init);
  SAFE_DLSYM(sched_clean);
  SAFE_DLSYM(add_proc);
  SAFE_DLSYM(sched_fin);
  SAFE_DLSYM(sched);

  if ( sched_init() ) {
    fprintf(stderr,"Error in sched_init\n");
    dlclose(handle);
    return __LINE__;
  }

  if ( !initscr() ) {
    fprintf(stderr,"Could not init ncurses\n");
    dlclose(handle);
    return __LINE__;
  }

#ifdef DYNAMIC_PROCESS_COUNT
  PROCESS_COUNT = LINES - 1;
  process = (typeof(process)) malloc(sizeof(struct process)*PROCESS_COUNT);
  if ( NULL == process ) {
    int err = errno;
    endwin();
    fprintf(stderr,"malloc: %s\n", strerror(err));
    dlclose(handle);
    return __LINE__;
  }
#endif

  srand(time(NULL) * getpid());
  for ( i = 0 ; i < PROCESS_COUNT ; i++ ) {
#if MINIMUM_WORK_TIME < MAXIMUM_WORK_TIME
    process[i].full_time = (rand() % (MAXIMUM_WORK_TIME - MINIMUM_WORK_TIME)) + MINIMUM_WORK_TIME;
#else
    process[i].full_time = MAXIMUM_WORK_TIME;
#endif
    process[i].kvant.min = process[i].kvant.max = (rand() % (MAXIMUM_KVANT)) + 1;
    while (process[i].kvant.min == process[i].kvant.max) {
      process[i].kvant.max = (rand() % (MAXIMUM_KVANT)) + process[i].kvant.min;
    }
  }
  
  test_count = TEST_COUNT;
  curs_set(0);
  while( test_count-- ) {
    sched_clean();
    for ( i = 0 ; i < PROCESS_COUNT ; i++) {
      process[i].work_time = process[i].life_time = 0;
      process[i].id = add_proc();
      if ( process[i].id == -1 ) {
	sched_fin();
	dlclose(handle);
	endwin();
	fprintf(stderr,"Error in add_proc\n");
#ifdef DYNAMIC_PROCESS_COUNT
	free(process);
#endif
	return __LINE__;
      }
    }
    
    kvant = end = 0;
    while( (-1) != (id = sched(kvant, end))) {
      clear();
      mvprintw(0,0,"process count: %d; average time: %.3f; test left: %d", PROCESS_COUNT, average, test_count);
      for ( i = 1 ; i < PROCESS_COUNT ; i++) {
	for ( j = 0 ; j <= (int)((((float)COLS) / (float)(process[i].full_time)) * (float)(process[i].work_time)); j++ ) {
	  mvaddch(i, j,  ACS_BLOCK);
	}
      }
      refresh();
      for ( i = 0 ; i < PROCESS_COUNT ; i++) {
	if ( process[i].id == id ) break;
      }
      if ( i == PROCESS_COUNT ) {
	sched_fin();
	dlclose(handle);
	endwin();
	fprintf(stderr,"Incorrect id: %d\n",id);
#ifdef DYNAMIC_PROCESS_COUNT
	free(process);
#endif
	return __LINE__;
      }
      if( process[i].work_time == process[i].full_time ){
	sched_fin();
	dlclose(handle);
	endwin();
	fprintf(stderr,"Process %d is dead\n",id);
#ifdef DYNAMIC_PROCESS_COUNT
	free(process);
#endif
	return __LINE__;
      }
      kvant = (rand() % (process[i].kvant.max - process[i].kvant.min)) + process[i].kvant.min;
      if ( (process[i].work_time + kvant) > process[i].full_time)
	kvant = process[i].full_time - process[i].work_time;

       for ( j = 0 ; j < PROCESS_COUNT ; j++ ) {
	 if (process[j].work_time == process[j].full_time) continue;
	 process[j].life_time += kvant;
       }
      process[i].work_time += kvant;
      end = process[i].full_time - process[i].work_time;
      usleep(100000);
    }
    average = 0.0;
    for ( i = 0 ; i < PROCESS_COUNT ; i++ ) {
      average += (float)process[i].life_time;
      if (process[i].work_time != process[i].full_time) {
	sched_fin();
	dlclose(handle);
	endwin();
	fprintf(stderr,"Process #%d is a life\n",process[i].id);
#ifdef DYNAMIC_PROCESS_COUNT
	free(process);
#endif
	return __LINE__;
      }
    }
    average /= (float)(PROCESS_COUNT);
  }
  sched_fin();
  dlclose(handle);
  endwin();
#ifdef DYNAMIC_PROCESS_COUNT
  free(process);
#endif
  printf("Test is done\n");
  return 0;
}
