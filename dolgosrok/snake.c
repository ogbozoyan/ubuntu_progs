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
#include <arpa/inet.h>

#define BORDER 0x8A2BE2

/* gcc -g snake.c -o game -pthread -lncurses
blue 0x8B559C69 ,blue 0x00009999, red 0xFF450000,purple 0x8A2BE2, black 0x00000000*/
int fi[4],si[4],sum1,sum2;
int work_flag = 1;
int i = 0;
size_t fb_size, map_size, page_size;
int fb;
struct fb_var_screeninfo info;
uint32_t *ptr;
pthread_t thread,thread2,thread_key1,thread_key2,thread_send,thread_recv,thread_press;
int ch1=0;
int ch2=0;
int way = 0;
int way2 = 0;
int sprava = 0;
int sleva = 0;
struct sockaddr_in me, other;
int my_fd;
int other_fd;
int size = sizeof(me);
FILE *f;
typedef struct Bike{
  unsigned int flag_of_die;
  unsigned int x;
  unsigned int y;
  unsigned int key;
  unsigned int side;
  unsigned int name;
  int cords[8][5];
  uint32_t color;
  uint32_t enemy_color;
}Bike;


int win(struct Bike *car){
  munmap(ptr, map_size);
  close(fb);
  if(car->name == 66){
  mvprintw(1,0, "%cLUE LOST GAME \nCongratulations to RED you earned %d bucks",car->name,i);
  }
  else{
    mvprintw(1,0, "%cED LOST GAME \nCongratulations to BLUE you earned %d bucks",car->name,i);
  }
  refresh();
  endwin();
  exit(0);
}
void handler(){work_flag = 0; munmap(ptr, map_size);
  close(fb);
  endwin();
  exit(0);}

void* press_first_bike(void *args){
    while(1){
        ch1=getch();
        sendto(my_fd,&ch1,1,MSG_CONFIRM,(struct sockaddr*)&other,size);
    }
}
void* press_second_bike(void *args){
    while(1){
        recvfrom(my_fd,&ch2,1,MSG_WAITALL,(struct sockaddr*)&me,&size);
    }
}

void* keypress_first(void *args){
  Bike* biker = (Bike*) args;
  while(work_flag){
    switch(ch1)
    {
      case 'w':
          way = 1;
          biker->side = way;
        break;
      case 's':
          way = 2;
          biker->side = way;
        break;
      case 'a':
          way = 3;
          biker->side = way;
        break;
      case 'd':
          way = 4;
          biker->side = way;
        break;
      default:
        break;

      }
  }
}
void* keypress_second(void *args){
  Bike* biker = (Bike*) args;
  while(work_flag){
    switch(ch2)
    {
      case 'w':
          way2 = 1;
          biker->side = way2;
        break;
      case 's':
          way2 = 2;
          biker->side = way2;
        break;
      case 'a':
          way2 = 3;
          biker->side = way2;
        break;
      case 'd':
          way2 = 4;
          biker->side = way2;
        break;
      default:
        break;

      }
  }
}

