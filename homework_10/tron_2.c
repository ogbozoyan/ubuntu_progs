#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>


/*
at first check_touch(&biker_u,&biker_d,&biker_r,&biker_l)
second check_alive(&biker_u,&biker_d,&biker_r,&biker_l)
*/


int curr_size = 1;

struct bike{
	int x[6750];
	int y[6750];
	int score;
	int flag_of_death; //if death == 1
	int flag_of_online; //if client has connected  == 1 
};
//______________MOVEMENT__________
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
//____________________________________

//_______ZHIZNESPOSOBNOSTI_KEK________
void check_touch(struct bike *biker1,struct bike *biker2,struct bike *biker3,struct bike *biker4){
	//check that bike don't touch tail or head_to_head if they do => death , and also cheks that don't reach end of map
	// x - head , y[i] - body
	for(int i = curr_size;i>0;i--){
		
		if(((biker1->x[0]) == (biker2 -> y[i])) || ((biker1->x[0]) == (biker3 -> y[i]))
		|| ((biker1->x[0]) == (biker4 -> y[i])) || ((biker1->x[0]) == (biker1 -> y[i])))	
		{
			biker1 -> flag_of_death = 1;
			mvaddstr(0,50,"biker1 bump to body");
		}

		if(((biker2->x[0]) == (biker2 -> y[i])) || ((biker2->x[0]) == (biker3 -> y[i]))
		|| ((biker2->x[0]) == (biker4 -> y[i])) || ((biker2->x[0]) == (biker1 -> y[i])))	
		{
			biker2 -> flag_of_death = 1;
			mvaddstr(0,50,"biker2 bump to body");
		}

		if(((biker3->x[0]) == (biker2 -> y[i])) || ((biker3->x[0]) == (biker3 -> y[i]))
		|| ((biker3->x[0]) == (biker4 -> y[i])) || ((biker3->x[0]) == (biker1 -> y[i])))	
		{
			biker3 -> flag_of_death = 1;
			mvaddstr(0,50,"biker3 bump to body");
		}

		if(((biker4->x[0]) == (biker2 -> y[i])) || ((biker4->x[0]) == (biker3 -> y[i]))
		|| ((biker4->x[0]) == (biker4 -> y[i])) || ((biker4->x[0]) == (biker1 -> y[i])))	
		{
			biker4 -> flag_of_death = 1;
			mvaddstr(0,50,"biker4 bump to body");
		}
	}
		//head_to_head
		if(((biker1->x[0]) == (biker2 -> x[0])) || ((biker2->x[0]) == (biker1 -> x[0]))) 
		{ 
			biker1 -> flag_of_death = 1;
			biker2 -> flag_of_death = 1;
			mvaddstr(0,50,"biker1 and biker2 hth");
			
		}

		if(((biker1->x[0]) == (biker3 -> x[0])) || ((biker3->x[0]) == (biker1 -> x[0]))) 
		{ 
			biker1 -> flag_of_death = 1;
			biker3 -> flag_of_death = 1;
			mvaddstr(0,50,"biker1 and biker3 hth");
			
		}
		else if(((biker1->x[0]) == (biker4 -> x[0])) || ((biker4->x[0]) == (biker1 -> x[0]))) 
		{ 
			biker1 -> flag_of_death = 1;
			biker4 -> flag_of_death = 1;
			mvaddstr(0,50,"biker1 and biker4 hth");
			
		}
		else if(((biker4->x[0]) == (biker2 -> x[0])) || ((biker2->x[0]) == (biker4 -> x[0]))) 
		{ 
			biker2 -> flag_of_death = 1;
			biker4 -> flag_of_death = 1;
			mvaddstr(0,50,"biker2 and biker4 hth");
			
		}
		else if(((biker3->x[0]) == (biker2 -> x[0])) || ((biker2->x[0]) == (biker3 -> x[0]))) 
		{ 
			biker3 -> flag_of_death = 1;
			biker2 -> flag_of_death = 1;
			mvaddstr(0,50,"biker2 and biker3 hth");
			
		}
		else if(((biker3->x[0]) == (biker4 -> x[0])) || ((biker3->x[0]) == (biker4 -> x[0]))) 
		{ 
			biker3 -> flag_of_death = 1;
			biker4 -> flag_of_death = 1;
			mvaddstr(0,50,"biker3 and biker4 hth");
			
		}

		if((biker1 -> x[0]) == COLS+1 ||(biker1 -> x[0]) == LINES+1){
			biker1 -> flag_of_death = 1;
			mvaddstr(0,50,"biker1 border");
		}
		if((biker4 -> x[0]) == COLS+1 ||(biker4 -> x[0]) == LINES+1){
			biker4 -> flag_of_death = 1;
			mvaddstr(0,50,"biker4 border");
		}
		if((biker3 -> x[0]) == COLS+1 ||(biker3 -> x[0]) == LINES+1){
			biker3 -> flag_of_death = 1;
			mvaddstr(0,50,"biker3 border");
		}
		if((biker2 -> x[0]) == COLS+1 ||(biker2 -> x[0]) == LINES+1){
			biker2 -> flag_of_death = 1;
			mvaddstr(0,50,"biker2 border");
		}	
}

