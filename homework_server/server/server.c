#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h> // для int64_t
#include <inttypes.h> // для правильного вывода int64_t в printf
#include <math.h>
//server
int Socket(int domain, int type , int protocol);
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen); //same debuger
void Listen(int sockfd , int backlog);
int Accept(int sockfd, struct sockaddr *addr ,socklen_t *addrlen);
void Connect(int sockfd,const struct sockaddr *addr ,socklen_t addrlen);
int64_t getFileSize(const char* file_name);



int main(int argc, char *argv[]){

    int server = 0; 
    int client = 0;
    int bin;
    struct sockaddr_in serv_addr;

    char buff[100000000];


    server = socket(AF_INET, SOCK_STREAM, 0);
    


    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
    serv_addr.sin_port = htons(8080);

    bind(server, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(server, 5);

    while(1){
        client = accept(server, (struct sockaddr*)NULL, NULL);
        if (client==-1) {
            perror("check accept");
            continue;
        }
        FILE* file = fopen( "get.txt", "wb");
        if(file != NULL){
            while( (bin = recv(client, buff, 1,0)) > 0 ) {
                fwrite(buff, 1, bin, file);//записываем в файл
            }
            fprintf(stdout,"done\n");
            if (bin<0)
               perror("check recv");

            fclose(file);
        } else {
            perror("File don't exist");
        }
        close(client);
    }

    return 0;
}


int64_t getFileSize(const char* file_name){
    int64_t _file_size = 0;
    FILE* fd = fopen(file_name, "rb");
    if(fd == NULL){
        _file_size = -1;
    }
    else{
        while(getc(fd) != EOF)
            _file_size++;
        fclose(fd);
    }
    
    
    return _file_size;

}

void Connect(int sockfd,const struct sockaddr *addr ,socklen_t addrlen){
	int res = connect(sockfd,addr,addrlen);
	if (res == -1 ){
		perror("check connect \n");
		exit(EXIT_FAILURE);
	}
}

int Accept(int sockfd, struct sockaddr *addr ,socklen_t *addrlen){
	int res = accept(sockfd ,addr , addrlen);
	if (res == -1){
		perror("check accept \n");
		exit(EXIT_FAILURE);
	}
	return res;
}

void Listen(int sockfd , int backlog){
	int res = listen(sockfd,backlog);
	if (res == -1 ){
		perror("chek listen \n");
		exit(EXIT_FAILURE);
	}
		
}
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) //same debuger
{
	int res = bind(sockfd,addr,addrlen);
	if (res == -1 ){
		perror("chek bind \n");
		exit(EXIT_FAILURE);
	}

}

int Socket(int domain, int type , int protocol){ //reinit socket funck for debug
	int res = socket(domain, type, protocol);
	if (res == -1 ){ //eror
		perror("check socket,there's error \n");
		exit(EXIT_FAILURE);
	}
	return res;
}
/*
int main(){
	char* buf;
	buf = (char*)malloc(sizeof(char));
	int msglen;
	
	int server = Socket(AF_INET , SOCK_STREAM , 0);
	struct sockaddr_in adr = {0}; //that's for searching in any ip's
	adr.sin_family = AF_INET;
	adr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
	adr.sin_port = htons(8080); //listen this port
	
	Bind(server, (struct sockaddr*) &adr, sizeof adr);
	
	Listen(server,5);
	socklen_t len_of_adr = sizeof adr;

	int client_soc = Accept(server, NULL, NULL);

/*
	ssize_t nread;
	while(nread != 0){
	nread = read(client_soc, buf, 8);
	}
	if (nread == -1){
		perror("check read \n");
		exit(EXIT_FAILURE);
	}
	else if (nread == 0 ){
		
		fprintf(stdout ,"%d\n",sizeof(nread)); //client don't sent nothing anymore
	}
	
	//write(STDOUT_FILENO,buf,nread);
	//write(client_soc,buf,nread);
	//close(client_soc);
	//close(listen);
	

*/
	//msglen = recv(client_soc, buf, 8, 0);
    //if ( msglen > 0 ){
     //write(1, buf, msglen);
    // msglen = 0;
  //   }	
//	return 0;
//}
