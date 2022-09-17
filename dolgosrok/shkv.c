#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <termios.h>
/* gcc название_игры -o game -pthread */
int sum1,sum2;
size_t fb_size, map_size, page_size;
int fb;
struct fb_var_screeninfo info;
uint32_t *ptr;
int char_my = '0',char_enemy= '0';
struct termios old, new;
struct sockaddr_in me, other;

int size = sizeof(me);

typedef struct tron{
   int x;
   int y;
   int prev_key;
   int side;
  uint32_t color;
  uint32_t enemy_color;
}tron;

typedef struct comm_t{
   int socket;
   int send;
   int recv;
}comm_t;


int end(uint32_t color){
  system("reset");
  if (color == 0xff0000){
    printf("red win\n\r");
  }
  else{
    printf("blue win\n\r");
  }
  munmap(ptr, map_size);
  close(fb);
  usleep(62500);
  exit(0);
}

void communicate(void *args){
    comm_t* comm = (comm_t*) args;
    while(1){
      if (comm->send == 1){
        char_my=getchar();
        sendto(comm->socket,&char_my,1,MSG_CONFIRM,(struct sockaddr*)&other,size);
      }
      else{
        recvfrom(comm->socket,&char_enemy,1,MSG_WAITALL,(struct sockaddr*)&me,&size);
      }
  }
}

void* keyboard_check(void *args){
  tron* player = (tron*) args;
  while(1){
    switch(char_my)
    {
      case 'w':
          player->side = 1;
        break;
      case 's':
          player->side = 2;
        break;
      case 'a':
          player->side = 3;
        break;
      case 'd':
          player->side = 4;
        break;
      default:
        break;
      }
  }
}

void* enemy_keyboard_check(void *args){
  tron* player_en = (tron*) args;
  while(1){
    switch(char_enemy)
    {
      case 'w':
          player_en->side = 1;
        break;
      case 's':
          player_en->side = 2;
        break;
      case 'a':
          player_en->side = 3;
        break;
      case 'd':
          player_en->side = 4;
        break;
      default:
        break;
      }
  }
}

void print_black(int x,int y,char nap){
  switch(nap){
    case 's':
        for(int i = x-2; i<=x+2 ;i++){
            for(int j = y+1; j <= y+9; j++){
                ptr[j*info.xres_virtual+i] = 0x00000000;
            }
        }
        break;
    case 'w':
        for(int i = x-2; i <= x+2;i++){
            for(int j = y-9; j <= y-1; j++){
                ptr[j*info.xres_virtual+i] = 0x00000000;
            }
        }
        break;
    case 'a':
         for(int i = x-9; i<=x-1 ;i++){
             for(int j = y-2; j <= y+2; j++){
                 ptr[j*info.xres_virtual+i] = 0x00000000;
             }
         }
         break;
    case 'd':
        for(int i = x+1; i<=x+9 ;i++){
            for(int j = y-2; j <= y+2; j++){
                ptr[j*info.xres_virtual+i] = 0x00000000;
            }
        }
        break;
    default:
        break;
  }
}

