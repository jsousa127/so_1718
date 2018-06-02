#include "headers/runner.h"

//Executa comando simples
char* runSingle(char* cmd) {
        int status,i=0,n=1;
        char* token,*out,*command,*pipeCase,*pipeInput;
        char* exec_args[16];
        char buffer[128];
        int pp[2],it=1;
        pipe(pp);
        
        command = cmd;
        pipeCase = strstr(command,"|");

        if (pipeCase) {
                command[pipeCase-command] = '\0';
                pipeInput = runSingle(command);
                return runPiped(pipeInput,pipeCase+2);

        }

        token = strtok(command," ");
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
                perror("Erro ao executar");
                _exit(1);
        }
        else{
                wait(&status);
                if (WIFEXITED(status)) {
                        if (WEXITSTATUS(status) == 1) return NULL;
                }
        

                close(pp[1]);
                n = read(pp[0],buffer,127);
                buffer[n]='\0';
                out = malloc(n+1);
                strncpy(out,buffer,n);
                if(n == 127) {
                        while(it) {
                                n = read(pp[0],buffer,127);
                                if(n == 0) break;
                                buffer[n] = '\0';
                                sprintf(out,"%s%s",out,buffer);
                        }
                }

                return out;
        }
        
}

//Executa comando composto
char* runPiped(char* input, char* cmd) {
        int status,i=0,n=1;
        char* string,*out,*command,*pipeCase,*pipeInput;
        char* exec_args[128],buffer[128];
        int ppIn[2], ppOut[2];
        pipe(ppIn);
        pipe(ppOut);
        
        command = cmd;
        pipeCase = strstr(command,"|");
        if (pipeCase) {
                command[pipeCase-command] = '\0';
                pipeInput = runPiped(input,command);
                return runPiped(pipeInput,pipeCase+2);

        }

        string = strtok(command," ");
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
                
                if (WIFEXITED(status)) {
                        if (WEXITSTATUS(status) == 1) return NULL;
                }

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







