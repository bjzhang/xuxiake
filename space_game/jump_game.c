#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <unistd.h>

static void finish(int sig);

static void draw_window_border(WINDOW *win)
{
	wattron(win, COLOR_PAIR(4));
	box(win, ACS_VLINE, ACS_HLINE);
	wrefresh(win);
}

/**
 *  jump from (start_x, start_y) with F jump and G.
 *  a_jump = F_jump * mass;	//a = accelerated velocity
 *  v_jump = A_jump * jump_interval;
 *  G      = g * mass;
 *  v_landing = G * t
 *  y = (v_landing - v_jump) * t;
 *
 *  stop when y <= start_y
 */
static int jump_step(void)
{
	int mass = 1000;
	int g = 10;
	int F_jump = 100;
	int a_jump = F_jump * mass;	//10 0000
	int jump_interval = 10;
	int v_jump = a_jump * jump_interval;	//100 0000
	int G = g * mass;
	int v_landing = 0;
	static int time = 1;

	v_landing = G * time; //100000
	y = (v_landing - v_jump) * time;
	time++;

	return y;
}

static void jumper(int scr_max_y, int scr_max_x)
{
	WINDOW *main_win;
	int y, x;
	int ch;

	y = scr_max_y - 1;
	x = 0;
	main_win= newwin(scr_max_y, scr_max_x, 0, 0);
	//error handling.
	draw_window_border(main_win);
	wattron(main_win, COLOR_PAIR(2));
	wmove(main_win, y, x);
	wrefresh(main_win);
	curs_set(0);	//hide the curser
	for (;;) {
		draw_window_border(main_win);
		wattron(main_win, COLOR_PAIR(2));
		if ((ch = getch()) != ERR) {
			/* delete the previous char */
			wmove(main_win, y, x);
			waddch(main_win, ' ' | A_INVIS);
			wrefresh(main_win);
			switch(ch) {
				case KEY_UP:
					y--;
					if (y <= 0)
						y = 0;
					break;
				case KEY_DOWN:
					y++;
					if (y >= scr_max_y - 1)
						y = scr_max_y -1;
					break;
				case KEY_LEFT:
					x--;
					if (x <= 0)
						x = 0;
					break;
				case KEY_RIGHT:
					x++;
					if (x >= scr_max_x - 1)
						x = scr_max_x - 1;
					break;
				case ' ':
					int y = jump_step();
					if (y < 
					break;
			}
			wmove(main_win, y, x);
			waddch(main_win, '#');
			wrefresh(main_win);
		}
	}
}

int main(int argc, char *argv[])
{
	int stdscr_h, stdscr_w;

	/* initialize your non-curses data structures here */

	(void) signal(SIGINT, finish);      /* arrange interrupts to terminate */

	(void) initscr();      /* initialize the curses library */
	keypad(stdscr, TRUE);  /* enable keyboard mapping */
	(void) nonl();         /* tell curses not to do NL->CR/NL on output */
	(void) cbreak();       /* take input chars one at a time, no wait for \n */
	(void) noecho();       /* no echo input */
	nodelay(stdscr, TRUE);

	if (has_colors())
	{
		printf("has color\n");
		start_color();

		/*
		 * Simple color assignment, often all we need.  Color pair 0 cannot
		 * be redefined.  This example uses the same value for the color
		 * pair as for the foreground color, though of course that is not
		 * necessary:
		 */
		init_pair(1, COLOR_RED,     COLOR_BLACK);
		init_pair(2, COLOR_GREEN,   COLOR_BLACK);
		init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
		init_pair(4, COLOR_BLUE,    COLOR_BLACK);
		init_pair(5, COLOR_CYAN,    COLOR_BLACK);
		init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(7, COLOR_WHITE,   COLOR_BLACK);
	}

	getmaxyx(stdscr, stdscr_h, stdscr_w);
	if (stdscr_h < 24 || stdscr_w < 80)
		goto err;

	jumper(24, 80);
err:
	finish(0);               /* we are done */
}

static void finish(int sig)
{
	endwin();

	/* do your non-curses wrapup here */
	printf("exit\n");

	exit(0);
}
