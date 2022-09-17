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

int Socket(int domain, int type , int protocol);
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen); //same debuger
void Listen(int sockfd , int backlog);
int Accept(int sockfd, struct sockaddr *addr ,socklen_t *addrlen);
void Connect(int sockfd,const struct sockaddr *addr ,socklen_t addrlen);
int64_t getFileSize(const char* file_name);

int main(int argc, char *argv[]){

    int server = 0; 
    int n=0;
    int client;

    struct sockaddr_in serv_addr;

    server = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    client = connect(server, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (client ==-1) {
        perror("check connect");
        exit(EXIT_FAILURE);
    }
    char name[30];
    fprintf(stdout, "Enter name of file: ");
    scanf("%s",name);
    int64_t fsize = getFileSize(name);
    char sendbuffer[fsize];
    
    FILE *file = fopen(name, "rb");
    if(file == NULL){
        perror("File not exist");
        exit(EXIT_FAILURE);
    }

    while( (client = fread(sendbuffer, 1, sizeof(sendbuffer), file))>0 ){
        send(server, sendbuffer, client, 0);
    }

    fclose(file);
    close(server);
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
	/*if((file_size%8) == 0){
		file_size = file_size/8;
	}
	else if ((file_size%8) != 0){
		file_size = (file_size/8)+1;
	}*/
	/*
	int i = 0;
	int count = 0;
	FILE* handle = fopen("file.txt","r");
	int64_t file_size = getFileSize("file.txt");
	if((file_size%8) == 0){
		file_size = file_size/8;
	}
	else if ((file_size%8) != 0){
		file_size = (file_size/8)+1;
	}
	
	char buf[file_size];
	char* tmp;
	//в buf[i] сохранено по 8 байт
	while(!feof(handle)){
		if(count !=8 ){
			buf[i] = fgetc(handle);
			count++;
		}
		else if(count == 8){
			i++;
			count = 0;
		}
	//	tmp = fgets(buf,8,handle);
	//	printf("%c(%d) ",buf[i],i);
	//}
	*/
//client


	/*
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
    
    int client_soc = Socket(AF_INET, SOCK_STREAM, 0);

    Connect(client_soc,(struct sockaddr *)&addr, sizeof(addr));
    
    buf[0] = "Hello World\n";

    send(client_soc,buf[0],16,0);
    close(client_soc);
    */
/*
int main(int argc, char* argv[])
{
	int b;
	struct sockaddr_in addr;
    char rbuff[1024];
	memset(rbuff, '0', sizeof(rbuff));
    
    FILE* handle = fopen("file.txt","rb");
	int64_t file_size = getFileSize("file.txt");
	char sendbuffer[file_size];
    
    int client_soc = Socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
 
    b = connect(client_soc,(struct sockaddr *)&addr, sizeof(addr));

    while( (b = fread(sendbuffer,100, sizeof(sendbuffer), handle))>0 ){
        send(client_soc, sendbuffer, b, 0);
    }
    fclose(handle);
    close(b);
    return 0;
}

*/