#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <pthread.h>

#include <ncurses.h>


typedef struct{

    int fd;
    int id;
    int death;
    uint32_t color;
    int x;
    int y;

} packet;

typedef struct{

    uint32_t *ptr;
    struct fb_var_screeninfo info;
    int fb;
    size_t fb_size;
    size_t map_size;
    size_t page_size;

} framebuff_args;


packet tron_pc[5];          // trones current data  
packet self;                // player's tron data 
framebuff_args framebuff;   
int stop = 0;
pthread_mutex_t mutex;


/////////////////////////////// [server and client] ////////////////////////////


int init_ncurses(){
    if( NULL == initscr() ) return -1;
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);
    return 0;
}


int init_framebuff(){
  framebuff.page_size = sysconf(_SC_PAGESIZE);
  
  if ( 0 > (framebuff.fb = open("/dev/fb0", O_RDWR))) {
    perror("open");
    return __LINE__;
  }

  if ( (-1) == ioctl(framebuff.fb, FBIOGET_VSCREENINFO, &framebuff.info)) {
    perror("ioctl");
    close(framebuff.fb);
    return __LINE__;
  }

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
    perror("mmap");
    close(framebuff.fb);
    return __LINE__;
  }
  
  return 0;
}


void create_rectangle(int x1, int y1, int x2, int y2, uint32_t border_color){
    int i = 0;
    for (i = y1; i < y2; i++)
      framebuff.ptr[i * framebuff.info.xres_virtual + x1] = border_color;
    for (i = x2; i > x1; i--)
      framebuff.ptr[y2 * framebuff.info.xres_virtual + i] = border_color;
    for (i = x1; i < x2; i++)
       framebuff.ptr[y1 * framebuff.info.xres_virtual + i] = border_color;
    for (i = y2; i > y1; i--)
       framebuff.ptr[i * framebuff.info.xres_virtual + x2] = border_color;

}


int print_deaths(){
    for (int i = 0; i<5; i++)
          if (tron_pc[i].death) 
                mvprintw(tron_pc[i].id, 70, "tron %d is dead", tron_pc[i].id);
    refresh(); 
}


int print_details(packet tron){
    framebuff.ptr[100 * framebuff.info.xres_virtual + 510] = tron.color;
    mvprintw(5, 70, " <- my color, id %d", tron.id);
}


int print_trones(){
    for(int i = 0; i<4; i++)
        framebuff.ptr[tron_pc[i].y * framebuff.info.xres_virtual + tron_pc[i].x] = tron_pc[i].color;
    create_rectangle(0, 0, 500, 500, 0xfd5e53);
    create_rectangle(100, 100, 200, 200, 0xfd5e53);
}


int keyboard_handler(void){
    
    int x = 0, y = 0, ch = 0;
    while(1) {
	    if (!stop){
	        pthread_mutex_lock(&mutex);
	        x = self.x, y = self.y;
	        ch = getch();
	            switch(ch) {
	                case 'w':
	                    y = (y + 500 - 1) % 500 ;
	                    break;
	                case 's':
	                    y = (y + 1) % 500;
	                    break;
	                case 'a':
	                    x = (x + 500 - 1) % 500;
	                    break;
	                case 'd':
	                    x = (x + 1) % 500;
	                    break;
	                default:
	                    break;
	            }
	        self.x = x;
            self.y = y;
            stop = 1;
            pthread_mutex_unlock(&mutex);
	    }
    }
}


////////////////////////////// [server] ////////////////////////////////////////


int init_host(char *ip, int port){

	typedef struct sockaddr_in Addr_struct;
	Addr_struct servAddr;

	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	servAddr.sin_addr.s_addr  = inet_addr(ip);

	int host_fd = socket(AF_INET, SOCK_STREAM, 0);
	int bind_flag = bind(host_fd, (const struct sockaddr *)&servAddr, sizeof(servAddr));

	if ( bind_flag != -1 ) {}
    return host_fd;
}


int check_death(packet tron){   
    if (tron.color != framebuff.ptr[tron.y * framebuff.info.xres_virtual + tron.x] && \
        framebuff.ptr[tron.y * framebuff.info.xres_virtual + tron.x] != 0 )
        return 1;
    return 0;
}


void packet_transmit(packet tron){
    packet buf;
    
    send(tron.fd, tron_pc, sizeof(packet)*5, 0);    
    if (tron_pc[tron.id].death == 0){
        recv(tron.fd, &tron_pc[tron.id], sizeof(packet), 0);
        tron_pc[tron.id].death = check_death(tron);
    }
    else recv(tron.fd, &buf, sizeof(packet), 0);
}


