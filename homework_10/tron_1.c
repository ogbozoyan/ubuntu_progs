#include <ncurses.h>
#include <stdio.h>
/*clock_t currentTime;
    currentTime = clock();
    for(int i = 6750;i>0;i--){
        x = i;
        y = x;
    }
    currentTime = clock() - currentTime;
    currentTime = (double)currentTime / CLOCKS_PER_SEC;
    printf("%ld",currentTime);
*/
int curr_size = 1;
struct bike{
	int x[6750];
	int y[6750];
	int flag_of_death; //if death == 1
	int flag_of_online; //if client has connected  == 1 
};

void right(struct bike *biker){
    for(int i=curr_size;i>0;i--){
        biker->x[i]=biker->x[i-1];
        biker->y[i]=biker->y[i-1];
    }
    biker->x[0]=(biker->x[0] + 1)%COLS;
}

void left(struct bike *biker){
    for(int i=curr_size;i>0;i--){
        biker->x[i]=biker->x[i-1];
        biker->y[i]=biker->y[i-1];
    }
    biker->x[0]=(biker->x[0] + COLS - 1)%COLS;
}

void up(struct bike *biker){
    for(int i=curr_size;i>0;i--){
        biker->x[i]=biker->x[i-1];
        biker->y[i]=biker->y[i-1];
    }
    biker->y[0]=(biker->y[0] + LINES - 1)%LINES;
}

void down(struct bike *biker){
    for(int i=curr_size;i>0;i--){
        biker->x[i]=biker->x[i-1];
        biker->y[i]=biker->y[i-1];
    }
    biker->y[0]=(biker->y[0] + 1)%LINES;
}

void set(struct bike *biker){
    for(int i=0; i<curr_size; i++){
        biker->x[i]=COLS/2;
        biker->y[i]=LINES/2;        
    }
}

int main(){
	int ch = 0;
	int curr_size = 1;
	initscr();
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);

    struct bike biker_u;
    struct bike biker_d;
    struct bike biker_r;
    struct bike biker_l;

    set(&biker_u);
    set(&biker_d);
    set(&biker_r);
    set(&biker_l);
    while(ch != 'q'){
        for(int i=curr_size; i>=0; i--){
            mvaddch(biker_u.y[i], biker_u.x[i], '*');
            mvaddch(biker_d.y[i], biker_d.x[i], '*');
            mvaddch(biker_l.y[i], biker_l.x[i], '*');
            mvaddch(biker_r.y[i], biker_r.x[i], '*');
            refresh();
        }
        ch=getch();
        //clean_tail(&biker_u);
        //clean_tail(&biker_d);
        //clean_tail(&biker_l);
        //clean_tail(&biker_r);
        
        switch(ch) {
        case KEY_UP:
            up(&biker_u);
            left(&biker_l);
            right(&biker_r);
            down(&biker_d);
            break;
        case KEY_DOWN:
            up(&biker_d);
            left(&biker_r);
            right(&biker_l);
            down(&biker_u);
            break;
        case KEY_LEFT:
            up(&biker_r);
            left(&biker_u);
            right(&biker_d);
            down(&biker_l);
            break;
        case KEY_RIGHT:
            up(&biker_l);
            left(&biker_d);
            right(&biker_u);
            down(&biker_r);
            break;
        default:
            break;
        }
        curr_size++;
    }
    endwin();
   
    return 0;
}
/*
#include <ncurses.h>
int main(int argc, char *argv[])
{
    int x = 0, y = 0, ch = 0;

    if( NULL == initscr()) {
	return __LINE__;
    }
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);
    do {
	mvaddch(y,x,' ');
	switch(ch) {
	case KEY_UP:
	    y = (y + LINES - 1) % LINES;
	    break;
	case KEY_DOWN:
	    y = (y + 1) % LINES;
	    break;
	case KEY_LEFT:
	    x = (x + COLS - 1) % COLS;
	    break;
	case KEY_RIGHT:
	    x = (x + 1) % COLS;
	    break;
	default:
	    break;
	}
	mvaddch(y,x,'*');
	refresh();
    }while('q' != (ch = getch()));
    endwin();
    return 0;
}
*/