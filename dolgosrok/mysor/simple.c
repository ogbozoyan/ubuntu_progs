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
#define DOWN    0
#define UP      1
#define RIGHT   2
#define LEFT    3
#define LENGHT 252
#define WIDHT  11
#define BLACK 0x00000000
#define GREEN 0x00009009
int work_flag = 1;



typedef struct Zmeyuka
{

  unsigned int coords[LENGHT][2];
  uint8_t direction;

}Zmeyuka;

void* setDirection(void *args)
{

  while(work_flag)
  {

    Zmeyuka* podkolodnaya = (Zmeyuka*) args;
    
    switch(getch())
    {
      case KEY_UP:
        podkolodnaya -> direction = UP;
        break;
      case KEY_DOWN:
        podkolodnaya -> direction = DOWN;
        break;
      case KEY_RIGHT:
        podkolodnaya -> direction = RIGHT;
        break;
      case KEY_LEFT:
        podkolodnaya -> direction = LEFT;
        break;
     }
    
}

return 0;

}

void handler(int none)
{

  work_flag = 0;

}

int main(int argc, char *argv[])
{

  int fb;
  struct fb_var_screeninfo info;
  size_t fb_size, map_size, page_size;
  uint32_t *ptr;
  
  pthread_t thread;
  
  Zmeyuka podkolodnaya;

  signal(SIGINT, handler);

  page_size = sysconf(_SC_PAGESIZE);
  
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

  if ( 0 > (fb = open("/dev/fb0", O_RDWR)))
  {

    perror("open");
    return __LINE__;

  }

  if ( (-1) == ioctl(fb, FBIOGET_VSCREENINFO, &info) )
  {

    perror("ioctl");
    close(fb);
    return __LINE__;

  }

  fb_size = sizeof(uint32_t) * info.xres_virtual * info.yres_virtual;
  map_size = (fb_size + (page_size - 1 )) & (~(page_size-1));

  ptr = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);

  if ( MAP_FAILED == ptr )
  {

    perror("mmap");
    close(fb);
    return __LINE__;

  }

  //for(int i = 0; i < LENGHT; i++)
  //{

    //podkolodnaya.coords[i][0] = 0;
    //podkolodnaya.coords[i][1] = 0;

  //}
  podkolodnaya.direction = DOWN;
  
  pthread_create(&thread, NULL, setDirection, (void*) &podkolodnaya);

  while(work_flag) 
  {

    ptr[podkolodnaya.coords[LENGHT - 1][1] * info.xres_virtual  + podkolodnaya.coords[LENGHT - 1][0]] = BLACK;

        for(int i = 0; i < LENGHT - 1; i++)
        {

             podkolodnaya.coords[LENGHT - i - 1][0] = podkolodnaya.coords[LENGHT - i - 2][0];
             podkolodnaya.coords[LENGHT - i - 1][1] = podkolodnaya.coords[LENGHT - i - 2][1];
             ptr[podkolodnaya.coords[LENGHT - i - 1][1] * info.xres_virtual + podkolodnaya.coords[LENGHT - i - 1][0]] = GREEN;
       
        }
    
        switch(podkolodnaya.direction)
        {
      
            case UP:
                podkolodnaya.coords[0][1] += info.yres;
                podkolodnaya.coords[0][1] %= info.yres + 1;
                break;
            case DOWN:
                podkolodnaya.coords[0][1]++;
                podkolodnaya.coords[0][1] %= info.yres + 1;
                break;
            case LEFT:
                podkolodnaya.coords[0][0] += info.xres;
                podkolodnaya.coords[0][0] %= info.xres + 1;
                break;
            case RIGHT:
                podkolodnaya.coords[0][0]++;
                podkolodnaya.coords[0][0] %= info.xres + 1;
                break;
        
        }
  usleep(3500);
  }
    
  pthread_join(thread, NULL);
  
  endwin();
  munmap(ptr, map_size);
  close(fb);
  return 0;
}
