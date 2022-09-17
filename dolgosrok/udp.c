#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ncurses.h>
#include <pthread.h>

struct sockaddr_in me, other;
pthread_t thread_send,thread_recv,thread_press;
int my_fd;
int other_fd;
char my_ch = '0',other_ch = '0';
int size = sizeof(me);

void* press(){
    while(1){
        my_ch=getch();
    }
}
void* send_f(){
    while(1){
        sendto(my_fd,&my_ch,1,MSG_CONFIRM,(struct sockaddr*)&other,size);
        //mvprintw(0, 10, "sent to enemy_ip 1 byte is %c",my_ch);
    }
}
void* recvfrom_f(){
    while(1){
        recvfrom(my_fd,&other_ch,1,MSG_WAITALL,(struct sockaddr*)&me,&size);
            //mvprintw(1, 10, "receved to my_ip 1 byte is %c",other_ch);
            mvprintw(0, 10, "my %c, other %c",my_ch, other_ch);
            refresh();
    }
}

int main(int argc,char** argv){

    if(argc<3){
        printf("Usage: %s Your_ip enemy_ip\n",argv[0]);
        exit(EXIT_FAILURE);
    }
       if ( (my_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    me.sin_family    = AF_INET;
    me.sin_addr.s_addr = inet_addr((argv[1]));
    me.sin_port = htons(5050);
    if ( bind(my_fd, (const struct sockaddr *)&me,sizeof(me)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
     if ( (other_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    other.sin_family = AF_INET;
    other.sin_addr.s_addr = inet_addr((argv[2]));
    other.sin_port = htons(5050);

    if( NULL == initscr()) {
          return __LINE__;
        }

    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);

    pthread_create(&thread_press, NULL,press, NULL);
    pthread_create(&thread_send, NULL,send_f, NULL);
    pthread_create(&thread_recv,NULL,recvfrom_f,NULL);

    pthread_join(thread_recv,NULL);
    pthread_join(thread_send,NULL);
    pthread_join(thread_press,NULL);
    endwin();
    return 0;
}
