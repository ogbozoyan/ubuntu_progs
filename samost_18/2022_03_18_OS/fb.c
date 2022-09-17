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

static void* movement();
void handler(int none);
static void* keypress();


pthread_t moved;
pthread_t keypress_check;


int work_flag = 1;
int fb, x, y, xstep, ystep;
struct fb_var_screeninfo info;
size_t fb_size, map_size, page_size;
uint32_t *ptr, color = 0x00000000;

int UP,DOWN,LEFT,RIGHT = 0;
int ch = 0;


int main(int argc, char *argv[])
{
  signal(SIGINT, handler);
  x = y = 0;
  xstep = ystep = 1;
  page_size = sysconf(_SC_PAGESIZE);
  
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
  if( NULL == initscr())
      return __LINE__;

  noecho();
  keypad(stdscr,TRUE);

  while(work_flag){
  pthread_create(&keypress_check,NULL,keypress,NULL);
  pthread_create(&moved,NULL,movement,NULL);
  }
  munmap(ptr, map_size);
  close(fb);
  endwin();
  return 0;
}

static void* movement(){
  while(work_flag) {
    ptr[y * info.xres_virtual  + x] = color;
        if (UP)
          if ( info.yres <= (y -= ystep)) {
                   ystep = -ystep;
                    y += 2 * ystep;
               }
        if (DOWN)
          if ( info.yres <= (y += ystep)) {
                  ystep = -ystep;
                   y += 2 * ystep;
               }
        if (LEFT)
          if ( info.xres <= (x -= xstep)) {
                 xstep = -xstep;
                 x += 2 * xstep;
                }
        if (RIGHT)
          if ( info.xres <= (x += xstep)) {
                    xstep = -xstep;
                    x += 2 * xstep;
                }

    color++;
    usleep(300);
  }
}
void handler(int none)
{
  work_flag = 0;
}
static void* keypress(){
    while(work_flag){
    switch(ch=getch()){
       case KEY_UP:
              DOWN = LEFT = RIGHT = 0; UP = 1;
              break;
          case KEY_DOWN:
              UP = LEFT = RIGHT = 0; DOWN = 1;
              break;
          case KEY_LEFT:
              UP = DOWN = RIGHT = 0; LEFT = 1;
              break;
          case KEY_RIGHT:
              UP = DOWN = LEFT = 0; RIGHT = 1;
              break;
          default:
              break;
          }
    }
}