void print(struct tron *tron,int x,int y,uint32_t enemy_color,char nap){
  int c_x[9],c_y[9],black_stick[5];
  int a,b;
  switch(nap){
    case 'd':
      a = x+1;
      b = y;
      for(int i=0;i<9;i++){
        c_x[i] = a+i;
      }
      black_stick[0] = b-2;black_stick[1] = b-1;black_stick[2] = b-0;black_stick[3] = b+1;black_stick[4] = b+2;
      for(int i = 0;i<9;i++){
        for(int j = 0;j<5;j++){
          ptr[black_stick[j]*info.xres_virtual+c_x[i]] = tron->color;
        }
      }
      for(int i = 0;i<5;i++){
        if(i == 2){ptr[black_stick[i]*info.xres_virtual+a] = tron->color;}
        else{
          ptr[black_stick[i]*info.xres_virtual+a] = 0x00000000;
        }
      }
      x=(a+9)%info.xres;

      break;
    case 'a':
      a = x-1;
      b = y;
      for(int i=0;i<9;i++){
        c_x[i] = a-i;
      }
      black_stick[0] = b-2;black_stick[1] = b-1;black_stick[2] = b-0;black_stick[3] = b+1;black_stick[4] = b+2;
      for(int i = 0;i<9;i++){
        for(int j = 0;j<5;j++){
          ptr[black_stick[j]*info.xres_virtual+c_x[i]] = tron->color;
        }
      }
      for(int i = 0;i<5;i++){
        if(i == 2){ptr[black_stick[i]*info.xres_virtual+a] = tron->color;}
        else{
          ptr[black_stick[i]*info.xres_virtual+a] = 0x00000000;
        }
      }
      x=(a+9)%info.xres;
      break;
    case 'w':
      a = x;
      b = y-1;
      for(int i=0;i<9;i++){
        c_y[i] = b-i;
      }
      black_stick[0] = a-2;black_stick[1] = a-1;black_stick[2] = a-0;black_stick[3] = a+1;black_stick[4] = a+2;
      for(int i = 0;i<9;i++){
        for(int j = 0;j<5;j++){
          ptr[c_y[i]*info.xres_virtual+black_stick[j]]=tron->color;
        }
      }
      for(int i = 0;i<5;i++){
        if(i == 2){ptr[b*info.xres_virtual+black_stick[i]] = tron->color;}
        else{
          ptr[b*info.xres_virtual+black_stick[i]] = 0x00000000;
        }
      }
      y = (b - 9)%info.yres;
      break;
    case 's':
      a = x;
      b = y+1;
      for(int i=0;i<9;i++){
        c_y[i] = b+i;
      }
      black_stick[0] = a-2;black_stick[1] = a-1;black_stick[2] = a-0;black_stick[3] = a+1;black_stick[4] = a+2;
      for(int i = 0;i<9;i++){
        for(int j = 0;j<5;j++){
          ptr[c_y[i]*info.xres_virtual+black_stick[j]]=tron->color;
        }
      }
      for(int i = 0;i<5;i++){
        if(i == 2){ptr[b*info.xres_virtual+black_stick[i]] = tron->color;}
        else{
          ptr[b*info.xres_virtual+black_stick[i]] = 0x00000000;
        }
      }
      y = (b + 9)%info.yres;
      break;
    default:
    break;
  }
}

