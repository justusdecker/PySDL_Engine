#include <stdlib.h>
#include <stdio.h>
void LOG_WRITE_C(char* msg,char* value, char color, char* logtype) {
    printf("[\033[%d;1m%s%s]%s %s\n",color,logtype,"\033[0;1m",msg, value);
}

void LOG_WRITE(char* msg, char color, char* logtype) {
    printf("[\033[%d;1m%s%s]%s\n",color,logtype,"\033[0;1m",msg);

}