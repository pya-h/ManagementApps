#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#ifndef CONSOLE_H
  #define CONSOLE_H
#endif


int strlen(char x[])
{
  int i = 0;
  for(i = 0; x[i]; i++);
  return i;
}
/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

/* reads from keypress, echoes */
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

char *strlwr(char str[], const int MAX)
{
  char *s = new char[MAX] {0};
  for(int i = 0; str[i]; s[i] = str[i], i++);
  return s;
}

void __pause__() 
{
  printf("\nPress Enter to continue...\n");
  getch();
}

#ifdef _WIN32
  #define CLEAR_SCREEN "cls"
  #define pause system("pause")
#elif defined __unix__
  #define CLEAR_SCREEN "clear"
  #define pause __pause__()
#elif defined __APPLE__
  #define CLEAR_SCREEN "clear"
  #define pause __pause__()
#endif