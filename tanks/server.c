#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
    int sd, cd;
    struct sockaddr_in addr;
    char msg[16];
    int msglen;
    
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if( sd < 0 ) {
	perror("Error calling socket");
	return __LINE__;
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(2021);
    addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );

    if( bind(sd, (struct sockaddr *)&addr, sizeof(addr)) < 0 ) {
	perror("Bind");
	return __LINE__;
    }
    
    if( listen(sd, 5) ) {
	perror("Listen");
	return __LINE__;
    }
    
    if (  0 > (cd = accept(sd, NULL, NULL)) ){
	perror("Accept");
	return __LINE__;
    }

    msglen = recv(cd, msg, 16, 0);
    if ( msglen > 0 ) write(1, msg, msglen);
    close(cd);
    close(sd);
    return 0;
}
