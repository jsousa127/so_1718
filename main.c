#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "headers/struct.h"
#include "headers/parser.h"

int main(int argc, char* argv[]) {
    int file;

    Struct s = initStruct(); // Iniciar a estrutura de dados
    parseFile(argv[1],s); // Parse do ficheiro txt para a estrutura
    s = execCommands(s); // Execução dos comandos
    
    if (execSucess(s)) { // Escrita no ficheiro, caso a execução tenha sido bem sucedida.
            file=open(argv[1],O_WRONLY | O_TRUNC, 0666);
            writeFile(s,file);
            close(file);
    }
    else write (1,"Erro na execução dos comandos\n",32);
    
    cleanUp(s); // Limpeza da memória utilizada
    return 0;
}