void game_start(struct tron *tron,int *x,int *y,uint32_t enemy_color){
    char nap_b,nap_tron = '0';
    int d = 0;
    if(tron->side == (1)){
      if(tron->prev_key == 's'){
        for(int i = (*x)-2;i<(*x)+3;i++){
          for(int j = (*y)-10;j<(*y)-2;j++){
            if((ptr[j*info.xres_virtual + i] == enemy_color) ||
                (ptr[j*info.xres_virtual + i] == 0xffffffff) ||
                (ptr[j*info.xres_virtual + i] == tron->color)) {
              d++;
            if(d>1){
              end(enemy_color);
          
            d = 0;
              }
          }
        }
      }
    }
      if(tron->prev_key == 'a'){
        nap_b = 'a';
        for(int i = (*x)-2;i<(*x)+3;i++){
          for(int j = (*y)-10;j<(*y)-2;j++){
            if((ptr[j*info.xres_virtual + i] == enemy_color) ||
                (ptr[j*info.xres_virtual + i] == 0xffffffff) ||
                (ptr[j*info.xres_virtual + i] == tron->color)) {
            d++;
            if(d>1){
              end(enemy_color);
            
            d = 0;
              }
              }
          }
        }
        print_black(*x,*y,nap_b);
      }
      if(tron->prev_key == 'd'){
        nap_b = 'd';
        for(int i = (*x)-2;i<(*x)+3;i++){
          for(int j = (*y)-10;j<(*y)-2;j++){
            if((ptr[j*info.xres_virtual + i] == enemy_color) ||
                (ptr[j*info.xres_virtual + i] == 0xffffffff) ||
                (ptr[j*info.xres_virtual + i] == tron->color)) {
            d++;
            if(d>1){
            end(enemy_color);
          
            d = 0;
              }
              }
          }
        }
        print_black(*x,*y,nap_b);
      }
      tron -> prev_key = 'w';
      *y = (*y + info.yres - 1)%info.yres;
    }

    if(tron->side == (2)){
      if(tron->prev_key == 'w'){
            for(int i = (*x)-2;i<(*x)+3;i++){
            for(int j = (*y)+2;j<(*y)+10;j++){
              if((ptr[j*info.xres_virtual + i] == enemy_color) ||
                  (ptr[j*info.xres_virtual + i] == 0xffffffff) ||
                  (ptr[j*info.xres_virtual + i] == tron->color)) {
              d++;
            if(d>1){
              end(enemy_color);
            
            d = 0;
              }
                }
            }
          }
      }
      if(tron->prev_key == 'a'){
        nap_b = 'a';
            for(int i = (*x)-2;i<(*x)+3;i++){
            for(int j = (*y)+2;j<(*y)+10;j++){
              if((ptr[j*info.xres_virtual + i] == enemy_color) ||
                  (ptr[j*info.xres_virtual + i] == 0xffffffff) ||
                  (ptr[j*info.xres_virtual + i] == tron->color)) {
              d++;
            if(d>1){
              end(enemy_color);
          
            d = 0;
              }
                }
            }
          }
        print_black(*x,*y,nap_b);
      }
      if(tron->prev_key == 'd'){
        nap_b = 'd';
         for(int i = (*x)-2;i<(*x)+3;i++){
            for(int j = (*y)+2;j<(*y)+10;j++){
              if((ptr[j*info.xres_virtual + i] == enemy_color) ||
                  (ptr[j*info.xres_virtual + i] == 0xffffffff) ||
                  (ptr[j*info.xres_virtual + i] == tron->color)) {
              d++;
            if(d>1){
           end(enemy_color);
           
            d = 0;
              }
                }
            }
          }
        print_black(*x,*y,nap_b);
      }
      tron -> prev_key = 's';

      *y = (*y+1)%info.yres;
    }
    if(tron->side == (3)){
      if(tron->prev_key == 'w'){
        nap_b = 'w';
        for(int i=(*x)-2;i<(*x)-10;i++){
          for(int j=(*y)-2;j<(*y)+3;j++){
            if( (ptr[j*info.xres_virtual + i] == enemy_color) ||
                (ptr[j*info.xres_virtual + i] == 0xffffffff) ||
                (ptr[j*info.xres_virtual + i] == tron->color) ) {
               d++;
            if(d>1){
            end(enemy_color);
    
            d = 0;
              }
                }
          }
        }
        print_black(*x,*y,nap_b);
      }
      if(tron->prev_key == 's'){
        nap_b = 's';
        for(int i=(*x)-2;i<(*x)-10;i++){
          for(int j=(*y)-2;j<(*y)+3;j++){
            if( (ptr[j*info.xres_virtual + i] == enemy_color) ||
                (ptr[j*info.xres_virtual + i] == 0xffffffff) ||
                (ptr[j*info.xres_virtual + i] == tron->color) ) {
              d++;
            if(d>1){
            end(enemy_color);
    
            d = 0;
              }
                }
          }
        }
        print_black(*x,*y,nap_b);
      }
      if(tron->prev_key == 'd'){
        for(int i=(*x)-2;i<(*x)-10;i++){
          for(int j=(*y)-2;j<(*y)+3;j++){
            if( (ptr[j*info.xres_virtual + i] == enemy_color) ||
                (ptr[j*info.xres_virtual + i] == 0xffffffff) ||
                (ptr[j*info.xres_virtual + i] == tron->color) ) {
              d++;
            if(d>1){
           end(enemy_color);
  
            d = 0;
              }
                }
          }
        }
      }
      tron -> prev_key = 'a';
      *x = (*x + info.xres -1)%info.xres;
    }
    if(tron->side == (4)){
      if(tron->prev_key == 'w'){
        nap_b = 'w';
        for(int i=(*x)+2;i<(*x)+10;i++){
          for(int j=(*y)-2;j<(*y)+3;j++){
            if((ptr[j*info.xres_virtual + i] == enemy_color) ||
                (ptr[j*info.xres_virtual + i] == 0xffffffff) ||
                (ptr[j*info.xres_virtual + i] == tron->color)) {
            d++;
            if(d>1){
        
              end(enemy_color);
            d = 0;
              }
                }
          }
        }
        print_black(*x,*y,nap_b);
      }
      if(tron->prev_key == 's'){
        nap_b = 's';
        for(int i=(*x)+2;i<(*x)+10;i++){
          for(int j=(*y)-2;j<(*y)+3;j++){
            if((ptr[j*info.xres_virtual + i] == enemy_color) ||
                (ptr[j*info.xres_virtual + i] == 0xffffffff) ||
                (ptr[j*info.xres_virtual + i] == tron->color)) {
            d++;
            if(d>1){
           
              end(enemy_color);
            d = 0;
              }
                }
          }
        }
        print_black(*x,*y,nap_b);
      }
      if(tron->prev_key == 'a'){
        for(int i=(*x)+2;i<(*x)+10;i++){
          for(int j=(*y)-2;j<(*y)+3;j++){
            if((ptr[j*info.xres_virtual + i] == enemy_color) ||
                (ptr[j*info.xres_virtual + i] == 0xffffffff) ||
                (ptr[j*info.xres_virtual + i] == tron->color)) {
            d++;
            if(d>1){
            
              end(enemy_color);
            d = 0;
              }
                }
          }
        }
      }
      tron -> prev_key = 'd';

      *x = (*x+1)%info.xres;
    }
    ptr[*y * info.xres_virtual + *x] = tron->color;
    for(int a = 0;a<info.yres;a++){
            ptr[a * info.xres_virtual] = 0xffffffff;
          }
    for(int a=0;a<info.xres;a++){
          ptr[0*info.xres_virtual + a] = 0xffffffff;
        }
    for(int a=0;a<info.xres;a++){
        ptr[(info.yres-1) * info.xres_virtual + a] = 0xffffffff;
      }
    for(int a=0;a<info.yres;a++){
        ptr[a*info.xres_virtual +(info.xres-1)] = 0xffffffff;
      }
      char o = tron->side+100;
      switch(o){
        case 'e':
          nap_tron = 'w';
          print(tron,*x,*y,enemy_color,nap_tron);
          break;
        case 'f':
          nap_tron = 's';
          print(tron,*x,*y,enemy_color,nap_tron);
          break;
        case 'g':
          nap_tron = 'a';
          print(tron,*x,*y,enemy_color,nap_tron);
          break;
        case 'h':
          nap_tron = 'd';
          print(tron,*x,*y,enemy_color,nap_tron);
          break;
        default:
          break;
      }
    usleep(62500);
}

