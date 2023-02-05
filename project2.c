#include <ncurses.h>
struct where
{
    int l ;
    int c ;
    int y ;
    int x ;

};

int line[10] = {0,6,3,11,11,11,11,11,12,10};

void go_up(struct where windows){
    int x, y;
    getyx(stdscr, y, x);
    if (y == windows.y){
        move(y, x);
    }
    else{
        move(y-1, x);
    }
}

void go_down(struct where windows){
    int x, y;
    getyx(stdscr, y, x);
    if (y ==  (windows.y + windows.l - 1)){
        move(y, x);
    }
    else{
        move(y+1, x);
    }
}

void go_left(struct where windows){
    int x, y;
    getyx(stdscr, y, x);
    if (x == windows.x){
        move(y, x);
    }
    else{
        move(y, x-1);
    }
}    

void go_right(struct where windows){
    int x, y;
    getyx(stdscr, y, x);
    if (x ==  (windows.x + windows.c - 1)){
        move(y, x);
    }
    else{
        move(y, x+1);
    }
}

int main()
{	
	initscr();	
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);	
    init_pair(2, COLOR_RED, COLOR_YELLOW);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLUE);
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
	// printw("Hello World !!!");	/* Print Hello World		  */
	refresh();

    char mode = 'n';
    struct where main = {LINES - 3, COLS-4, 1, 4};
    struct where line_number = {LINES - 3, 4, 1, 0};
    struct where header = {1, COLS  , 0, 0};
    struct where command = {1, COLS , LINES - 1, 0};
    struct where info = {1,  COLS - 7, LINES - 2, 7};
    struct where situation = {1, 7 , LINES - 2, 0};


    WINDOW *mains= newwin(main.l, main.c, main.y, main.x);
    WINDOW *line_numbers = newwin(line_number.l, line_number.c, line_number.y, line_number.x);
    WINDOW *headers = newwin( header.l, header.c, header.y, header.x);
    WINDOW *commands = newwin( command.l, command.c, command.y, command.x);
    WINDOW *infos = newwin( info.l, info.c, info.y, info.x);
    WINDOW *situations = newwin( situation.l, situation.c, situation.y, situation.x);

    wrefresh(mains);wrefresh(line_numbers);wrefresh(infos);wrefresh(commands);wrefresh(headers);wrefresh(situations);
    wbkgd(mains, COLOR_PAIR(1));
    wbkgd(line_numbers, COLOR_PAIR(2));
    wbkgd(headers, COLOR_PAIR(3));
    wbkgd(commands, COLOR_PAIR(4));
    wbkgd(infos, COLOR_PAIR(5));
    wbkgd(situations, COLOR_PAIR(6));
    noecho();
    wprintw(mains, "salam");
    wprintw(commands, "command : ");


    for(int i = 0; i < 10; i++){
        mvwprintw( line_numbers, i, 1, "~0%d", i);
    }
    for(int i = 10; i < LINES-1; i++){
        mvwprintw( line_numbers, i, 1, "~%d", i);
    }
    
    wrefresh(mains);wrefresh(line_numbers);wrefresh(infos);wrefresh(commands);wrefresh(headers);wrefresh(situations);

    wmove(mains, 0, 0);wrefresh(mains);

    while(1){
        if(mode == 'n'){
            wclear(situations);
            wprintw(situations, "NORMAL");wrefresh(situations);
        }
        else if(mode == 'v'){
            wclear(situations);
            wprintw(situations,"VISUAL");wrefresh(situations);
        }
        else if(mode == 'i'){
            wclear(situations);
            wprintw(situations, "INSERT");wrefresh(situations);
        }
        char c = getch();
        if (c == 'k'){
            go_up(main);
        }
        else if(c == 'j') {
            go_down(main);
        }
        else if(c == 'h') {
            go_left(main);
        }
        else if(c == 'l') {
            go_right(main);
        }
        else if((int)c == 27){
            wmove(mains, 0, 0);wrefresh(mains);

        }
        else if((c == '\\')||(c == ':')){
            echo();
            wmove(commands, command.y, command.x + 7);wrefresh(commands);
            while((c = wgetch(commands)) != '\n'){}   
            noecho();    
        }
        else if(c == 'v'){
            mode = 'v';
        } 
        else if(c == 'i'){
            mode = 'i';
        } 
        else if(c == 'n'){
            mode = 'n';
        }
        else if( c == 'x'){
            endwin();
            break;
        }
    }
    int x,y;
    // getyx(stdscr, y, x);
    // printf("%d %d", x, y);
    refresh();
	getch();			
	endwin();			

	return 0;
}