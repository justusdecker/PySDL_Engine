struct LCOLORS{
    char DEBUG;
    char INFO;
    char WARN;
    char ERROR;
    char RESET;
};

struct LTYPES{
    char* DEBUG;
    char* INFO;
    char* WARN;
    char* ERROR;
};

/*
Pretty logs:
    - Places automatically an \n at the end
    - colorize the terminal a bit
*/
void LOG_WRITE(char* msg, int color, char* logtype);