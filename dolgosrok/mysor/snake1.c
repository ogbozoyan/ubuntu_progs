#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <string.h>
#include <sys/mman.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <signal.h>
#include <ncurses.h>
#include <pthread.h>
#define X 800
#define Y 600
#define MAX 480000

/* gcc -g snake.c -o game -pthread -lncurses
info.xres_virtual = 2048
info.yres_virtual = 2048
info.xres = 800
info.yres = 600
KEY_UP = 259 , DOWN = 258 , LEFT = 260 , RIGHT = 261
blue 0x8B559C69 , red 0xFF450000,purple 0x8A2BE2*/

int work_flag = 1;
int i = 0;
pthread_t thread,thread2,thread_cikla;
int fb;
struct fb_var_screeninfo info;
size_t fb_size, map_size, page_size;
uint32_t *ptr,*ptr2;
int ch;
int UP,LEFT,RIGHT = 0;
int DOWN = 1;


typedef struct Bike
{
  unsigned int flag_of_die; //if 1 => dead, dead could be,when touchs tail
  unsigned int x;
  unsigned int y;
  int coords[MAX][2];
  unsigned int side; //up,down,left,right
  uint32_t color;//OCHEVIDNO
}Bike;

void handler(int none);
void* keypress(void *args);
int initialization(void);
void* init_bikes_and_cikl(void *args);

void chek_touch(struct Bike *first,struct Bike *second){
  FILE *f;
  int j = 0;
  int buf2[2] = {0,0};
  int buf1[2] ={0,0};
  for(j;j<i;j++){
    buf2[0] = second -> coords[i][0];
    buf2[1] = second -> coords[i][1]; //get coords of head second biker
    buf1[0] = first -> coords[i][0];
    buf1[1] = first -> coords[i][1];
    if((buf2[0] == first-> coords[i-1][0]) && (buf2[1] == first -> coords[i-1][1])){
      second->flag_of_die = 1;
      f = fopen("debug.txt","w+");
      fprintf(f,"64string\n");
      fclose(f);
      exit(0);
    }
    else if((buf1[0] == second-> coords[i-1][0]) && (buf1[1] == second -> coords[i-1][1])){
      first->flag_of_die = 1;
      f = fopen("debug.txt","w+");
      fprintf(f,"72string\n");
      fclose(f);
      exit(0);
    }
  }
}




int main(int argc, char *argv[])
{
  signal(SIGINT, handler);
  initialization();
  /*
  Bike first;
  first.x = 0;
  first.y = 0;
  first.color = 0x8A2BE2;
  first.side = DOWN;
  first.flag_of_die = 0;
  Bike second;
  second.x = 759;
  second.y = 549;
  second.color = 0xFF450000;
  second.side = UP;
  second.flag_of_die = 0;*/


  
  pthread_create(&thread_cikla, NULL, init_bikes_and_cikl, NULL);


  pthread_join(thread_cikla,NULL);
  
  
  munmap(ptr, map_size);
  close(fb);
  endwin();
  return 0;
}

void handler(int none){
  work_flag = 0;
}

void* keypress(void *args){
  
  while('q'!=(ch=getch())){

    Bike* biker = (Bike*) args;
    switch(ch)
    {
      case 'w':
          UP = 1;
          DOWN = 0;
          LEFT = 0;
          RIGHT = 0;
          biker->side = UP;
        break;
      case 's':
          UP = 0;
          DOWN = 1;
          LEFT = 0;
          RIGHT = 0;
          biker->side = DOWN;
        break;
      case 'a':
          UP = 0;
          DOWN = 0;
          LEFT = 1;
          RIGHT = 0;
          biker->side = LEFT;
        break;
      case 'd':
          UP = 0;
          DOWN = 0;
          LEFT = 0;
          RIGHT = 1;
          biker->side = RIGHT;
        break;
      default:
        break;

    }
  }
}
int initialization(void){
    page_size = sysconf(_SC_PAGESIZE);
      
    if( NULL == initscr()) {
          return __LINE__;
        }
      noecho();
      curs_set(0);
      keypad(stdscr,TRUE);

      if ( 0 > (fb = open("/dev/fb0", O_RDWR))) {
        perror("open");
        return __LINE__;
      }

      if ( (-1) == ioctl(fb, FBIOGET_VSCREENINFO, &info)) {
        perror("ioctl");
        close(fb);
        return __LINE__;
      }

      fb_size = sizeof(uint32_t) * info.xres_virtual * info.yres_virtual;
      map_size = (fb_size + (page_size - 1 )) & (~(page_size-1));

      ptr = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
      if ( MAP_FAILED == ptr ) {
        perror("mmap");
        close(fb);
        return __LINE__;
      }
      ptr2 = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
      if ( MAP_FAILED == ptr2 ) {
        perror("mmap");
        close(fb);
        return __LINE__;
      }
}
void* init_bikes_and_cikl(void *args){
  Bike first;
  first.x = 0;
  first.y = 0;
  first.color = 0x8A2BE2;
  first.side = DOWN;
  first.flag_of_die = 0;
  Bike second;
  second.x = 759;
  second.y = 549;
  second.color = 0xFF450000;
  second.side = UP;
  second.flag_of_die = 0;
  pthread_create(&thread, NULL, keypress, &first);
  pthread_create(&thread2, NULL, keypress, &second);
  while(work_flag) {
    void chek_touch(&first,&second);
    ptr[first.y * info.xres_virtual + first.x] = first.color;
    ptr2[second.y * info.xres_virtual + second.x] = second.color;
    if(UP){
      first.x = first.x;
      first.y = (first.y + info.yres - 1)%info.yres;
      first.coords[i][0] = first.x;
      first.coords[i][1] = first.y;
      second.x = second.x;
      second.y = (second.y + info.yres - 1)%info.yres;
      second.coords[i][0] = second.x;
      second.coords[i][1] = second.y;
    }
    if(DOWN){
      first.x = first.x;
      first.y = (first.y+1)%info.yres;
      first.coords[i][0] = first.x;
      first.coords[i][1] = first.y;
      second.x = second.x;
      second.y = (second.y+1)%info.yres;
      second.coords[i][0] = second.x;
      second.coords[i][1] = second.y;
    }
    if(LEFT){
      first.x = (first.x + info.xres -1)%info.xres;
      first.y = first.y;
      first.coords[i][0] = first.x;
      first.coords[i][1] = first.y;
      second.x = (second.x + info.xres -1)%info.xres;
      second.y = second.y;
      second.coords[i][0] = second.x;
      second.coords[i][1] = second.y;
    }
    if(RIGHT){
      first.x = (first.x+1)%info.xres;
      first.y = first.y;
      first.coords[i][0] = first.x;
      first.coords[i][1] = first.y;
      second.x = (second.x+1)%info.xres;
      second.y = second.y;
      second.coords[i][0] = second.x;
      second.coords[i][1] = second.y;
    }
    i++;
    usleep(5500);
  }
  pthread_join(thread,NULL);
  pthread_join(thread2,NULL);
}

