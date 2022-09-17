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
#include <netdb.h>
#include <ifaddrs.h>
#include <linux/if_link.h>

#define IP "127.0.0.1"
//#define IP "10.0.2.15"

#define BORDER 0x5A2BE2
int fi[4],si[4],sum1,sum2;
int work_flag = 1;
int i = 0;
size_t fb_size, map_size, page_size;
int fb;
struct fb_var_screeninfo info;
uint32_t *ptr;
pthread_t thread,thread2,thread_key1,thread_key2,thread_send,thread_recv,thread_press;
pthread_mutex_t mutex;
int ch1='0';
int ch2='0';
int ch_dead='0';
int way = 0;
int way2 = 0;
int sprava = 0;
int sleva = 0;
struct sockaddr_in me, other;
int my_fd;
int other_fd;
int size = sizeof(me);

typedef struct Bike{
  unsigned int flag_of_die;
  unsigned int x;
  unsigned int y;
  unsigned int key;
  unsigned int side;
  unsigned int name;
  uint32_t color;
  uint32_t enemy_color;
}Bike;

int glip(unsigned long addr_c){
    struct ifaddrs *ifaddr;
    unsigned long addr_s;
    int mask;
    if (getifaddrs(&ifaddr) == -1) 
    {
        perror("getifaddrs");
        return 0;
    }

    for (struct ifaddrs *ifa = ifaddr; ifa != NULL;
                ifa = ifa->ifa_next) 
    {
        if (ifa->ifa_addr == NULL)
            continue;

        if (ifa->ifa_addr->sa_family == AF_INET) 
        {
            addr_s = ((struct sockaddr_in *)ifa->ifa_addr)->sin_addr.s_addr;
            if(addr_s != 0)
            {
                mask = ((struct sockaddr_in *)ifa->ifa_netmask)->sin_addr.s_addr; 
                if((addr_s&mask) == (addr_c&mask))
                {
                    return addr_s;
                }
            }
        }
    }
    return 0;
}

int win(){
  mvprintw(1,0, "You win \n Enemy lost %d bucks",i);
  refresh();
  endwin();
  munmap(ptr, map_size);
  close(fb);
  sleep(5);
  exit(0);
  system("clear");
}
int syncwin(int who){//1 i won,else i died
  
  if(who == 1){
  mvprintw(3,0, "You lost");
 refresh();
  endwin();
  munmap(ptr, map_size);
  close(fb);
  sleep(5);
  exit(0);
  system("clear");
}
  else{
  mvprintw(3,0, "You win you earned %d bucks",i);
  refresh();
  endwin();
  munmap(ptr, map_size);
  close(fb);
  sleep(5);
  exit(0);
  system("clear");
  }
}

