#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <unistd.h>

static void finish(int sig);

int
main(int argc, char *argv[])
{
	int stdscr_h, stdscr_w;
	WINDOW *main_win;
	int ch;
	int i;

	/* initialize your non-curses data structures here */

	(void) signal(SIGINT, finish);      /* arrange interrupts to terminate */

	(void) initscr();      /* initialize the curses library */
	keypad(stdscr, TRUE);  /* enable keyboard mapping */
	(void) nonl();         /* tell curses not to do NL->CR/NL on output */
	(void) cbreak();       /* take input chars one at a time, no wait for \n */
	(void) noecho();       /* no echo input */

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

	main_win= newwin(24, 80, 0, 0);
	i = 0;
	wattron(main_win, COLOR_PAIR(2));
	nodelay(stdscr, TRUE);
	for (;;) {
		if ((ch = getch()) != ERR) {
			wmove(main_win, 24, i);
			waddch(main_win, ch);
			wrefresh(main_win);
			i++;
		}
	}

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
