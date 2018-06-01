#include "headers/runner.h"

//Executa comando simples
char* runSingle(char* cmd) {
        int status,i=0,n=1,sizeOut=0;
        char* token,* out,*aux,*str;
        char* exec_args[16];
        char buffer[128];
        int pp[2],it=1;
        pipe(pp);
        aux = cmd;
        token = strtok(aux," ");
        while(token!=NULL){
                exec_args[i]=token;
                token=strtok(NULL," ");
                i++;
        }
        exec_args[i]=NULL;

        if(!fork()){
                close(pp[0]);
                dup2(pp[1],1); 
                execvp(exec_args[0],exec_args);
                _exit(1);
        }
        else{
                wait(&status);
                close(pp[1]);
                n = read(pp[0],buffer,128);
                buffer[n]='\0';
                out = malloc(n+1);
                strcpy(out,buffer);
                if(n == 128) {
                    while(it) {
                        n = read(pp[0],buffer,128);
                        if(n == 0) break;
                        buffer[n] = '\0';
                        sprintf(out,"%s%s",out,buffer);
                    }
                }

                //out[sizeOut] = '\0';

                return out;
        }
}

//Executa comando composto
char* runPiped(char* input, char* cmd) {
        int status,i=0,n=1;
        char* string,*out,buffer[128];
        char* exec_args[128],*aux;
        int ppIn[2], ppOut[2];
        pipe(ppIn);
        pipe(ppOut);
        aux = cmd;
        string = strtok(aux," ");

        while(string!=NULL) {
                exec_args[i]=string;
                string=strtok(NULL," ");
                i++;
        }
        exec_args[i]=NULL;


        if(!fork()) {
                close(ppIn[1]);
                dup2(ppIn[0],0);
                close(ppOut[0]);
                dup2(ppOut[1],1);

                execvp(exec_args[0],exec_args);
                perror("Erro ao executar");
                _exit(1);
        }
        else {
                close(ppIn[0]);
                write(ppIn[1], input, strlen(input));
                close(ppIn[1]);
                wait(&status);
                close(ppOut[1]);
                n = read(ppOut[0],buffer,128);
                buffer[n]='\0';
                out = malloc(n+1);
                strcpy(out,buffer);
                if(n == 128) {
                    while(n) {
                        n = read(ppOut[0],buffer,128);
                        if(n == 0) break;
                        buffer[n] = '\0';
                        sprintf(out,"%s%s",out,buffer);
                    }
                }
                        return out;
        } 
}   







