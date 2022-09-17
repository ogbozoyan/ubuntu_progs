void game(){
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
        check_touch(&biker_u,&biker_d,&biker_r,&biker_l);
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
    }
}