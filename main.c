#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "headers/struct.h"


int main(int argc, char* argv[]) {
    int file;
    char* line;
    Struct s = initStruct();
    file=open(argv[1], O_RDONLY, 0666);
    s = populate(s,file);
    close(file); 
    s = execCommands(s);
    if (execSucess(s)) {
            file=open(argv[1],O_WRONLY | O_TRUNC, 0666);
            writeFile(s,file);
            close(file);
    }
    else write (1,"Erro na execução dos comandos\n",32);
            
    return 0;
}
