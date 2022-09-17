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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <termios.h>

void* communicate(void *args){
    while(1){
      if(send){
        ch1=getchar();
        swith(ch1){
          case 'w': ch
          case 'a':
          case 's':
          case 'd':
        }

        sendto(my_fd,&ch1,1,MSG_CONFIRM,(struct sockaddr*)&other,sizeof(other));
      }
      else{
        recvfrom(my_fd,&ch2,1,MSG_WAITALL,(struct sockaddr*)&me,&size);
      }
    }
}
//gcc name.c -o game -pthread
int main(int argc,char** argv){
    size_t fb_size, map_size, page_size;
    int fb;
    struct fb_var_screeninfo info;
    uint32_t *ptr;
    struct termios old, new;
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

    info.xres = args[0];
    info.yres = args[1];

    system("clear");

    tcgetattr(0, &old);
    new = old;
    new.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    new.c_oflag &= ~OPOST;
    new.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
    new.c_cflag &= ~(CSIZE | PARENB);
    new.c_cflag |= CS8;
    tcsetattr(0,TCSANOW,&new);

    ptr = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
    if ( MAP_FAILED == ptr ) {
      perror("mmap");
      close(fb);
      return __LINE__;
    }

    if(argc < 5){
      printf("Чтобы_запустить: %s Xres Yres Your_ip Enemy_ip\n\r",argv[0]);
      exit(0);
    }
    int args[3];

    int my_x,my_y,enemy_x,enemy_y = 0;
    char my_k,enemy_k = '0';
    int edge = 0xffffffff;
    uint32_t my_color,enemy_color;

    args[0] = atoi(argv[1]);
    args[1] = atoi(argv[2]);

    struct sockaddr_in me;
    struct sockaddr_in enemy;

    me.sin_family    = AF_INET;
    me.sin_addr.s_addr = inet_addr((argv[3]));
    me.sin_port = htons(12345);//порт менять тут

    enemy.sin_family    = AF_INET;
    enemy.sin_addr.s_addr = inet_addr((argv[4]));
    enemy.sin_port = htons(12345);//порт менять тут

    int socket = socket(AF_INET, SOCK_DGRAM, 0);
    bind(socket, (const struct sockaddr *)&me,sizeof(me));

    threead

}
