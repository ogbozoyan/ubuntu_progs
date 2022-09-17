#include <stdio.h>
#include <ncurses.h>

int main(int argc,char** argv){
	int ch = 0;
	int x = 77, y = 21, x1,x2,x3,x4 = x ,y1,y2,y3,y4 = y; //for @
	int z = 81, w = 23, z1,z2,z3,z4 = z ,w1,w2,w3,w4 = w; //for #
	int l = 77, k = 25, l1,l2,l3,l4 = l ,k1,k2,k3,k4 = k; //for ^
	int p = 73, o = 23, p1,p2,p3,p4 = p ,o1,o2,o3,o4 = o; //for *
	int count = 1;
	initscr(); /*initialization lib*/
	noecho();/*makes not to print pressed key*/
	curs_set(0);/*delete coursor*/
	keypad(stdscr,TRUE);
	while(ch != 'q'){ 
		//if even 1
		if (count == 1){
		mvaddch(y,x,'@'); //1
		mvaddch(w,z,'#'); //2
		mvaddch(k,l,'^'); //3
		mvaddch(o,p,'*'); //4
		mvaddstr(23,75,"START");
		refresh();
		ch = getch();
		mvaddch(y,x,' ');
		mvaddch(w,z,' ');
		mvaddch(k,l,' ');
		mvaddch(o,p,' ');
		switch(ch){
			case KEY_LEFT:
				x = (x + COLS -1)%COLS;
				w = (w+LINES-1)%LINES;
				l = (l+1)%COLS;
				o = (o+1)%LINES;
				count++;
				break;
			case KEY_RIGHT:
				x = (x+1)%COLS;
				w = (w+1)%LINES;
				l = (l + COLS -1)%COLS;
				o = (o+LINES-1)%LINES;
				count++;
				break;
			case KEY_DOWN:
				y = (y+1)%LINES;
				z = (z + COLS -1)%COLS;
				k = (k+LINES-1)%LINES;
				p = (p+1)%COLS;
				count++;
				break;
			case KEY_UP:
				y = (y+LINES-1)%LINES;
				z = (z+1)%COLS;
				k = (k+1)%LINES;
				p = (p + COLS -1)%COLS;
				count++;
			default:
			break;
		}
		//end if even 1
	} //size snake 2
		if (count == 2 ){
		mvaddch(y,x,'@'); //1
		mvaddch(y1,x1,'~');
		mvaddch(w,z,'#'); //2
		mvaddch(w1,z1,'~');
		mvaddch(k,l,'^'); //3
		mvaddch(k1,l1,'~');
		mvaddch(o,p,'*'); //4
		mvaddch(o1,p1,'~');
		refresh();
		ch = getch();
		mvaddch(y,x,' ');
		mvaddch(y1,x1,' ');
		mvaddch(w,z,' ');
		mvaddch(w1,z1,' ');
		mvaddch(k,l,' ');
		mvaddch(k1,l1,' ');
		mvaddch(o,p,' ');
		mvaddch(o1,p1,' ');
		switch(ch){
			case KEY_LEFT:
				z1 = z;
				w1 = w;
				x1 = x;
				y1 = y;
				k1 = k;
				l1 = l;
				o1 = o;
				p1 = p;
				x = (x + COLS -1)%COLS;
				w = (w+LINES-1)%LINES;
				l = (l+1)%COLS;
				o = (o+1)%LINES;
				count++;
				break;
			case KEY_RIGHT:
				w1 = w;
				z1 = z;
				x1 = x;
				y1 = y;
				k1 = k;
				l1 = l;
				o1 = o;
				p1 = p;
				x = (x+1)%COLS;
				w = (w+1)%LINES;
				l = (l + COLS -1)%COLS;
				o = (o+LINES-1)%LINES;
				count++;
				break;
			case KEY_DOWN:
				w1 = w;
				z1 = z;
				x1 = x;
				y1 = y;
				k1 = k;
				l1 = l;
				o1 = o;
				p1 = p;
				y = (y+1)%LINES;
				z = (z + COLS -1)%COLS;
				k = (k+LINES-1)%LINES;
				p = (p+1)%COLS;
				count++;
				break;
			case KEY_UP:
				z1 = z;
				w1 = w;
				x1 = x;
				y1 = y;
				k1 = k;
				l1 = l;
				o1 = o;
				p1 = p;
				y = (y+LINES-1)%LINES;
				z = (z+1)%COLS;
				k = (k+1)%LINES;
				p = (p + COLS -1)%COLS;
				count++;
			default:
			break;
			}
		}
		//size 3
		if(count == 3){

		mvaddch(y,x,'@'); //1
		mvaddch(y1,x1,'~');
		mvaddch(y2,x2,'~');
		mvaddch(w,z,'#'); //2
		mvaddch(w1,z1,'~');
		mvaddch(w2,z2,'~');
		mvaddch(k,l,'^'); //3
		mvaddch(k1,l1,'~');
		mvaddch(k2,l2,'~');
		mvaddch(o,p,'*'); //4
		mvaddch(o1,p1,'~');
		mvaddch(o2,p2,'~');

		refresh();
		ch = getch();

		mvaddch(y,x,' ');
		mvaddch(y1,x1,' ');
		mvaddch(y2,x2,' ');
		mvaddch(w,z,' ');
		mvaddch(w1,z1,' ');
		mvaddch(w2,z2,' ');
		mvaddch(k,l,' ');
		mvaddch(k1,l1,' ');
		mvaddch(k2,l2,' ');
		mvaddch(o,p,' ');
		mvaddch(o1,p1,' ');
		mvaddch(o2,p2,' ');
		switch(ch){
			case KEY_LEFT:
				z2 = z1;
				w2 = w1;
				x2 = x1;
				y2 = y1;
				k2 = k1;
				l2 = l1;
				o2 = o1;
				p2 = p1;
				z1 = z;
				w1 = w;
				x1 = x;
				y1 = y;
				k1 = k;
				l1 = l;
				o1 = o;
				p1 = p;
				x = (x + COLS -1)%COLS;
				w = (w+LINES-1)%LINES;
				l = (l+1)%COLS;
				o = (o+1)%LINES;
				count++;
				break;
			case KEY_RIGHT:
				z2 = z1;
				w2 = w1;
				x2 = x1;
				y2 = y1;
				k2 = k1;
				l2 = l1;
				o2 = o1;
				p2 = p1;
				z1 = z;
				w1 = w;
				x1 = x;
				y1 = y;
				k1 = k;
				l1 = l;
				o1 = o;
				p1 = p;
				x = (x+1)%COLS;
				w = (w+1)%LINES;
				l = (l + COLS -1)%COLS;
				o = (o+LINES-1)%LINES;
				count++;
				break;
			case KEY_DOWN:
				z2 = z1;
				w2 = w1;
				x2 = x1;
				y2 = y1;
				k2 = k1;
				l2 = l1;
				o2 = o1;
				p2 = p1;
				z1 = z;
				w1 = w;
				x1 = x;
				y1 = y;
				k1 = k;
				l1 = l;
				o1 = o;
				p1 = p;
				y = (y+1)%LINES;
				z = (z + COLS -1)%COLS;
				k = (k+LINES-1)%LINES;
				p = (p+1)%COLS;
				count++;
				break;
			case KEY_UP:
				z2 = z1;
				w2 = w1;
				x2 = x1;
				y2 = y1;
				k2 = k1;
				l2 = l1;
				o2 = o1;
				p2 = p1;
				z1 = z;
				w1 = w;
				x1 = x;
				y1 = y;
				k1 = k;
				l1 = l;
				o1 = o;
				p1 = p;
				y = (y+LINES-1)%LINES;
				z = (z+1)%COLS;
				k = (k+1)%LINES;
				p = (p + COLS -1)%COLS;
				count++;
				break;
			default:
			break;
			}
		}
		//size 4
		if(count == 4){
		
		mvaddch(y,x,'@'); //1
		mvaddch(y1,x1,'~');
		mvaddch(y2,x2,'~');
		mvaddch(y3,x3,'~');
		mvaddch(w,z,'#'); //2
		mvaddch(w1,z1,'~');
		mvaddch(w2,z2,'~');
		mvaddch(w3,z3,'~');
		mvaddch(k,l,'^'); //3
		mvaddch(k1,l1,'~');
		mvaddch(k2,l2,'~');
		mvaddch(k3,l3,'~');
		mvaddch(o,p,'*'); //4
		mvaddch(o1,p1,'~');
		mvaddch(o2,p2,'~');
		mvaddch(o3,p3,'~');

		refresh();
		ch = getch();

		mvaddch(y,x,' ');
		mvaddch(y1,x1,' ');
		mvaddch(y2,x2,' ');
		mvaddch(y3,x3,' ');
		mvaddch(w,z,' ');
		mvaddch(w1,z1,' ');
		mvaddch(w2,z2,' ');
		mvaddch(w3,z3,' ');
		mvaddch(k,l,' ');
		mvaddch(k1,l1,' ');
		mvaddch(k2,l2,' ');
		mvaddch(k3,l3,' ');
		mvaddch(o,p,' ');
		mvaddch(o1,p1,' ');
		mvaddch(o2,p2,' ');
		mvaddch(o3,p3,' ');

		switch(ch){
			case KEY_LEFT:
				z3 = z2;
				w3 = w2;
				x3 = x2;
				y3 = y2;
				k3 = k2;
				l3 = l2;
				o3 = o2;
				p3 = p2;
				z2 = z1;
				w2 = w1;
				x2 = x1;
				y2 = y1;
				k2 = k1;
				l2 = l1;
				o2 = o1;
				p2 = p1;
				z1 = z;
				w1 = w;
				x1 = x;
				y1 = y;
				k1 = k;
				l1 = l;
				o1 = o;
				p1 = p;
				x = (x + COLS -1)%COLS;
				w = (w+LINES-1)%LINES;
				l = (l+1)%COLS;
				o = (o+1)%LINES;
				count++;
				break;
			case KEY_RIGHT:
				z3 = z2;
				w3 = w2;
				x3 = x2;
				y3 = y2;
				k3 = k2;
				l3 = l2;
				o3 = o2;
				p3 = p2;
				z2 = z1;
				w2 = w1;
				x2 = x1;
				y2 = y1;
				k2 = k1;
				l2 = l1;
				o2 = o1;
				p2 = p1;
				z1 = z;
				w1 = w;
				x1 = x;
				y1 = y;
				k1 = k;
				l1 = l;
				o1 = o;
				p1 = p;
				x = (x+1)%COLS;
				w = (w+1)%LINES;
				l = (l + COLS -1)%COLS;
				o = (o+LINES-1)%LINES;
				count++;
				break;
			case KEY_DOWN:
				z3 = z2;
				w3 = w2;
				x3 = x2;
				y3 = y2;
				k3 = k2;
				l3 = l2;
				o3 = o2;
				p3 = p2;
				z2 = z1;
				w2 = w1;
				x2 = x1;
				y2 = y1;
				k2 = k1;
				l2 = l1;
				o2 = o1;
				p2 = p1;
				z1 = z;
				w1 = w;
				x1 = x;
				y1 = y;
				k1 = k;
				l1 = l;
				o1 = o;
				p1 = p;
				y = (y+1)%LINES;
				z = (z + COLS -1)%COLS;
				k = (k+LINES-1)%LINES;
				p = (p+1)%COLS;
				count++;
				break;
			case KEY_UP:
				z3 = z2;
				w3 = w2;
				x3 = x2;
				y3 = y2;
				k3 = k2;
				l3 = l2;
				o3 = o2;
				p3 = p2;
				z2 = z1;
				w2 = w1;
				x2 = x1;
				y2 = y1;
				k2 = k1;
				l2 = l1;
				o2 = o1;
				p2 = p1;
				z1 = z;
				w1 = w;
				x1 = x;
				y1 = y;
				k1 = k;
				l1 = l;
				o1 = o;
				p1 = p;
				y = (y+LINES-1)%LINES;
				z = (z+1)%COLS;
				k = (k+1)%LINES;
				p = (p + COLS -1)%COLS;
				count++;
			default:
			break;
			}
		}
		//size 5
		if (count == 5){

		mvaddch(y,x,'@'); //1
		mvaddch(y1,x1,'~');
		mvaddch(y2,x2,'~');
		mvaddch(y3,x3,'~');
		mvaddch(y4,x4,'~');
		mvaddch(w,z,'#'); //2
		mvaddch(w1,z1,'~');
		mvaddch(w2,z2,'~');
		mvaddch(w3,z3,'~');
		mvaddch(w4,z4,'~');
		mvaddch(k,l,'^'); //3
		mvaddch(k1,l1,'~');
		mvaddch(k2,l2,'~');
		mvaddch(k3,l3,'~');
		mvaddch(k4,l4,'~');
		mvaddch(o,p,'*'); //4
		mvaddch(o1,p1,'~');
		mvaddch(o2,p2,'~');
		mvaddch(o3,p3,'~');
		mvaddch(o4,p4,'~');
		refresh();
		ch = getch();

		mvaddch(y,x,' ');
		mvaddch(y1,x1,' ');
		mvaddch(y2,x2,' ');
		mvaddch(y3,x3,' ');
		mvaddch(y4,x4,' ');
		mvaddch(w,z,' ');
		mvaddch(w1,z1,' ');
		mvaddch(w2,z2,' ');
		mvaddch(w3,z3,' ');
		mvaddch(w4,z4,' ');
		mvaddch(k,l,' ');
		mvaddch(k1,l1,' ');
		mvaddch(k2,l2,' ');
		mvaddch(k3,l3,' ');
		mvaddch(k4,l4,' ');
		mvaddch(o,p,' ');
		mvaddch(o1,p1,' ');
		mvaddch(o2,p2,' ');
		mvaddch(o3,p3,' ');
		mvaddch(o4,p4,' ');

		switch(ch){
			case KEY_LEFT:
				z4 = z3;
				w4 = w3;
				x4 = x3;
				y4 = y3;
				k4 = k3;
				l4 = l3;
				o4 = o3;
				p4 = p3;
				z3 = z2;
				w3 = w2;
				x3 = x2;
				y3 = y2;
				k3 = k2;
				l3 = l2;
				o3 = o2;
				p3 = p2;
				z2 = z1;
				w2 = w1;
				x2 = x1;
				y2 = y1;
				k2 = k1;
				l2 = l1;
				o2 = o1;
				p2 = p1;
				z1 = z;
				w1 = w;
				x1 = x;
				y1 = y;
				k1 = k;
				l1 = l;
				o1 = o;
				p1 = p;
				x = (x + COLS -1)%COLS;
				w = (w+LINES-1)%LINES;
				l = (l+1)%COLS;
				o = (o+1)%LINES;
				break;
			case KEY_RIGHT:
				z4 = z3;
				w4 = w3;
				x4 = x3;
				y4 = y3;
				k4 = k3;
				l4 = l3;
				o4 = o3;
				p4 = p3;
				z3 = z2;
				w3 = w2;
				x3 = x2;
				y3 = y2;
				k3 = k2;
				l3 = l2;
				o3 = o2;
				p3 = p2;
				z2 = z1;
				w2 = w1;
				x2 = x1;
				y2 = y1;
				k2 = k1;
				l2 = l1;
				o2 = o1;
				p2 = p1;
				z1 = z;
				w1 = w;
				x1 = x;
				y1 = y;
				k1 = k;
				l1 = l;
				o1 = o;
				p1 = p;
				x = (x+1)%COLS;
				w = (w+1)%LINES;
				l = (l + COLS -1)%COLS;
				o = (o+LINES-1)%LINES;
				break;
			case KEY_DOWN:
				z4 = z3;
				w4 = w3;
				x4 = x3;
				y4 = y3;
				k4 = k3;
				l4 = l3;
				o4 = o3;
				p4 = p3;
				z3 = z2;
				w3 = w2;
				x3 = x2;
				y3 = y2;
				k3 = k2;
				l3 = l2;
				o3 = o2;
				p3 = p2;
				z2 = z1;
				w2 = w1;
				x2 = x1;
				y2 = y1;
				k2 = k1;
				l2 = l1;
				o2 = o1;
				p2 = p1;
				z1 = z;
				w1 = w;
				x1 = x;
				y1 = y;
				k1 = k;
				l1 = l;
				o1 = o;
				p1 = p;
				y = (y+1)%LINES;
				z = (z + COLS -1)%COLS;
				k = (k+LINES-1)%LINES;
				p = (p+1)%COLS;
				break;
			case KEY_UP:/*trash dude*?*/
				z4 = z3;
				w4 = w3;
				x4 = x3;
				y4 = y3;
				k4 = k3;
				l4 = l3;
				o4 = o3;
				p4 = p3;
				z3 = z2;
				w3 = w2;
				x3 = x2;
				y3 = y2;
				k3 = k2;
				l3 = l2;
				o3 = o2;
				p3 = p2;
				z2 = z1;
				w2 = w1;
				x2 = x1;
				y2 = y1;
				k2 = k1;
				l2 = l1;
				o2 = o1;
				p2 = p1;
				z1 = z;
				w1 = w;
				x1 = x;
				y1 = y;
				k1 = k;
				l1 = l;
				o1 = o;
				p1 = p;
				y = (y+LINES-1)%LINES;
				z = (z+1)%COLS;
				k = (k+1)%LINES;
				p = (p + COLS -1)%COLS;
			break;
			default:
			break;
			}
		}
}
endwin();
	return 0;
}