#ifndef LOG_H
#define LOG_H
/*
Pretty logs:
    - Places automatically an \n at the end
    - colorize the terminal a bit
*/
void LOG_WRITE(char* msg, char color, char* logtype);
void LOG_WRITE_C(char* msg,char* value, char color, char* logtype);
struct LTYPES{
    char* DEBUG;
    char* INFO;
    char* WARN;
    char* ERROR;
};
enum LCOLORS {LOG_DEBUG=34,LOG_INFO=32,LOG_WARN=33,LOG_ERROR=31,LOG_RESET=0};

struct LTYPES LOG_TYPES = {"DEB", "INF", "WAR", "ERR"};
#endif