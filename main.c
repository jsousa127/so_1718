#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "headers/struct.h"
#include "headers/parser.h"

int ids[16];
int nc = 0;

int forFile(char* file) {
    int fil;

    Struct s = initStruct(); // Iniciar a estrutura de dados
    parseFile(file,s); // Parse do ficheiro txt para a estrutura
    s = execCommands(s); // Execução dos comandos
    
    if (s != NULL) { // Escrita no ficheiro, caso a execução tenha sido bem sucedida.
            fil=open(file,O_WRONLY | O_TRUNC, 0666);
            writeFile(s,fil);
            close(fil);
            cleanUp(s);
            return 1;
    }
    else return 0;
}

void killChildren() {
    
    int i;
    
    for(i = 0; i < nc; i++) {
        kill(ids[i], SIGKILL);
    }

}

int main(int argc, char* argv[]) {
    int i,fk;
    
    signal(SIGINT,killChildren);
    for(i = 1; i < argc; i++) {
        if(!(fk=fork())) {   
            forFile(argv[i]);
            sleep(5);
            _exit(1);
        } 
        else {
            ids[i-1] = fk;
            nc++;
        }
    }
    return 0;
}