void* game(void *args){
  pthread_t thread,thread2;
  tron me,enemy;
  if(sum1>sum2){
       me.x = 0;
       me.y = 3;
       me.color = 0xff0000;
       me.side = 4;
       me.prev_key = '.';
       enemy.x = info.xres - 1;
       enemy.y = info.yres - 4;
       enemy.color = 0x01009999;
       enemy.side = 3;
       enemy.prev_key = '.';
       me.enemy_color = enemy.color;
       enemy.enemy_color = me.color;
       pthread_create(&thread, NULL, keyboard_check, &me);
       pthread_create(&thread2, NULL, enemy_keyboard_check, &enemy);

  }
  else if(sum2>sum1){
      me.x = info.xres - 1;
      me.y = info.yres - 4;
      me.color = 0x01009999;
      me.side = 3;
      me.prev_key = '.';
      enemy.x = 0;
      enemy.y = 3;
      enemy.color = 0xff0000;
      enemy.side = 4;
      enemy.prev_key = '.';
      me.enemy_color = enemy.color;
      enemy.enemy_color = me.color;
      pthread_create(&thread, NULL, keyboard_check, &me);//выставляет клавиши
      pthread_create(&thread2, NULL, enemy_keyboard_check, &enemy);//выставляет клавиши

  }
  while(1)
  {
      if (char_my == 'w' && me.y < 10 ||
          char_my == 's' && me.y > info.yres-10 ||
          char_my == 'a' && me.x < 10 ||
          char_my == 'd' && me.x > info.xres-10){

          printf("Border!\n\r");
          usleep(62500);
          end(me.enemy_color);
        }

      game_start(&me,&me.x,&me.y,me.enemy_color);

      if (char_enemy == 'w' && enemy.y < 10 ||
          char_enemy == 's' && enemy.y > info.yres-10 ||
          char_enemy == 'a' && enemy.x < 10 ||
          char_enemy == 'd' && enemy.x > info.xres-10){

          printf("Border!\n\r");
          usleep(62500);
          end(enemy.enemy_color);
      }

      game_start(&enemy,&enemy.x,&enemy.y,enemy.enemy_color);
  }
  pthread_join(thread,NULL);
  pthread_join(thread2,NULL);
}

