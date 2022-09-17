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
int work_flag = 1;
void handler(int none)
{
  work_flag = 0;
}
int main(int argc, char *argv[])
{
  int fb, x, y, xstep, ystep;
  struct fb_var_screeninfo info;
  size_t fb_size, map_size, page_size;
  uint32_t *ptr, color;

  
  
  color = 0x12345678;
  x = y = 0;
  xstep = ystep = 1;
  page_size = sysconf(_SC_PAGESIZE);
  if(signal(SIGINT, handler)){
    printf("%d",color);
  }
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

  
  while(work_flag) {
    ptr[y * info.xres_virtual  + x] = color;

    if ( info.xres <= (x += xstep)) {
      xstep = -xstep;
      x += 2 * xstep;
    }

    if ( info.yres <= (y += ystep)) {
      ystep = -ystep;
      y += 2 * ystep;
    }

    color=color + 5;
    usleep(1);
  }


  munmap(ptr, map_size);
  close(fb);
  return 0;
}
