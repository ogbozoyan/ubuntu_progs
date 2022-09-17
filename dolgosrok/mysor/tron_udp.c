#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <ncurses.h>
#include <pthread.h>

#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define NAP 50

typedef struct sockaddr_in Addr_struct;
typedef struct{

    uint32_t *ptr;
    struct fb_var_screeninfo info;
    int fb;
    size_t fb_size;
    size_t map_size;
    size_t page_size;

} framebuff_args;
framebuff_args framebuff;  

typedef struct{

    int key;
    int x;
    int y;
    uint32_t color; 

} packet;

packet self;
int work_flag = 1;

int init_ncurses(){
    if( NULL == initscr() ) return -1;
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);
    return 0;
}


int init_framebuff(){
    framebuff.page_size = sysconf(_SC_PAGESIZE);
  
    if ( 0 > (framebuff.fb = open("/dev/fb0", O_RDWR)))
        handle_error("open");

    if ( (-1) == ioctl(framebuff.fb, FBIOGET_VSCREENINFO, &framebuff.info)) 
        handle_error("ioctl");

    framebuff.fb_size  = sizeof(uint32_t) * \
                       framebuff.info.xres_virtual * \
                       framebuff.info.yres_virtual;
    framebuff.map_size = (framebuff.fb_size + \
                       (framebuff.page_size - 1 )) & (~(framebuff.page_size-1));

    framebuff.ptr      = mmap(NULL, \
                            framebuff.map_size, \
                            PROT_READ | PROT_WRITE, \
                            MAP_SHARED, \
                            framebuff.fb, 0);
                            
    if ( MAP_FAILED == framebuff.ptr ){
        close(framebuff.fb);
        handle_error("mmap");
    }
  
    return 0;
}


int keyboard_handler(void){
    
    int ch = 0;
    while(work_flag) {
	    ch = getch();
	    self.key = ch;
	}
}


int game_over(){
    mvprintw(10, 10, "game over");
    refresh();
    work_flag = 0;
    napms(1000);
}


int print_tron(packet tron, int* x, int* y, uint32_t op_color){

    switch(tron.key) {
        case 'w':
            *y = (*y + 500 - 1) % 500;
            break;
        case 's':
            *y = (*y + 1) % 500;
            break;
        case 'a':
            *x = (*x + 500 - 1) % 500;
            break;
        case 'd':
            *x = (*x + 1) % 500;
            break;
        default:
            break;
    }
    if ( framebuff.ptr[*y * framebuff.info.xres_virtual + *x] == op_color)
        game_over();
        
    //if ( framebuff.ptr[*y * framebuff.info.xres_virtual + *x] == tron.color)
    //    game_over();
        
    framebuff.ptr[*y * framebuff.info.xres_virtual + *x] = tron.color;
}  


int start_game(int fd, Addr_struct addr_struct, int host){

    int start = 1;
    int client_address_size = sizeof(addr_struct);
    int host_address_size = 0;
    
    if (host){
        packet client;
        packet host;
        
        host.key = 'd';
        host.color = 0xff0000;
        host.x = 10;
        host.y = 10;
        
        client.key = 'a';
        client.color = 0x0001f6;
        client.x = 400;
        client.y = 10;
        
        self = host;
        
        mvprintw(0, 0, "ip: %s\n", inet_ntoa(addr_struct.sin_addr));

        if ( recvfrom(fd, &start, sizeof(int), MSG_WAITALL, (struct sockaddr*)&addr_struct, &client_address_size) < 0 )
            handle_error("recvfrom");
            
        if ( sendto(fd, &client, sizeof(packet), MSG_CONFIRM, (struct sockaddr*)&addr_struct, client_address_size) < 0 )
            handle_error("sendto");
            
        if ( sendto(fd, &host, sizeof(packet), MSG_CONFIRM, (struct sockaddr*)&addr_struct, client_address_size) < 0 )
            handle_error("sendto");
            
        int h_x = host.x;
        int h_y = host.y;
        
        int c_x = client.x;
        int c_y = client.y;

        while(work_flag){
            host = self;
            recvfrom(fd, &client, sizeof(packet), MSG_WAITALL, (struct sockaddr*)&addr_struct, &client_address_size);
            sendto(fd, &host, sizeof(packet), MSG_CONFIRM, (struct sockaddr*)&addr_struct, client_address_size);
            print_tron(client, &c_x, &c_y, host.color);
            print_tron(host, &h_x, &h_y, client.color);
            napms(NAP);
        }
    }
    else{
    
        packet client;
        packet host;
        
        if ( sendto(fd, &start, sizeof(int), MSG_CONFIRM, (struct sockaddr*)&addr_struct, sizeof(addr_struct)) < 0 )
            handle_error("sendto");
        
        if ( recvfrom(fd, &client, sizeof(packet), MSG_WAITALL, (struct sockaddr*)&addr_struct, &host_address_size) < 0 ) // wait host data
            handle_error("recvfrom");
            
        if ( recvfrom(fd, &host, sizeof(packet), MSG_WAITALL, (struct sockaddr*)&addr_struct, &client_address_size) < 0 ) // wait host data
            handle_error("recvfrom");
            
        self = client;
        
        int h_x = host.x;
        int h_y = host.y;
        
        int c_x = client.x;
        int c_y = client.y;
        
        while(work_flag){
            client = self;
            sendto(fd, &client, sizeof(packet), MSG_CONFIRM, (struct sockaddr*)&addr_struct, sizeof(addr_struct));
            recvfrom(fd, &host, sizeof(packet), MSG_WAITALL, (struct sockaddr*)&addr_struct, &client_address_size);
            print_tron(client, &c_x, &c_y, host.color);
            print_tron(host, &h_x, &h_y, client.color);
            napms(NAP);
            
        }
    }
    
}


int init_client(char *ip, int port){

	int client_fd = 0;
	if ( (client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
        handle_error("socket creation failed");
	
	return client_fd;
}


int init_host(char *ip, int port, Addr_struct hostAddr){

	int host_fd = 0;
	if ( (host_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
        handle_error("socket creation failed");
    
	if ( bind(host_fd, (const struct sockaddr*)&hostAddr, sizeof(hostAddr)) < 0 )
        handle_error("bind failed");
        
    return host_fd;
}


int main(int argc, char *argv[]){
    if (argc != 4){
        printf("Usage: %s <ip> <port> h for host\n", argv[0]);
        printf("Usage: %s <ip> <port> c for client\n", argv[0]);
        return -1;}
    //sockaddr_in
    Addr_struct hostAddr;
    Addr_struct clientAddr;

    pthread_t keyboard;
    init_ncurses();
    init_framebuff();
    
    memset(&hostAddr, 0, sizeof(hostAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));

    hostAddr.sin_family      = AF_INET;
    hostAddr.sin_port        = htons(atoi(argv[2]));
	hostAddr.sin_addr.s_addr = inet_addr(argv[1]);
    
    if ( argv[3][0] == 'h' ){  

	    pthread_create(&keyboard, NULL, (void*)keyboard_handler, NULL);
	    
        int host_fd = init_host( argv[1], atoi(argv[2]), hostAddr);
        start_game(host_fd, hostAddr, 1);
        
        pthread_join(keyboard, NULL);
        
    }

    if ( argv[3][0] == 'c' ){
    
	    pthread_create(&keyboard, NULL, (void*)keyboard_handler, NULL);

        int client_fd = init_client( argv[1], atoi(argv[2]));
        start_game(client_fd, hostAddr, 0);
        
        pthread_join(keyboard, NULL);
        
    }
    
    return 0;
}
