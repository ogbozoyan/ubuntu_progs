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
#include <pthread.h>
#include <ncurses.h>
int work_flag = 1;

void handler(int none)
{
  work_flag = 0;
}

int left = 0, right = 1, up = 0, down = 0, ch = 0;
int fb, x = 10, y = 10, xstep = 1, ystep = 1;
uint32_t *ptr, color = 0xffffffff; // white color
struct fb_var_screeninfo info;

void sn_move(void){
    while(work_flag){
	    
	    ptr[y * info.xres_virtual  + x] = color;    	
	        
	        if (up)
	            if ( info.yres <= (y -= ystep)) {
                   ystep = -ystep;
                    y += 2 * ystep;
               }
	        if (down)
	          if ( info.yres <= (y += ystep)) {
                  ystep = -ystep;
                   y += 2 * ystep;
               }
	        if (left)
	            if ( info.xres <= (x -= xstep)) {
                 xstep = -xstep;
                 x += 2 * xstep;
                }
	        if (right)
	            if ( info.xres <= (x += xstep)) {
                    xstep = -xstep;
                    x += 2 * xstep;
                }
	        usleep(1000);
    }
}

int main(int argc, char *argv[])
{
  size_t fb_size, map_size, page_size;

  signal(SIGINT, handler);

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

    pthread_t thr;
    pthread_create(&thr, NULL, sn_move, NULL);
    
    do {
      
	    switch(ch) {
	        case KEY_UP:
	            down = left = right = 0; up = 1;
	            break;
	        case KEY_DOWN:
	            up = left = right = 0; down = 1;
	            break;
	        case KEY_LEFT:
	            up = down = right = 0; left = 1;
	            break;
	        case KEY_RIGHT:
	            up = down = left = 0; right = 1;
	            break;
	        default:
	            break;
	        }

    } while('q' != (ch = getch()) || work_flag);
  
    endwin();

  munmap(ptr, map_size);
  close(fb);
  return 0;
}

