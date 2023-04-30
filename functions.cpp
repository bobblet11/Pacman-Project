#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "functions.h"

//Move the cursor to a specific position on the console or terminal screen.
void gotoxy(int x, int y)
{
    printf("\033[%d;%dH", x, y);
}

//Initialize the terminal input and output settings.
void initializeTermios(int echo)
{
    tcgetattr(0, &old);
    newer = old;
    newer.c_lflag &= ~ICANON;
    newer.c_lflag &= echo ? ECHO : ~ECHO;
    tcsetattr(0, TCSANOW, &newer);
}

//Reset the terminal settings to their original values, which were saved by the initializeTermios() function.
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

//Detect if a key has been pressed on the keyboard without blocking the program's execution.
bool keyboardhit()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}

//Read a single character of input from the keyboard.
char getch_(int echo)
{
    char ch;
    initializeTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

//Wrapper function for getch_()
char GETCH(void)
{
    return getch_(0);
}

//Wrapper function for getch_()
char getche(void)
{
    return getch_(1);
}

//Get the maximum number of columns that can be displayed on the terminal
int getmax_x()
{
    int lines = 24;
#ifdef TIOCGSIZE
    struct ttysize ts;
        ioctl(STDIN_FILENO, TIOCGSIZE, &ts);

        lines = ts.ts_lines;
#elif defined(TIOCGWINSZ)
    struct winsize ts;
        ioctl ( STDIN_FILENO, TIOCGWINSZ, &ts);

        lines = ts.ws_row;
#endif /* TIOCGSIZE */
    return lines;
}

//Get the maximum number of rows that can be displayed on the terminal
int getmax_y()
{
    int cols = 80;

#ifdef TIOCGSIZE
    struct ttysize ts;
        ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
        cols = ts.ts_cols;

#elif defined(TIOCGWINSZ)
    struct winsize ts;
        ioctl ( STDIN_FILENO, TIOCGWINSZ, &ts);
        cols = ts.ws_col;

#endif /* TIOCGSIZE */
    return cols;
}