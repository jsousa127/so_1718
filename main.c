#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

Struct populate(Struct s, int file) {
    int n;
    char buf[1024];
    char* token;
    n = read(file,buf,1024);
    token = strtok(buf,"\n");
    while(token != NULL)  {
        s = addLine(s,token);
        token = strtok(NULL, "\n");    
    }
    
    return s;
}

int main(int argc, char* argv[]) {
    int file;
    char* line;
    Struct s = initStruct();
    
    file=open(argv[1], O_RDONLY, 0666);
    s = populate(s,file);
    close(file); 
    //s = execCommands(s);
    if (execSucess(s)) {
            file=open(argv[1],O_WRONLY | O_TRUNC, 0666);
            writeFile(s,file);
            close(file);
    }
    else write (1,"Erro na execução dos comandos\n",30);
            
    return 0;
}
