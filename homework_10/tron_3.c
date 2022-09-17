#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>


/*
x_________________COLS
|
|
|
|
|
y LINES

at first check_touch(&biker_u,&biker_d,&biker_r,&biker_l)
second check_alive(&biker_u,&biker_d,&biker_r,&biker_l)
*/


int curr_size = 0;

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
int i = 2;
int s* = NULL;
s = (int*)realloc(s, i*(sizeof(body));
i = 3;

typedef struct{
    int x;
    int y;
    
}body;

//_______ZHIZNESPOSOBNOSTI_KEK________
bool check_touch(struct bike *biker1,struct bike *biker2,struct bike *biker3,struct bike *biker4 ){
	//check that bike don't touch tail or head_to_head if they do => death , and also cheks that don't reach end of map
	// x - head , y[i] - body
	for(int i = 6750;i>0;i--){
		
		if(( ((biker1->x[0]) == (biker2 -> x[i])) && ((biker1->y[0]) == (biker2 -> y[i])) ) || \
		   ( ((biker1->x[0]) == (biker3 -> x[i])) && ((biker1->y[0]) == (biker3 -> y[i])) ) || \
		   ( ((biker1->x[0]) == (biker4 -> x[i])) && ((biker1->y[0]) == (biker4 -> y[i])) ) )
		{
			biker1 -> flag_of_death = 1;
			mvwprintw(stdscr,2,COLS/2, "x1 - %d ,y2 - %d , y3 - %d, y4 -%d", biker1 -> x[0],biker2 -> y[i],biker3 -> y[i],
				biker4 -> y[i]);
			
			mvaddstr(0,50,"biker1 bump to body");
		}
		//if(((biker2->x[0]) == (biker2 -> y[i])) || ((biker2->x[0]) == (biker3 -> y[i]))
		//|| ((biker2->x[0]) == (biker4 -> y[i])) || ((biker2->x[0]) == (biker1 -> y[i])))	
		if(( ((biker2->x[0]) == (biker1 -> x[i])) && ((biker2->y[0]) == (biker1 -> y[i])) ) || \
		   ( ((biker2->x[0]) == (biker3 -> x[i])) && ((biker2->y[0]) == (biker3 -> y[i])) ) || \
		   ( ((biker2->x[0]) == (biker4 -> x[i])) && ((biker2->y[0]) == (biker4 -> y[i])) ) )
		{
			biker2 -> flag_of_death = 1;
			mvwprintw(stdscr,2,COLS/2, "x2 - %d ,y1 - %d , y3 - %d , y4 - %d", biker2 -> x[0],biker1 -> y[i],biker3 -> y[i],
				biker4 -> y[i]);
			mvaddstr(0,50,"biker2 bump to body");
			
		}

		//if(((biker3->x[0]) == (biker2 -> y[i])) || ((biker3->x[0]) == (biker3 -> y[i]))
		//|| ((biker3->x[0]) == (biker4 -> y[i])) || ((biker3->x[0]) == (biker1 -> y[i])))	
		if(( ((biker3->x[0]) == (biker2 -> x[i])) && ((biker3->y[0]) == (biker2 -> y[i])) ) || \
		   ( ((biker3->x[0]) == (biker1 -> x[i])) && ((biker3->y[0]) == (biker1 -> y[i])) ) || \
		   ( ((biker3->x[0]) == (biker4 -> x[i])) && ((biker3->y[0]) == (biker4 -> y[i])) ) )
		{
			biker3 -> flag_of_death = 1;
			mvwprintw(stdscr,2,COLS/2, "x3 - %d ,y1 - %d , y2 - %d , y4 - %d", biker3 -> x[0],biker1 -> y[i],biker2 -> y[i],
				biker4 -> y[i]);
			mvaddstr(0,50,"biker3 bump to body");
			 
		}

		//if(((biker4->x[0]) == (biker2 -> y[i])) || ((biker4->x[0]) == (biker3 -> y[i]))
		//|| ((biker4->x[0]) == (biker4 -> y[i])) || ((biker4->x[0]) == (biker1 -> y[i])))
		if(( ((biker4->x[0]) == (biker2 -> x[i])) && ((biker4->y[0]) == (biker2 -> y[i])) ) || \
		   ( ((biker4->x[0]) == (biker3 -> x[i])) && ((biker4->y[0]) == (biker3 -> y[i])) ) || \
		   ( ((biker4->x[0]) == (biker1 -> x[i])) && ((biker4->y[0]) == (biker1 -> y[i])) ) )	
		{
			biker4 -> flag_of_death = 1;
			mvwprintw(stdscr,2,COLS/2, "x4 - %d ,y1 - %d , y2 - %d , y3 - %d", biker4 -> x[0],biker1 -> y[i],biker2 -> y[i],
				biker3 -> y[i]);
			mvaddstr(0,50,"biker4 bump to body");
			
		}
	}
		//head_to_head
		if(((biker1->x[0]) == (biker2 -> x[0])) && ((biker1->y[0]) == (biker2 -> y[0]))) // || to &&
		{ 
			biker1 -> flag_of_death = 1;
			biker2 -> flag_of_death = 1;
			mvwprintw(stdscr,2,COLS/2, "x1 - %d ,x2 - %d", biker1 -> x[0],biker2 -> x[0]);
			mvwprintw(stdscr, 3,COLS/2, "y1 - %d , y2 - %d", biker1 -> y[0],biker2 -> y[0]);
			mvaddstr(0,50,"biker1 and biker2 hth");
			
		}

		else if(((biker1->x[0]) == (biker3 -> x[0])) && ((biker1->y[0]) == (biker3 -> y[0]))) 
		{ 
			biker1 -> flag_of_death = 1;
			biker3 -> flag_of_death = 1;
			mvwprintw(stdscr,2,COLS/2, "x1 - %d ,x3 - %d", biker1 -> x[0],biker3 -> x[0]);
			mvwprintw(stdscr, 3,COLS/2, "y - %d , y - %d", biker1 -> y[0],biker3 -> y[0]);
			mvaddstr(0,50,"biker1 and biker3 hth");
			
		}
		else if(((biker1->x[0]) == (biker4 -> x[0])) && ((biker4->y[0]) == (biker1 -> y[0]))) 
		{ 
			biker1 -> flag_of_death = 1;
			biker4 -> flag_of_death = 1;
			mvwprintw(stdscr,2,COLS/2, "x1 - %d ,x4 - %d", biker1 -> x[0],biker4 -> x[0]);
			mvwprintw(stdscr, 3,COLS/2, "y4 - %d , y4 - %d", biker1 -> y[0],biker4 -> y[0]);
			mvaddstr(0,50,"biker1 and biker4 hth");
			
		}
		else if(((biker4->x[0]) == (biker2 -> x[0])) && ((biker2->y[0]) == (biker4 -> y[0]))) 
		{ 
			biker2 -> flag_of_death = 1;
			biker4 -> flag_of_death = 1;
			mvwprintw(stdscr,2,COLS/2, "x2 - %d ,x4- %d", biker2 -> x[0],biker4 -> x[0]);
			mvwprintw(stdscr, 3,COLS/2, "y2 - %d , y4 - %d", biker2 -> y[0],biker4 -> y[0]);
			mvaddstr(0,50,"biker2 and biker4 hth");
			
		}
		else if(((biker3->x[0]) == (biker2 -> x[0])) && ((biker2->y[0]) == (biker3 -> y[0]))) 
		{ 
			biker3 -> flag_of_death = 1;
			biker2 -> flag_of_death = 1;
			mvwprintw(stdscr,2,COLS/2, "x3 - %d ,x2 - %d", biker3 -> x[0],biker2 -> x[0]);
			mvwprintw(stdscr, 3,COLS/2, "y3 - %d , y2 - %d", biker3 -> y[0],biker2 -> y[0]);
			mvaddstr(0,50,"biker2 and biker3 hth");
			
		}
		else if(((biker3->x[0]) == (biker4 -> x[0])) && ((biker3->y[0]) == (biker4 -> x[0]))) 
		{ 
			biker3 -> flag_of_death = 1;
			biker4 -> flag_of_death = 1;
			mvwprintw(stdscr,2,COLS/2, "x3 - %d ,x4 - %d", biker3 -> x[0],biker4 -> x[0]);
			mvwprintw(stdscr, 3,COLS/2, "y3 - %d , y4 - %d", biker3 -> y[0],biker4 -> y[0]);
			mvaddstr(0,50,"biker3 and biker4 hth");
			
		}
        /*
		if((biker1 -> x[0]) == COLS+1 || (biker1 -> x[0]) == LINES+1){
			biker1 -> flag_of_death = 1;
			mvaddstr(0,50,"biker1 border");
		}
		if((biker4 -> x[0]) == COLS+1 || (biker4 -> x[0]) == LINES+1){
			biker4 -> flag_of_death = 1;
			mvaddstr(0,50,"biker4 border");
		}
		if((biker3 -> x[0]) == COLS+1 || (biker3 -> x[0]) == LINES+1){
			biker3 -> flag_of_death = 1;
			mvaddstr(0,50,"biker3 border");
		}
		if((biker2 -> x[0]) == COLS+1 || (biker2 -> x[0]) == LINES+1){
			biker2 -> flag_of_death = 1;
			mvaddstr(0,50,"biker2 border");
		}*/	
}

int check_alive(struct bike *biker){
	
	if(biker -> flag_of_death){
		mvwprintw(stdscr,2,COLS/2, "flag_of_death = %d",biker -> flag_of_death); 
		return false;
	}
	else{
		return true;
	}  

}
//______________________________________

//___BESPOLEZNYA________________________

//_______________________________________
void set(struct bike *biker,int y,int x){
    for(int i=0; i<6750; i++){
        biker->x[i]=COLS/2 + x;
        biker->y[i]=LINES/2 + y;        
    }
}

int main(){
	int ch = 0;
	int u,d,l,r = 0;
	int curr_size = 1;
	initscr();
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);

    struct bike biker_u;
    struct bike biker_d;
    struct bike biker_r;
    struct bike biker_l;


    set(&biker_u,-5,0);
    set(&biker_d,5,0);
    set(&biker_r,0,5);
    set(&biker_l,0,-5);

    while(ch != 'q'){
    	u = check_alive(&biker_u);
    	d = check_alive(&biker_d);
    	l = check_alive(&biker_l);
    	r = check_alive(&biker_r); 

        for(int i = curr_size; i>=0; i--){
        	if(u){
            mvaddch(biker_u.y[i], biker_u.x[i], '1');
        	}
        	if(d){
            mvaddch(biker_d.y[i], biker_d.x[i], '2');
        	}
         	if(l){
            mvaddch(biker_l.y[i], biker_l.x[i], '3');
        	}
        	if(r){
            mvaddch(biker_r.y[i], biker_r.x[i], '4');
        	}
            refresh();
        }
        
        ch=getch();
     
        switch(ch) {
        case KEY_UP:
            if(u){
            up(&biker_u);
        }
        	if(l){
            left(&biker_l);
        }
        	if(r){
            right(&biker_r);
        }
        	if(d){
            down(&biker_d);
        }
            break;
        case KEY_DOWN:
            if(d){
            up(&biker_d);
        }
            if(r){
            left(&biker_r);
        }
            if(l){
            right(&biker_l);
        }
            if(u){
            down(&biker_u);
        }
            break;
        case KEY_LEFT:
           	if(r){
            up(&biker_r);
        }
            if(u){
            left(&biker_u);
        }
            if(d){
            right(&biker_d);
        }
            if(l){
            down(&biker_l);
        }
            break;
        case KEY_RIGHT:
          	if(l){
            up(&biker_l);
        }
            if(d){
            left(&biker_d);
        }
            if(u){
            right(&biker_u);
        }
            if(r){
            down(&biker_r);
        }
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