void check_alive(struct bike *biker){
	
	if((biker -> flag_of_death) == 1){
		biker -> score = curr_size;

		for(int i = 0; i<curr_size; i++){
			mvaddch(biker -> y[i],biker -> x[i],'\0');
		}
	}
}
//______________________________________

//___BESPOLEZNYA________________________
void set(struct bike *biker,int x,int y){
    biker -> flag_of_death = 0;
    biker -> score = 0;
    for(int i=0; i<curr_size; i++){
        biker->x[i]=COLS/2 + x - y;
        biker->y[i]=LINES/2 + y - x;        
}
}
//_______________________________________


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


    set(&biker_u,30,46);
    set(&biker_d,50,62);
    set(&biker_r,15,12);
    set(&biker_l,13,70);

    while(ch != 'q'){
        for(int i=curr_size; i>=0; i--){
            
            if(biker_u.flag_of_death != 1)
            	{mvaddstr(biker_u.y[i], biker_u.x[i], "^");}
            if(biker_d.flag_of_death != 1)
            	{mvaddstr(biker_d.y[i], biker_d.x[i], "&");}
            if(biker_l.flag_of_death != 1)
            	{mvaddstr(biker_l.y[i], biker_l.x[i], "#");}
            if(biker_r.flag_of_death != 1)
            	{mvaddstr(biker_r.y[i], biker_r.x[i], "*");}
            
            refresh();
        }
        //check_touch(&biker_u,&biker_d,&biker_r,&biker_l);
        ch=getch();
     
        
        switch(ch) {
        case KEY_UP:
	        check_alive(&biker_u);
	        check_alive(&biker_l);
	        check_alive(&biker_r);
	        check_alive(&biker_d);
            up(&biker_u);
            left(&biker_l);
            right(&biker_r);
            down(&biker_d);
            break;
        case KEY_DOWN:
	        check_alive(&biker_u);
	        check_alive(&biker_l);
	        check_alive(&biker_r);
	        check_alive(&biker_d);
            up(&biker_d);
            left(&biker_r);
            right(&biker_l);
            down(&biker_u);
            break;
        case KEY_LEFT:
	        check_alive(&biker_u);
	        check_alive(&biker_l);
	        check_alive(&biker_r);
	        check_alive(&biker_d);
            up(&biker_r);
            left(&biker_u);
            right(&biker_d);
            down(&biker_l);
            break;
        case KEY_RIGHT:
	        check_alive(&biker_u);
	        check_alive(&biker_l);
	        check_alive(&biker_r);
	        check_alive(&biker_d);
            up(&biker_l);
            left(&biker_d);
            right(&biker_u);
            down(&biker_r);
            break;
        default:
            break;
        }
        curr_size++;
        check_touch(&biker_u,&biker_d,&biker_r,&biker_l);
    }
    endwin();
   
    return 0;
}
/*
clock_t currentTime;
    currentTime = clock();
    for(int i = 6750;i>0;i--){
        x = i;
        y = x;
    }
    currentTime = clock() - currentTime;
    currentTime = (double)currentTime / CLOCKS_PER_SEC;
    printf("%ld",currentTime);
*/