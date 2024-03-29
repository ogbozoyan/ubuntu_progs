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
#include <sys/socket.h>
#include <netinet/in.h>

#define BORDER 0x01009999

/* gcc -g snake.c -o game -pthread -lncurses
info.xres_virtual = 2048
info.yres_virtual = 2048
info.xres = 800
info.yres = 600
KEinfro.yres_UP = 259 , DOWN = 258 , LEFT = 260 , RIGHT = 261
blue 0x8B559C69 ,blue 0x00009999, red 0xFF450000,purple 0x8A2BE2, black 0x00000000*/

int work_flag = 1;
int i = 1;
pthread_t thread,thread2,thread_cikla;
int fb;
struct fb_var_screeninfo info;
size_t fb_size, map_size, page_size;
uint32_t *ptr,*ptr2,*black;
int ch;
int UP,LEFT,RIGHT = 0;
int DOWN = 1;
typedef struct Bike
{
  unsigned int flag_of_die; 
  unsigned int x;
  unsigned int y;
  unsigned int side;
  int cords[8][5]; 
  uint32_t color;
}Bike;

void handler(int none);
void* keypress(void *args);
int initialization(int *args);
void* init_bikes_and_cikl(void *args);
void border_print();
int print(struct Bike *car,int *x,int *y,uint32_t enemy_color);
void print_u(struct Bike *car,int x,int y);
void print_d(struct Bike *car,int x,int y);
void print_r(struct Bike *car,int x,int y);
void print_l(struct Bike *car,int x,int y);
void print_black_r(int x, int y);
void print_black_l(int x, int y);
void print_black_u(int x, int y);
void print_black_d(int x, int y);

