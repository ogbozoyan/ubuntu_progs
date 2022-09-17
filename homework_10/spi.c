#include <ncurses.h>
#include <stdio.h>
#include <time.h>
struct snk{
    int x[5];
    int y[5];
};


void set(struct snk *snake){
    for(int i=0; i<5; i++){
        snake->x[i]=COLS/2;
        snake->y[i]=LINES/2;        
    }
}

void clean_tail(struct snk *snake){
    int x,y;
    x=snake->x[4];
    y=snake->y[4];   
    mvaddch(y,x,' ');
}

void right(struct snk *snake){
    for(int i=4;i>0;i--){
        snake->x[i]=snake->x[i-1];
        snake->y[i]=snake->y[i-1];
    }
    snake->x[0]=(snake->x[0] + 1)%COLS;
}

void left(struct snk *snake){
    for(int i=4;i>0;i--){
        snake->x[i]=snake->x[i-1];
        snake->y[i]=snake->y[i-1];
    }
    snake->x[0]=(snake->x[0] + COLS - 1)%COLS;
}

void up(struct snk *snake){
    for(int i=4;i>0;i--){
        snake->x[i]=snake->x[i-1];
        snake->y[i]=snake->y[i-1];
    }
    snake->y[0]=(snake->y[0] + LINES - 1)%LINES;
}

void down(struct snk *snake){
    for(int i=4;i>0;i--){
        snake->x[i]=snake->x[i-1];
        snake->y[i]=snake->y[i-1];
    }
    snake->y[0]=(snake->y[0] + 1)%LINES;
}


int main(int argc, char *argv[])
{
    int ch = 0;
    struct snk snk_u;
    struct snk snk_d;
    struct snk snk_r;
    struct snk snk_l;
    
    
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);
    
    set(&snk_u);
    set(&snk_d);
    set(&snk_r);
    set(&snk_l);
    

    while(ch != 'q'){
        for(int i=4; i>=0; i--){
            mvaddch(snk_u.y[i], snk_u.x[i], '*');
            mvaddch(snk_d.y[i], snk_d.x[i], '*');
            mvaddch(snk_l.y[i], snk_l.x[i], '*');
            mvaddch(snk_r.y[i], snk_r.x[i], '*');
            refresh();
        }
        ch=getch();
        clean_tail(&snk_u);
        clean_tail(&snk_d);
        clean_tail(&snk_l);
        clean_tail(&snk_r);
        
        switch(ch) {
        case KEY_UP:
            up(&snk_u);
            left(&snk_l);
            right(&snk_r);
            down(&snk_d);
            break;
        case KEY_DOWN:
            up(&snk_d);
            left(&snk_r);
            right(&snk_l);
            down(&snk_u);
            break;
        case KEY_LEFT:
            up(&snk_r);
            left(&snk_u);
            right(&snk_d);
            down(&snk_l);
            break;
        case KEY_RIGHT:
            up(&snk_l);
            left(&snk_d);
            right(&snk_u);
            down(&snk_r);
            break;
        default:
            break;
        }
    }
    endwin();
   
    return 0;
}
