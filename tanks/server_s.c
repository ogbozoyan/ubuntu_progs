#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[]) {
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[1025];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0); #descriptor socket
    memset(&serv_addr, '0', sizeof(serv_addr)); #filling serv_addr by 0
    memset(sendBuff, '0', sizeof(sendBuff));  #filling sendbuff by 0

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));#connecting socket with ip

    listen(listenfd, 3); #listen up to 3 clients

    while(1) {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);#connection / potok
                                                                                                                                                                              
        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(connfd, sendBuff, strlen(sendBuff)); #write to connfd 

        close(connfd);
        sleep(1);
     }
}