int main(int argc, char *argv[]){
    int fi[4];
    int args[2];

    if(argc < 5){
      printf("Запускать %s 800 600 айпи_свой айпи_соперника\n\r",argv[0]);
      exit(0);
    }

    args[0] = atoi(argv[1]);
    args[1] = atoi(argv[2]);

	  sscanf(argv[3],"%d.%d.%d.%d",&fi[0],&fi[1],&fi[2],&fi[3]);
    sum1 = fi[0]+fi[1]+fi[2]+fi[3];
	  sscanf(argv[4],"%d.%d.%d.%d",&fi[0],&fi[1],&fi[2],&fi[3]);
    sum2 = fi[0]+fi[1]+fi[2]+fi[3];

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
    int sock = 0;
    if ( (sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        munmap(ptr, map_size);
        exit(EXIT_FAILURE);
    }
    me.sin_family    = AF_INET;
    me.sin_addr.s_addr = inet_addr((argv[3]));
    me.sin_port = htons(12345);
    other.sin_family = AF_INET;
    other.sin_addr.s_addr = inet_addr((argv[4]));
    other.sin_port = htons(12345);
    if ( bind(sock, (const struct sockaddr *)&me,sizeof(me)) < 0 )
    {
        perror("bind failed");
        munmap(ptr, map_size);
        exit(EXIT_FAILURE);
    }
    comm_t comm1, comm2;
    comm1.socket = comm2.socket = sock;
    comm1.send = 1;
    pthread_t thread_key1, thread_key2, thread_game;

    pthread_create(&thread_key1,NULL, (void*)communicate, &comm1);//проверят нажатие
    comm2.send = 0;
    pthread_create(&thread_key2,NULL, (void*)communicate, &comm2);//проверяет нажатие

    while (char_my == '0' || char_enemy == '0') {} // ждет нажатия двух клавиш

    char_my = '0';
    char_enemy = '0';

    pthread_create(&thread_game, NULL, game, NULL);
    pthread_join(thread_game,NULL);
    pthread_join(thread_key1,NULL);
    pthread_join(thread_key2,NULL);
    munmap(ptr, map_size);
    close(fb);
  return 0;
}
