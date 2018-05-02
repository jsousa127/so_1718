#include "headers/utilities.h"

bool startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0;
}

int getNumber(char* line) { 
    char aux[2];    
    strncpy(aux,line,2);
    write(1,aux,2);
    return atoi(aux);
}

int contains(int value, int v[],int count) {
    int i;
    for(i=0;i<count;i++){
        if (v[i]==value) return i;
    }
    return 0;
}
