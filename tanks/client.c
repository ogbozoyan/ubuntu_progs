#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[])

{
    int cd; #socket descrptor
    struct sockaddr_in addr;
    
    if ( 0 > (cd = socket(AF_INET, SOCK_STREAM, 0))) {
	perror("Error calling socket");
	return __LINE__;
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(2021);
    addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
    
    
    if ( (-1) == connect(cd,(struct sockaddr *)&addr, sizeof(addr))) {
	perror("connect");
	return __LINE__;
    }
    
    send(cd,"Hello, World\n",14,0);
    close(cd);
    return 0;
}
