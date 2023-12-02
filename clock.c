#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1

char *zero[5][3] = {
    {"█", "█", "█"},
    {"█", " ", "█"},
    {"█", " ", "█"},
    {"█", " ", "█"},
    {"█", "█", "█"}};

char *one[5][3] = {
    {" ", " ", "█"},
    {" ", " ", "█"},
    {" ", " ", "█"},
    {" ", " ", "█"},
    {" ", " ", "█"}};

char *two[5][3] = {
    {"█", "█", "█"},
    {" ", " ", "█"},
    {"█", "█", "█"},
    {"█", " ", " "},
    {"█", "█", "█"}};

char *three[5][3] = {
    {"█", "█", "█"},
    {" ", " ", "█"},
    {"█", "█", "█"},
    {" ", " ", "█"},
    {"█", "█", "█"}};

char *four[5][3] = {
    {"█", " ", "█"},
    {"█", " ", "█"},
    {"█", "█", "█"},
    {" ", " ", "█"},
    {" ", " ", "█"}};

char *five[5][3] = {
    {"█", "█", "█"},
    {"█", " ", " "},
    {"█", "█", "█"},
    {" ", " ", "█"},
    {"█", "█", "█"}};

char *six[5][3] = {
    {"█", "█", "█"},
    {"█", " ", " "},
    {"█", "█", "█"},
    {"█", " ", "█"},
    {"█", "█", "█"}};

char *seven[5][3] = {
    {"█", "█", "█"},
    {" ", " ", "█"},
    {" ", " ", "█"},
    {" ", " ", "█"},
    {" ", " ", "█"}};

char *eight[5][3] = {
    {"█", "█", "█"},
    {"█", " ", "█"},
    {"█", "█", "█"},
    {"█", " ", "█"},
    {"█", "█", "█"}};

char *nine[5][3] = {
    {"█", "█", "█"},
    {"█", " ", "█"},
    {"█", "█", "█"},
    {" ", " ", "█"},
    {"█", "█", "█"}};

char *colon[5][3] = {
    {" ", " ", " "},
    {" ", "█", " "},
    {" ", " ", " "},
    {" ", "█", " "},
    {" ", " ", " "}};

//create an array of pointers to the arrays of pointers to the digits
char *(*digits[10])[5][3] = {&zero, &one, &two, &three, &four, &five, &six, &seven, &eight, &nine};

int flags[2] = {FALSE,FALSE};

    // create a fonction to print a digit
    void printDigit(int digit, int x, int y)
{
    // get the array of pointers to the arrays of pointers to the digits
    char *(*digitArray)[5][3] = digits[digit];
    // print the digit
    for (int i = 0; i < 5; i++)
    {
        printf("\033[%d;%dH", y + i, x);
        for (int j = 0; j < 3; j++)
        {
            printf("%s", (*digitArray)[i][j]);
        }
    }
}

    void printColon(int x, int y){
        //print the colon
        for (int i = 0; i < 5; i++)
        {
            printf("\033[%d;%dH", y+i, x);
            for (int j = 0; j < 3; j++)
            {
                printf("%s", colon[i][j]);
            }
        }
    }


     int getTermLength(){struct winsize w;
ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
return w.ws_row;
}



int getTermWidth()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void signalhandler(int signum)
{
    printf("Caught signal %d, coming out...\n", signum);
    //clear screen
    system("clear");
    //make cursot white
    printf("\033[37m");
    //move cursor to the top left corner
    printf("\033[1;1H");
    //make cursor visible
    printf("\033[?25h");
    exit(1);
}

void printClock(int hour, int minute, int second, int width, int height, int secondFlag){
    //print the hour
    int digit = hour / 10;
    printDigit(digit, width / 2 - 8, height / 2 - 2);
    digit = hour % 10;
    printDigit(digit, width / 2 - 3, height / 2 - 2);
    //print the colon
    printColon(width / 2 + 2, height / 2 - 2);
    //print the minute
    digit = minute / 10;
    printDigit(digit, width / 2 + 5, height / 2 - 2);
    digit = minute % 10;
    printDigit(digit, width / 2 + 10, height / 2 - 2);
    if (secondFlag == TRUE)
    {
        printColon(width / 2 + 15, height / 2 - 2);
        digit = second / 10;
        printDigit(digit, width / 2 + 18, height / 2 - 2);
        digit = second % 10;
        printDigit(digit, width / 2 + 23, height / 2 - 2);
    }
}


enum colors{
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white
};
char *colorspe;

int main(int argc, char *argv[])
{
    printf("\033[?25l");
    signal(SIGINT, signalhandler);
    system("clear");
    for(int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-s") == 0)
        {
            flags[0] = TRUE;
        }else if (strcmp(argv[i], "-c") == 0)
        {
            flags[1] = TRUE;
            //get the color
            colorspe = argv[i+1];
            //if null, print error message
            if (colorspe == NULL)
            {
                printf("Error: no color specified\n");
                exit(1);
            }
        }
    }

   while(1){
       int width = getTermWidth() - 2;
       int height = getTermLength() - 2;
       //get time hour and minute
       time_t rawtime;
       struct tm * timeinfo;
       time(&rawtime);
       timeinfo = localtime(&rawtime);
       int hour = timeinfo->tm_hour;
       int minute = timeinfo->tm_min;
       int second = timeinfo->tm_sec;
       system("clear");
       if (flags[1] == TRUE)
       {
            //get the color with the enum 
            if (strcmp(colorspe, "red") == 0)
            {
                printf("\033[31m");
            }else if (strcmp(colorspe, "green") == 0)
            {
                printf("\033[32m");
            }else if (strcmp(colorspe, "yellow") == 0)
            {
                printf("\033[33m");
            }else if (strcmp(colorspe, "blue") == 0)
            {
                printf("\033[34m");
            }else if (strcmp(colorspe, "magenta") == 0)
            {
                printf("\033[35m");
            }else if (strcmp(colorspe, "cyan") == 0)
            {
                printf("\033[36m");
            }else if (strcmp(colorspe, "white") == 0)
            {
                printf("\033[37m");
            }else{
                printf("Error: invalid color\n");
                exit(1);
            }

       }
       
       if (flags[0] == TRUE)
       {
           width = width - 15;
       }
        printClock(hour, minute, second, width, height, flags[0]);
       
      



    fflush(stdout);
    usleep(50000);
}
 
    return 0;
}
