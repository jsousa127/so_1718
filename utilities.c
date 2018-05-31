#include "headers/utilities.h"


// Verifica se uma string é prefixo de outra
int startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? 0 : strncmp(pre, str, lenpre) == 0;
}

//Devolve o numero que se encontra no inicio de uma string
int getNumber(char* line) { 
    char aux[2];    
    strncpy(aux,line,2);
    //write(1,aux,2);
    return atoi(aux);
}

