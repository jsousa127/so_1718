#include "headers/struct.h"

//Estrutura que armazena um comando, o seu comentário e o seu output
typedef struct command {
        char* comment;
        char* cmd;
        char* output;
} *Command; 

//Estrutura que armazena todos os nosso comandos
struct file {
        Command* comands;
        int size;
        int sizeT;
        int sucess;
};

//Iniciar estrutura file
Struct initStruct() {
        Struct st = malloc(sizeof(struct file));
        st->size = 0;
        st->sizeT = 128;
        st->sucess = 0;
        st->comands = malloc(st->sizeT);

        return st;  
}

//Adicionar comando à estrutura
Struct addCommand(char* comment,char* command,Struct st) {
        Command c = malloc(sizeof(struct command));
        c->comment = strdup(comment);
        c->cmd = strdup(command);
        c->output = NULL;
        st->comands[st->size] = c;
        st->size++;
        if (st->size == st->sizeT - 1) {
                st->sizeT *= 2;
                st->comands = realloc(st->comands, st->sizeT);
        }
        return st;
}

// Atribuir output a um comando
void setOutput(Command c, char* output) {
        c->output = strdup(output);
}

// Devolve o output de um comando
char* getOutput(Struct s, int cmdNumber) {
        Command c = s->comands[cmdNumber];
        return c->output;
}

// Executar um comando
void runCommand(Struct s,int cmdNumber){
        char* out;
        int n = 1, sum = 3;
        Command c = s->comands[cmdNumber];
        char* cmd = malloc(strlen(c->cmd));
        strcpy(cmd,c->cmd);
        if(startsWith("$|",cmd)) {

                if(cmd[2]!=' '){
                        n = getNumber(cmd+2);
                        if(n>9) sum = 5;
                        else sum = 4;
                }

                char* in = getOutput(s,cmdNumber-n);

                out = runPiped(in,cmd+sum);
        }
        else out = runSingle(cmd+2);
        setOutput(c,out);
        return;
}

//Execução da lista de comandos
Struct execCommands(Struct s) {
        int n;

        for(n=0;n<s->size;n++) {
                runCommand(s,n);
                if(n==(s->size)-1) s->sucess = 1;
        }

        return s;
}

//Escrever comentário no ficheiro
void writeComment(Command c, int file) {
        if(c->comment[0]=='\n') c->comment=c->comment +1;
        write(file,c->comment,strlen(c->comment));
}

//Escrever comando no ficheiro
void writeCommand(Command c, int file) {
        write(file,c->cmd,strlen(c->cmd));
}

//Escrever output no ficheiro
void writeOutput(Command c, int file) {
        if(c->output){
                write(file,"\n<<<\n",5);
                write(file,c->output,strlen(c->output));
                write(file,">>>\n",4);
        }
}

//Escrever estrutura no ficheiro
void writeFile(Struct s, int file) {
        int i=0;
        Command c;
        while(i<s->size){
                c = s->comands[i];
                c->cmd = c->cmd;
                writeComment(c,file);
                writeCommand(c,file);
                writeOutput(c,file);
                i++;
        }
}

//Libertar memória da estrutura
void cleanUp(Struct s) {
        int i;
        Command c;
        for(i=0;i<s->size;i++) {
                c = s->comands[i];
                free(c->cmd);
                if(c->output) free(c->output);
                free(c);    
        }
}

// Verificar se a execução dos comandos foi bem sucedida
int execSucess(Struct s) {
        return s->sucess;
}