int main(int argc, char *argv[])
{
  signal(SIGINT, handler);
  int args[3];
  if(argc < 3){
    printf("Usage %s Xres Yres\n",argv[0]);
    exit(0);
  }

  args[0] = atoi(argv[1]);
  args[1] = atoi(argv[2]);
  initialization(args);

  pthread_create(&thread_cikla, NULL, init_bikes_and_cikl, NULL);
  pthread_join(thread_cikla,NULL);
  

  munmap(ptr, map_size);
  close(fb);
  endwin();
  return 0;
}
int win(){
  munmap(ptr, map_size);
  close(fb);
  endwin();
  exit(0);
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
int initialization(int *args){
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
      srand(time(NULL));
      
      if((args[0]>info.xres_virtual)||(args[1])>info.yres_virtual){
      printf("Max value of X %d\tY %d\n",info.xres_virtual,info.yres_virtual);
      win();
      exit(0);
  } //ВОТ ЭТИ ПЕРМЕННЫЕ ОТВЕЧАЮТ ЗА РАЗМЕР ИГРОВОЙ ЗОНЫ не должны превышать x/y_virtual
      info.xres = args[0];
      info.yres = args[1];
      if( NULL == initscr()) {
          return __LINE__;
        }
      noecho();
      curs_set(0);
      keypad(stdscr,TRUE);
      ptr = mmap(NULL, map_size, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
      if ( MAP_FAILED == ptr ) {
        perror("mmap");
        close(fb);
        return __LINE__;
      }
      for(int a = 0;a<=info.xres;a++){
        for(int b = 0;b<=info.yres;b++){
          ptr[b * info.xres_virtual + a]=0x00000000;
        }
      }
}

void border_print(){
  for(int a = 0;a<info.yres;a++){
        ptr[a * info.xres_virtual] = BORDER;
      }
  for(int a=0;a<info.xres;a++){
      ptr[a] = BORDER;
    }
  for(int a=0;a<info.xres;a++){
    ptr[(info.yres-1) * info.xres_virtual + a] = BORDER;
  }
  for(int a=0;a<info.yres;a++){
    ptr[a*info.xres_virtual +(info.xres-1)] =BORDER;
  }
}
int print(struct Bike *car,int *x,int *y,uint32_t enemy_color){
    if(car->side == (UP)){
      *y = (*y + info.yres - 1)%info.yres;
      
    }
    if(car->side == (DOWN)){
      *y = (*y+1)%info.yres;
      
    }
    if(car->side == (LEFT)){
      *x = (*x + info.xres -1)%info.xres;
      
    }
    if(car->side == (RIGHT)){
      *x = (*x+1)%info.xres;
      
    }
    //if((ptr[*y * info.xres_virtual + *x] == enemy_color) || 
     // (ptr[*y * info.xres_virtual + *x] == car -> color)||
      //(ptr[*y * info.xres_virtual + *x] == BORDER)){
      //car->flag_of_die = 1;
    //win();
    //}
    border_print();
    ptr[*y * info.xres_virtual + *x] = car->color;
    if(car->side == UP){
      print_u(car,*x,*y);
    }
    if(car->side == DOWN){
      print_d(car,*x,*y);
    }
    if(car->side == LEFT){
      print_l(car,*x,*y);
    }
    if(car->side == RIGHT){
      print_r(car,*x,*y);
    }

    }
void print_black_r(int x, int y){
  int cords_x[8];
  int cords_y[5];
  int a = x+1;
  int b = y;
  for(int i=0;i<8;i++){
    cords_x[i] = a+i;
  }
  cords_y[0] = b-2;
  cords_y[1] = b-1;
  cords_y[2] = b-0;
  cords_y[3] = b+1;
  cords_y[4] = b+2;
  for(int i=0;i<8;i++){
    for(int j=0;j<5;j++){
      ptr[cords_y[j]*info.xres_virtual+cords_x[i]] = 0x00000000;
    }
  }
}
void print_black_l(int x, int y){
 int cords_x[8];
  int cords_y[5];
  int a = x-1;
  int b = y;
  for(int i=0;i<8;i++){
    cords_x[i] = a-i;
  }
  cords_y[0] = b-2;
  cords_y[1] = b-1;
  cords_y[2] = b-0;
  cords_y[3] = b+1;
  cords_y[4] = b+2;
  for(int i = 0;i<8;i++){
    for(int j = 0;j<5;j++){
      ptr[cords_y[j]*info.xres_virtual+cords_x[i]] = 0x00000000;
    }
  }
}
void print_black_u(int x, int y){
  int cords_y[8];
  int cords_x[5];
  int a = x;
  int b = y-1;
  for(int i=0;i<8;i++){
    cords_y[i] = b-i;
  }
  cords_x[0] = a-2;
  cords_x[1] = a-1;
  cords_x[2] = a-0;
  cords_x[3] = a+1;
  cords_x[4] = a+2;
  for(int i = 0;i<8;i++){
    for(int j = 0;j<5;j++){
      ptr[cords_y[i]*info.xres_virtual+cords_x[j]]=0x00000000;
    }
  }
}
void print_black_d(int x,int y){
  int cords_y[8];
  int cords_x[5];
  int a = x;
  int b = y+1;
  for(int i=0;i<8;i++){
    cords_y[i] = b+i;
  }
  cords_x[0] = a-2;
  cords_x[1] = a-1;
  cords_x[2] = a-0;
  cords_x[3] = a+1;
  cords_x[4] = a+2;
  for(int i = 0;i<8;i++){
    for(int j = 0;j<5;j++){
      ptr[cords_y[i]*info.xres_virtual+cords_x[j]]=0x00000000;
    }
  }
}
void print_r(struct Bike *car,int x,int y){
  int cords_x[8];
  int cords_y[5];
  int tail[5];
  int a = x+1;
  int b = y;
  
  for(int i=0;i<8;i++){
    cords_x[i] = a+i;
  }
  tail[0] = b-2;
  tail[1] = b-1;
  tail[2] = b-0;
  tail[3] = b+1;
  tail[4] = b+2;
  cords_y[0] = b-2;
  cords_y[1] = b-1;
  cords_y[2] = b-0;
  cords_y[3] = b+1;
  cords_y[4] = b+2;
  for(int i = 0;i<8;i++){
    for(int j = 0;j<5;j++){
      ptr[cords_y[j]*info.xres_virtual+cords_x[i]] = car->color;
    }
  }
  ptr[tail[0]*info.xres_virtual+a] = 0x00000000;
  ptr[tail[1]*info.xres_virtual+a] = 0x00000000;
  ptr[tail[2]*info.xres_virtual+a] = car->color;
  ptr[tail[3]*info.xres_virtual+a] = 0x00000000;
  ptr[tail[4]*info.xres_virtual+a] = 0x00000000;
  x=(a+8)%info.xres;
}
void print_l(struct Bike *car,int x,int y){
  int cords_x[8];
  int cords_y[5];
  int tail[5];
  int a = x-1;
  int b = y;
  
  for(int i=0;i<8;i++){
    cords_x[i] = a-i;
  }
  tail[0] = b-2;
  tail[1] = b-1;
  tail[2] = b-0;
  tail[3] = b+1;
  tail[4] = b+2;
  cords_y[0] = b-2;
  cords_y[1] = b-1;
  cords_y[2] = b-0;
  cords_y[3] = b+1;
  cords_y[4] = b+2;
  //print tail in tail[2] put car->color,then print car
  for(int i = 0;i<8;i++){
    for(int j = 0;j<5;j++){
      ptr[cords_y[j]*info.xres_virtual+cords_x[i]] = car->color;
    }
  }
  ptr[tail[0]*info.xres_virtual+a] = 0x00000000;
  ptr[tail[1]*info.xres_virtual+a] = 0x00000000;
  ptr[tail[2]*info.xres_virtual+a] = car->color;
  ptr[tail[3]*info.xres_virtual+a] = 0x00000000;
  ptr[tail[4]*info.xres_virtual+a] = 0x00000000;
  x=(a+8)%info.xres;
}
void print_u(struct Bike *car,int x,int y){
  int cords_y[8];
  int cords_x[5];
  int tail[5];
  int a = x;
  int b = y-1;
  for(int i=0;i<8;i++){
    cords_y[i] = b-i;
  }
  tail[0] = a-2;
  tail[1] = a-1;
  tail[2] = a-0;
  tail[3] = a+1;
  tail[4] = a+2;
  cords_x[0] = a-2;
  cords_x[1] = a-1;
  cords_x[2] = a-0;
  cords_x[3] = a+1;
  cords_x[4] = a+2;
  for(int i = 0;i<8;i++){
    for(int j = 0;j<5;j++){
      ptr[cords_y[i]*info.xres_virtual+cords_x[j]]=car->color;
    }
  }
  ptr[b*info.xres_virtual+tail[0]] = 0x00000000;
  ptr[b*info.xres_virtual+tail[1]] = 0x00000000;
  ptr[b*info.xres_virtual+tail[2]] = car->color;
  ptr[b*info.xres_virtual+tail[3]] = 0x00000000;
  ptr[b*info.xres_virtual+tail[4]] = 0x00000000;
  y = (b - 8)%info.yres; 
}
void print_d(struct Bike *car,int x,int y){
  int cords_y[8];
  int cords_x[5];
  int tail[5];
  int a = x;
  int b = y+1;
  for(int i=0;i<8;i++){
    cords_y[i] = b+i;
  }
  tail[0] = a-2;
  tail[1] = a-1;
  tail[2] = a-0;
  tail[3] = a+1;
  tail[4] = a+2;
  cords_x[0] = a-2;
  cords_x[1] = a-1;
  cords_x[2] = a-0;
  cords_x[3] = a+1;
  cords_x[4] = a+2;
  for(int i = 0;i<8;i++){
    for(int j = 0;j<5;j++){
      ptr[cords_y[i]*info.xres_virtual+cords_x[j]]=car->color;
    }
  }
  ptr[b*info.xres_virtual+tail[0]] = 0x00000000;
  ptr[b*info.xres_virtual+tail[1]] = 0x00000000;
  ptr[b*info.xres_virtual+tail[2]] = car->color;
  ptr[b*info.xres_virtual+tail[3]] = 0x00000000;
  ptr[b*info.xres_virtual+tail[4]] = 0x00000000;
  y = (b + 8)%info.yres; 
}
void* init_bikes_and_cikl(void *args){
  Bike first;
  first.x = info.xres/2 +(info.xres%34);
  first.y = info.yres/2 + (info.yres%34);
  first.color = 0x8A2BE2;
  first.side = DOWN;
  first.flag_of_die = 0;
  Bike second;
  second.x = info.xres/2 - (info.xres%34);
  second.y = info.yres/2 - (info.yres%34);
  second.color = 0xFF450000;
  second.side = DOWN;
  second.flag_of_die = 0;
  pthread_create(&thread, NULL, keypress, &first);
  pthread_create(&thread2, NULL, keypress, &second);
  
  
  while(work_flag) 
  {
    print(&first,&first.x,&first.y,second.color);
    print(&second,&second.x,&second.y,first.color);

    i++;
    
    usleep(5500);
    
  }
  pthread_join(thread,NULL);
  pthread_join(thread2,NULL);
  
}