/*
void* cikl(void *args){
  Params *p = (Params*) p;
  
    while(work_flag) {
    ptr[p->first->y * info.xres_virtual + p->first->x] = p->first->color;
    ptr2[p->second->y * info.xres_virtual + p->second->x] = p->second->color;
    if(UP){
      p->first->x = p->first->x;
      p->first->y = (p->first->y + info.yres - 1)%info.yres;
      p->first->coords[i][0] = p->first->x;
      p->first->coords[i][1] = p->first->y;
      p->second->x = p->second->x;
      p->second->y = (p->second->y + info.yres - 1)%info.yres;
      p->second->coords[i][0] = p->second->x;
      p->second->coords[i][1] = p->second->y;
 
    }
    if(DOWN){
      p->first->x = p->first->x;
      p->first->y = (p->first->y+1)%info.yres;
      p->first->coords[i][0] = p->first->x;
      p->first->coords[i][1] = p->first->y;
      p->second->x = p->second->x;
      p->second->y = (p->second->y+1)%info.yres;
      p->second->coords[i][0] = p->second->x;
      p->second->coords[i][1] = p->second->y;
    }
    if(LEFT){
      p->first->x = (p->first->x + info.xres -1)%info.xres;
      p->first->y = p->first->y;
      p->first->coords[i][0] = p->first->x;
      p->first->coords[i][1] = p->first->y;
      p->second->x = (p->second->x + info.xres -1)%info.xres;
      p->second->y = p->second->y;
      p->second->coords[i][0] = p->second->x;
      p->second->coords[i][1] = p->second->y;
    }
    if(RIGHT){
      p->first->x = (p->first->x+1)%info.xres;
      p->first->y = p->first->y;
      p->first->coords[i][0] = p->first->x;
      p->first->coords[i][1] = p->first->y;
      p->second->x = (p->second->x+1)%info.xres;
      p->second->y = p->second->y;
      p->second->coords[i][0] = p->second->x;
      p->second->coords[i][1] = p->second->y;
    }
    i++;
    usleep(5500);
  }
}*/
/* стояло после pthread_create(&thread_cikla
while(work_flag) {

    ptr[first.y * info.xres_virtual + first.x] = first.color;
    ptr2[second.y * info.xres_virtual + second.x] = second.color;
    if(UP){
      first.x = first.x;
      first.y = (first.y + info.yres - 1)%info.yres;
      first.coords[i][0] = first.x;
      first.coords[i][1] = first.y;
      second.x = second.x;
      second.y = (second.y + info.yres - 1)%info.yres;
      second.coords[i][0] = second.x;
      second.coords[i][1] = second.y;
    }
    if(DOWN){
      first.x = first.x;
      first.y = (first.y+1)%info.yres;
      first.coords[i][0] = first.x;
      first.coords[i][1] = first.y;
      second.x = second.x;
      second.y = (second.y+1)%info.yres;
      second.coords[i][0] = second.x;
      second.coords[i][1] = second.y;
    }
    if(LEFT){
      first.x = (first.x + info.xres -1)%info.xres;
      first.y = first.y;
      first.coords[i][0] = first.x;
      first.coords[i][1] = first.y;
      second.x = (second.x + info.xres -1)%info.xres;
      second.y = second.y;
      second.coords[i][0] = second.x;
      second.coords[i][1] = second.y;
    }
    if(RIGHT){
      first.x = (first.x+1)%info.xres;
      first.y = first.y;
      first.coords[i][0] = first.x;
      first.coords[i][1] = first.y;
      second.x = (second.x+1)%info.xres;
      second.y = second.y;
      second.coords[i][0] = second.x;
      second.coords[i][1] = second.y;
    }
    i++;
    usleep(5500);
  }
*/

/* над usleep находилось
    if ( info.xres <= (x += xstep)) {
      xstep = -xstep;
      x += 2 * xstep;
    }

    if ( info.yres <= (y += ystep)) {
      ystep = -ystep;
      y += 2 * ystep;
    }
  */