void* press_first_bike(void *args){
    while(1){
        ch1=getch();
        sendto(my_fd,&ch1,1,MSG_CONFIRM,(struct sockaddr*)&other,size);
    }
}
void* press_second_bike(void *args){
    while(1){
      if(ch2 == '_'){
          int who_won = 1;
          syncwin(who_won);
        }
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
      srand(time(NULL));

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
  
  for(int i = 0;i<9;i++){
    for(int j = 0;j<5;j++){
		if( (ptr[tail[j]*info.xres_virtual + cords_x[i]] == enemy_color) ||
        (ptr[tail[j]*info.xres_virtual + cords_x[i]] == BORDER) ||
        (ptr[tail[j]*info.xres_virtual + cords_x[i]] == car->color) ) {
        ch_dead = '_';
    sendto(my_fd,&ch_dead,1,MSG_CONFIRM,(struct sockaddr*)&other,size);
      syncwin(2);
      }
      ptr[tail[j]*info.xres_virtual+cords_x[i]] = car->color+1;
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

  for(int i = 0;i<9;i++){
    for(int j = 0;j<5;j++){
		if( (ptr[tail[j]*info.xres_virtual + cords_x[i]] == enemy_color) ||
        (ptr[tail[j]*info.xres_virtual + cords_x[i]] == BORDER) ||
        (ptr[tail[j]*info.xres_virtual + cords_x[i]] == car->color) ) {
        ch_dead = '_';
    sendto(my_fd,&ch_dead,1,MSG_CONFIRM,(struct sockaddr*)&other,size);
      syncwin(2);
      }
      ptr[tail[j]*info.xres_virtual+cords_x[i]] = car->color+1;
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

  for(int i = 0;i<9;i++){
    for(int j = 0;j<5;j++){
		if( (ptr[cords_y[i]*info.xres_virtual + tail[j]] == enemy_color) ||
        (ptr[cords_y[i]*info.xres_virtual + tail[j]] == BORDER) ||
        (ptr[cords_y[i]*info.xres_virtual + tail[j]] == car->color) ) {
      ch_dead = '_';
    sendto(my_fd,&ch_dead,1,MSG_CONFIRM,(struct sockaddr*)&other,size);
      syncwin(2);
  }
      ptr[cords_y[i]*info.xres_virtual+tail[j]]=car->color+1;
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

  for(int i = 0;i<9;i++){
    for(int j = 0;j<5;j++){
		if( (ptr[cords_y[i]*info.xres_virtual + tail[j]] == enemy_color) ||
        (ptr[cords_y[i]*info.xres_virtual + tail[j]] == BORDER) ||
        (ptr[cords_y[i]*info.xres_virtual + tail[j]] == car->color) ) {
        ch_dead = '_';
    sendto(my_fd,&ch_dead,1,MSG_CONFIRM,(struct sockaddr*)&other,size);
      syncwin(2);
  }
      ptr[cords_y[i]*info.xres_virtual+tail[j]]=car->color+1;
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
    if(car->side == (1)){
      if(car->key == 's') {}
      if(car->key == 'a') print_black_l(*x,*y);
      if(car->key == 'd') print_black_r(*x,*y);
      car -> key = 'w';
      *y = (*y + info.yres - 1)%info.yres;
    }
    if(car->side == (2)){
      if(car->key == 'w') {}
      if(car->key == 'a') print_black_l(*x,*y);
      if(car->key == 'd') print_black_r(*x,*y);
      car -> key = 's';
      *y = (*y+1)%info.yres;
    }
    if(car->side == (3)){
      if(car->key == 'w') print_black_u(*x,*y);
      if(car->key == 's') print_black_d(*x,*y);
      if(car->key == 'd') {}
      car -> key = 'a';
      *x = (*x + info.xres -1)%info.xres;
    }
    if(car->side == (4)){
      if(car->key == 'w') print_black_u(*x,*y);
      if(car->key == 's') print_black_d(*x,*y);
      if(car->key == 'a') {}
      car -> key = 'd';
      *x = (*x+1)%info.xres;
    }

      ptr[*y * info.xres_virtual + *x] = car->color;
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

//void init_bikes_and_cikl()

void* init_bikes_and_cikl(void *args){
  system("clear");
  move(0,COLS-1);
  pthread_t thread,thread2;
  Bike first,second;
  
  while(ch1 == '0'){}
  
  ch1,ch2 = '0';
  
  if(sum2>sum1){
  ch1 = 'a';
  ch2 = 'd';
  first.x = info.xres - 1;
  first.y = info.yres - 4;
  first.color = 0x01009999;
  first.side = 3;
  first.key = '.';
  first.flag_of_die = 0;
  second.x = 0;
  second.y = 3;
  second.color = 0xff0000;
  second.side = 4;
  second.key = '.';
  second.flag_of_die = 0;
  way = first.side;
  way2 = second.side;
  first.name = 'B';
  second.name = 'R';
 }
 else if(sum1>sum2){
  ch1 = 'd';
  ch2 = 'a'; 
  first.x = 0;
  first.y = 3;
  first.color = 0xff0000;
  first.side = 4;
  first.key = '.';
  first.flag_of_die = 0;
  second.x = info.xres - 1;
  second.y = info.yres - 4;
  second.color = 0x01009999;
  second.side = 3;
  second.key = '.';
  second.flag_of_die = 0;
  way = first.side; //
  way2 = second.side;
  first.name = 'R';
  second.name = 'B';
}  
  pthread_create(&thread, NULL, keypress_first, &first);
  
  pthread_create(&thread2, NULL, keypress_second, &second);

  while(work_flag)
  {
    i++;
    print(&first,&first.x,&first.y,second.color);//меняет координаты и рисует
    print(&second,&second.x,&second.y,first.color);//меняет координаты и рисует
    if(&first.x < 0|| &first.y<0){win();};
    if(&second.x < 0|| &second.y<0){win();};
    usleep(62500);
  }
  pthread_join(thread,NULL);
  pthread_join(thread2,NULL);
 }


int main(int argc, char *argv[]){
  pthread_mutex_init(&mutex, NULL);

  int args[2];
  if(argc < 4){
    printf("Usage: %s Xres Yres Enemy_ip\n",argv[0]);
    exit(0);
  }
  args[0] = atoi(argv[1]);
  args[1] = atoi(argv[2]);
sscanf(IP,"%d.%d.%d.%d",&fi[0],&fi[1],&fi[2],&fi[3]);
 sscanf(argv[3],"%d.%d.%d.%d",&si[0],&si[1],&si[2],&si[3]);
 sum1 = fi[0]+fi[1]+fi[2]+fi[3];
   sum2 = si[0]+si[1]+si[2]+si[3];
  if(sum1 > sum2){ sprava = 1;sleva = 0;}
  else if (sum1 < sum2){ sleva = 1;sprava = 0;}
  initialization(args,argv);
  
    other.sin_family = AF_INET;
    other.sin_addr.s_addr = inet_addr((argv[3]));
    other.sin_port = htons(12345);
     if ( (other_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        munmap(ptr, map_size);
        endwin();
        exit(EXIT_FAILURE);
    }
    
    me.sin_family    = AF_INET;
    me.sin_addr.s_addr = inet_addr(IP);
    //me.sin_addr.s_addr = glip(other.sin_addr.s_addr); //get local ip
    me.sin_port = htons(12345);

    if ( (my_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        munmap(ptr, map_size);
        endwin();
        exit(EXIT_FAILURE);
    }
    if ( bind(my_fd, (const struct sockaddr *)&me,sizeof(me)) < 0 )
    {
        perror("bind failed");
        munmap(ptr, map_size);
        endwin();
        exit(EXIT_FAILURE);
    }

    //fprintf(stdout,"UDP part done press any key\n%d",me.sin_addr.s_addr);
    //getchar();
    
  pthread_t thread_key1,thread_key2,thread_cikla;;
  
  pthread_create(&thread_key1,NULL,press_first_bike,NULL);//проверят нажатие
  pthread_create(&thread_key2,NULL,press_second_bike,NULL);//проверяет нажатие
	
  //init_bikes_and_cikl();
  pthread_create(&thread_cikla,NULL,init_bikes_and_cikl,NULL);

  
  pthread_join(thread_cikla,NULL);
  pthread_join(thread_key1,NULL);
  pthread_join(thread_key2,NULL);
  munmap(ptr, map_size);
  close(fb);
  endwin();
  return 0;
}