int initialization(int *args,char **argv){

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
      

      if((args[0]>info.xres_virtual)||(args[1])>info.yres_virtual){
        printf("Max value of X %d\tY %d\n",info.xres_virtual,info.yres_virtual);
        munmap(ptr, map_size);
        close(fb);
        endwin();
        exit(0);
     }
 
      info.xres = args[0];
      info.yres = args[1];
      if( NULL == initscr()) {
          return __LINE__;
        }
      noecho();
      curs_set(2);
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
  // везде 8 на 9 поменяю в принтах
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
void print_black_r(int x, int y){
  int cords_x[9];
  int cords_y[5];
  int a = x+1;
  int b = y;
  for(int i=0;i<9;i++){
    cords_x[i] = a+i;
  }
  cords_y[0] = b-2;
  cords_y[1] = b-1;
  cords_y[2] = b-0;
  cords_y[3] = b+1;
  cords_y[4] = b+2;
  for(int i=0;i<9;i++){
    for(int j=0;j<5;j++){
      ptr[cords_y[j]*info.xres_virtual+cords_x[i]] = 0x00000000;
    }
  }
}
void print_black_l(int x, int y){
 int cords_x[9];
  int cords_y[5];
  int a = x-1;
  int b = y;
  for(int i=0;i<9;i++){
    cords_x[i] = a-i;
  }
  cords_y[0] = b-2;
  cords_y[1] = b-1;
  cords_y[2] = b-0;
  cords_y[3] = b+1;
  cords_y[4] = b+2;
  for(int i = 0;i<9;i++){
    for(int j = 0;j<5;j++){
      ptr[cords_y[j]*info.xres_virtual+cords_x[i]] = 0x00000000;
    }
  }
}
void print_black_u(int x, int y){
  int cords_y[9];
  int cords_x[5];
  int a = x;
  int b = y-1;
  for(int i=0;i<9;i++){
    cords_y[i] = b-i;
  }
  cords_x[0] = a-2;
  cords_x[1] = a-1;
  cords_x[2] = a-0;
  cords_x[3] = a+1;
  cords_x[4] = a+2;
  for(int i = 0;i<9;i++){
    for(int j = 0;j<5;j++){
      ptr[cords_y[i]*info.xres_virtual+cords_x[j]]=0x00000000;
    }
  }
}
void print_black_d(int x,int y){
  int cords_y[9];
  int cords_x[5];
  int a = x;
  int b = y+1;
  for(int i=0;i<9;i++){
    cords_y[i] = b+i;
  }
  cords_x[0] = a-2;
  cords_x[1] = a-1;
  cords_x[2] = a-0;
  cords_x[3] = a+1;
  cords_x[4] = a+2;
  for(int i = 0;i<9;i++){
    for(int j = 0;j<5;j++){
      ptr[cords_y[i]*info.xres_virtual+cords_x[j]]=0x00000000;
    }
  }
}
void print_r(struct Bike *car,int x,int y,uint32_t enemy_color){
  int cords_x[9];
  int tail[5];
  int a = x+1;
  int b = y;

  for(int i=0;i<9;i++){
    cords_x[i] = a+i;
  }
  tail[0] = b-2;
  tail[1] = b-1;
  tail[2] = b-0;
  tail[3] = b+1;
  tail[4] = b+2;
  for(int i = 0;i<5;i++){
    if( (ptr[tail[i]*info.xres_virtual + cords_x[8]] == enemy_color) ||
        (ptr[tail[i]*info.xres_virtual + cords_x[8]] == BORDER) ||
        (ptr[tail[i]*info.xres_virtual + cords_x[8]] == car->color) ) {
      car->flag_of_die = 1;
      win(car);
      }
  }
  for(int i = 0;i<9;i++){
    for(int j = 0;j<5;j++){
      ptr[tail[j]*info.xres_virtual+cords_x[i]] = car->color;
    }
  }
  ptr[tail[0]*info.xres_virtual+a] = 0x00000000;
  ptr[tail[1]*info.xres_virtual+a] = 0x00000000;
  ptr[tail[2]*info.xres_virtual+a] = car->color;
  ptr[tail[3]*info.xres_virtual+a] = 0x00000000;
  ptr[tail[4]*info.xres_virtual+a] = 0x00000000;
  x=(a+9)%info.xres;


}
void print_l(struct Bike *car,int x,int y,uint32_t enemy_color){
  int cords_x[9];
  int tail[5];
  int a = x-1;
  int b = y;

  for(int i=0;i<9;i++){
    cords_x[i] = a-i;
  }
  tail[0] = b-2;
  tail[1] = b-1;
  tail[2] = b-0;
  tail[3] = b+1;
  tail[4] = b+2;
  for(int i = 0;i<5;i++){
  if( (ptr[tail[i]*info.xres_virtual + cords_x[8]] == enemy_color) ||
        (ptr[tail[i]*info.xres_virtual + cords_x[8]] == BORDER) ||
        (ptr[tail[i]*info.xres_virtual + cords_x[8]] == car->color) ) {
      car->flag_of_die = 1;
      win(car);
      }
  }
  for(int i = 0;i<9;i++){
    for(int j = 0;j<5;j++){
      ptr[tail[j]*info.xres_virtual+cords_x[i]] = car->color;
    }
  }
  ptr[tail[0]*info.xres_virtual+a] = 0x00000000;
  ptr[tail[1]*info.xres_virtual+a] = 0x00000000;
  ptr[tail[2]*info.xres_virtual+a] = car->color;
  ptr[tail[3]*info.xres_virtual+a] = 0x00000000;
  ptr[tail[4]*info.xres_virtual+a] = 0x00000000;

  x=(a+9)%info.xres;

}
void print_u(struct Bike *car,int x,int y,uint32_t enemy_color){
  int cords_y[9];
  int tail[5];
  int a = x;
  int b = y-1;
  for(int i=0;i<9;i++){
    cords_y[i] = b-i;
  }
  tail[0] = a-2;
  tail[1] = a-1;
  tail[2] = a-0;
  tail[3] = a+1;
  tail[4] = a+2;
  for(int i = 0;i<5;i++){
    if( (ptr[cords_y[8]*info.xres_virtual + tail[i]] == enemy_color) ||
        (ptr[cords_y[8]*info.xres_virtual + tail[i]] == BORDER) ||
        (ptr[cords_y[8]*info.xres_virtual + tail[i]] == car->color) ) {
      car->flag_of_die = 1;
      win(car);
      }
  }
  for(int i = 0;i<9;i++){
    for(int j = 0;j<5;j++){
      ptr[cords_y[i]*info.xres_virtual+tail[j]]=car->color;
    }
  }
  ptr[b*info.xres_virtual+tail[0]] = 0x00000000;
  ptr[b*info.xres_virtual+tail[1]] = 0x00000000;
  ptr[b*info.xres_virtual+tail[2]] = car->color;
  ptr[b*info.xres_virtual+tail[3]] = 0x00000000;
  ptr[b*info.xres_virtual+tail[4]] = 0x00000000;
  y = (b - 9)%info.yres;
}
void print_d(struct Bike *car,int x,int y,uint32_t enemy_color){
  int cords_y[9];
  int tail[5];
  int a = x;
  int b = y+1;
  for(int i=0;i<9;i++){
    cords_y[i] = b+i;
  }
  tail[0] = a-2;
  tail[1] = a-1;
  tail[2] = a-0;
  tail[3] = a+1;
  tail[4] = a+2;
  for(int i = 0;i<5;i++){
    if( (ptr[cords_y[8]*info.xres_virtual + tail[i]] == enemy_color) ||
        (ptr[cords_y[8]*info.xres_virtual + tail[i]] == BORDER) ||
        (ptr[cords_y[8]*info.xres_virtual + tail[i]] == car->color) ) {
      car->flag_of_die = 1;
      win(car);
      }
  }
  for(int i = 0;i<9;i++){
    for(int j = 0;j<5;j++){
      ptr[cords_y[i]*info.xres_virtual+tail[j]]=car->color;
    }
  }
  ptr[b*info.xres_virtual+tail[0]] = 0x00000000;
  ptr[b*info.xres_virtual+tail[1]] = 0x00000000;
  ptr[b*info.xres_virtual+tail[2]] = car->color;
  ptr[b*info.xres_virtual+tail[3]] = 0x00000000;
  ptr[b*info.xres_virtual+tail[4]] = 0x00000000;
  y = (b + 9)%info.yres;
}
int print(struct Bike *car,int *x,int *y,uint32_t enemy_color){
    ptr[*y * info.xres_virtual + *x] = car->color;
    if(car->side == (1)){
      if(car->key == 's') {}//print_black_d(*x,*y);
      if(car->key == 'a') print_black_l(*x,*y);
      if(car->key == 'd') print_black_r(*x,*y);
      car -> key = 'w';
      *y = (*y + info.yres - 1)%info.yres;
    }
    if(car->side == (2)){
      if(car->key == 'w') {}//print_black_u(*x,*y);
      if(car->key == 'a') print_black_l(*x,*y);
      if(car->key == 'd') print_black_r(*x,*y);
      car -> key = 's';
      *y = (*y+1)%info.yres;
    }
    if(car->side == (3)){
      if(car->key == 'w') print_black_u(*x,*y);
      if(car->key == 's') print_black_d(*x,*y);
      if(car->key == 'd') {}//print_black_r(*x,*y);
      car -> key = 'a';
      *x = (*x + info.xres -1)%info.xres;
    }
    if(car->side == (4)){
      if(car->key == 'w') print_black_u(*x,*y);
      if(car->key == 's') print_black_d(*x,*y);
      if(car->key == 'a') {}//print_black_l(*x,*y);
      car -> key = 'd';
      *x = (*x+1)%info.xres;
    }

      
    border_print();

    if(car->side == 1){
      print_u(car,*x,*y,enemy_color);
    }
    if(car->side == 2){
      print_d(car,*x,*y,enemy_color);
    }
    if(car->side == 3 ){
      print_l(car,*x,*y,enemy_color);
    }
    if(car->side == 4){
      print_r(car,*x,*y,enemy_color);
    }
}

void* init_bikes_and_cikl(void *args){
  if(sum2>sum1){
    fprintf(f,"SLEVA %d sum1\t %d sum2\n",sum1,sum2);
  Bike first;
  first.x = info.xres - 10;
  first.y = info.yres - 30;
  first.color = 0x01009999;
  first.side = 0;
  first.key = '.';
  first.flag_of_die = 0;
  Bike second;
  second.x = 10;
  second.y = 10;
  second.color = 0xff0000;
  second.side = 0;
  second.key = '.';
  second.flag_of_die = 0;
  way = first.side;
  way2 = second.side;
  first.name = 'B';
  second.name = 'R';

  pthread_create(&thread_key1,NULL,press_first_bike,NULL);//проверят нажатие
  pthread_create(&thread_key2,NULL,press_second_bike,NULL);//проверяет нажатие
  pthread_create(&thread, NULL, keypress_first, &first);//выставляет клавиши
  pthread_create(&thread2, NULL, keypress_second, &second);//выставляет клавиши

  while(work_flag)
  {
    print(&first,&first.x,&first.y,second.color);//меняет координаты и рисует
    print(&second,&second.x,&second.y,first.color);//меняет координаты и рисует
    i++;
    usleep(62500);
  }
  pthread_join(thread_key1,NULL);
  pthread_join(thread_key2,NULL);
  pthread_join(thread,NULL);
  pthread_join(thread2,NULL);}
 else if(sum1>sum2){
   fprintf(f,"SPRava %d sum1\t %d sum2\n",sum1,sum2);
  Bike first;
  first.x = 10;
  first.y = 10;
  first.color = 0xff0000;
  first.side = 0;
  first.key = '.';
  first.flag_of_die = 0;
  Bike second;
  second.x = info.xres - 10;
  second.y = info.yres - 30;
  second.color = 0x01009999;
  second.side = 0;// направление текущее
  second.key = '.';//переменная которая была предыдущей
  second.flag_of_die = 0;
  way = first.side; //
  way2 = second.side;
  first.name = 'R';
  second.name = 'B';
  pthread_t thread,thread2,thread_key1,thread_key2;
  pthread_create(&thread_key1,NULL,press_first_bike,NULL);//проверят нажатие
  pthread_create(&thread_key2,NULL,press_second_bike,NULL);//проверяет нажатие
  pthread_create(&thread, NULL, keypress_first, &first);//выставляет клавиши
  pthread_create(&thread2, NULL, keypress_second, &second);//выставляет клавиши

  while(work_flag)
  {
    print(&first,&first.x,&first.y,second.color);//меняет координаты и рисует
    print(&second,&second.x,&second.y,first.color);//меняет координаты и рисует

    i++;
    usleep(62500);
  }
  pthread_join(thread_key1,NULL);
  pthread_join(thread_key2,NULL);
  pthread_join(thread,NULL);
  pthread_join(thread2,NULL);
 }
}

int main(int argc, char *argv[]){

  signal(SIGINT, handler);
  int args[2];
  if(argc < 5){
    printf("Usage: %s Xres Yres Your_ip Enemy_ip\n",argv[0]);
    exit(0);
  }

  args[0] = atoi(argv[1]);
  args[1] = atoi(argv[2]);

 sscanf(argv[3],"%d.%d.%d.%d",&fi[0],&fi[1],&fi[2],&fi[3]);
 sscanf(argv[4],"%d.%d.%d.%d",&si[0],&si[1],&si[2],&si[3]);
 sum1 = fi[0]+fi[1]+fi[2]+fi[3];
   sum2 = si[0]+si[1]+si[2]+si[3];
   f = fopen("debug.txt","w");
   fprintf(f,"MAIN %d sum1\t %d sum2\n",sum1,sum2);
  initialization(args,argv);

  if ( (my_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        munmap(ptr, map_size);
        endwin();
        exit(EXIT_FAILURE);
    }
    me.sin_family    = AF_INET;
    me.sin_addr.s_addr = inet_addr((argv[3]));
    me.sin_port = htons(12345);
    if ( bind(my_fd, (const struct sockaddr *)&me,sizeof(me)) < 0 )
    {
        perror("bind failed");
        munmap(ptr, map_size);
        endwin();
        exit(EXIT_FAILURE);
    }
     if ( (other_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        munmap(ptr, map_size);
        endwin();
        exit(EXIT_FAILURE);
    }
    other.sin_family = AF_INET;
    other.sin_addr.s_addr = inet_addr((argv[4]));
    other.sin_port = htons(12345);
  pthread_t thread_cikla;
  pthread_create(&thread_cikla, NULL, init_bikes_and_cikl, NULL);
  pthread_join(thread_cikla,NULL);
  munmap(ptr, map_size);
  close(fb);
  fclose(f);
  endwin();
  return 0;
}