void client_handler(int host_fd){
    int client_fd = 0, incoming_connection = 0, id = -1;
    
    mvprintw(0, 10, "%s","Waiting for other players\n");
    incoming_connection = listen(host_fd, 10);
    
    while (++id < 3){
    
        client_fd = accept(host_fd, NULL, NULL);
        mvprintw(0, 10, "new connection:%d\n", client_fd);
        refresh();
        
        if (id == 0) 
            tron_pc[id] = (packet) {.fd=client_fd, .id=id, .death=0, .color=0x00ff00, .x=490, .y=10};
        if (id == 1) 
            tron_pc[id] = (packet) {.fd=client_fd, .id=id, .death=0, .color=0x1e90ff, .x=490, .y=490};
        if (id == 2) 
            tron_pc[id] = (packet) {.fd=client_fd, .id=id, .death=0, .color=0xffffff, .x=10, .y=490};
    }
    
    // server always have id 3 and always became tron number 4
    self = tron_pc[3] = (packet) {.fd=host_fd, .id=3, .death=0, .color=0xff00ff, .x=10, .y=10}; 
    
    send(tron_pc[0].fd, &tron_pc[0], sizeof(packet), 0);    // initialize tron1
    send(tron_pc[1].fd, &tron_pc[1], sizeof(packet), 0);    // initialize tron2
    send(tron_pc[2].fd, &tron_pc[2], sizeof(packet), 0);    // initialize tron3

}


void game(){   
    mvprintw(0, 10, "                                         ");
    refresh();
    print_details(self);
    
    while (1){
        stop = 0;
        tron_pc[3] = self; // prepare server data to transmit
        packet_transmit(tron_pc[0]);
        packet_transmit(tron_pc[1]);
        packet_transmit(tron_pc[2]);
        if ( !self.death && check_death(self) ) self.death = 1;
        print_trones();    // after getting all coordinates print them 
        print_deaths();
    }
}


////////////////////////////// [client] ////////////////////////////////////////


int get_server_fd(char *ip, int port){

	int client_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	typedef struct sockaddr_in Addr_struct;
	Addr_struct servAddr;
	
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	servAddr.sin_addr.s_addr = inet_addr(ip);
	
	int connection;
	connection = connect(client_fd, (const struct sockaddr *)&servAddr, sizeof(servAddr)); 
	if ( connection == 0 ) {/*printf("connected %d\n", sock)*/;} 
	else if ( connection == -1 ){ perror("[!]connect(): "); }
	//close(sock);
	return client_fd;
}


int recv_packet(void* server_fd){
   
    mvprintw(0, 10, "                                                 ");
    mvprintw(1, 10, "                                                 ");
    refresh();
    
    while (1){
        stop = 0;
        recv(*(int*)server_fd, tron_pc, sizeof(packet)*5, 0);
        print_trones();
        print_deaths();
        send(*(int*)server_fd, &self, sizeof(packet), 0);   
    }
    return 0;
}


////////////////////////////// [main] //////////////////////////////////////////


int main(int argc, char *argv[]){
    if (argc != 4)
        {printf("[!] Error: usage: ./tron ip port [h/c]\n"); return -1;}

    init_ncurses(); 
    init_framebuff();
    pthread_t keyboard;
    
    pthread_mutex_init(&mutex, NULL);
    
    if ( argv[3][0] == 'h' ){   
        mvprintw(0, 10, "host activated"); 
        refresh();

        int host_fd = init_host( argv[1], atoi(argv[2]) );
        client_handler(host_fd);
        pthread_create(&keyboard, NULL, (void*)keyboard_handler, NULL);
        
        game();
        pthread_join(keyboard, NULL);
    }

    if ( argv[3][0] == 'c' ){
        mvprintw(0, 10, "client activated");
        refresh();
        
        int server_fd = get_server_fd( argv[1], atoi(argv[2]) );
        
        mvprintw(1, 10, "sucsessfully connected. whaiting players");
        refresh();
        
        recv(server_fd, &self, sizeof(packet), 0); // initialize tron
        print_details(self);
        
        pthread_t packet;
        
        pthread_create(&packet, NULL, (void*)recv_packet, &server_fd);
        pthread_create(&keyboard, NULL, (void*)keyboard_handler, NULL);
        
        pthread_join(keyboard, NULL);
        pthread_join(packet, NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    return 0;
}
