#include <stdio.h>

void LOG_WRITE(char* msg, int color, char* logtype) {
    printf("[\033[%d;1m%s%s]%s\n",color,logtype,"\033[0;1m",msg);
}