#include "struct.h"

struct file {
    char* lines[128];
    int indexes[128];
    int li,ii,sucess;
};

Struct addLine(Struct st, char* line) {
    char* new = malloc(sizeof(line));
    strcpy(new,line);
    st->li++;
    st->lines[st->li] = new;
 
    if(line[0]=='$'){
            st->ii++;
            st->indexes[st->ii] = st->li;
    }
    return st;
}

Struct initStruct() {
    Struct st = malloc(sizeof(struct file));
    st->li = -1;
    st->ii = -1;
    sucess = 0;
    return st;  
}

Struct execCommands(Struct s) {
    
}

void writeFile(Struct s, int file) {
    int i=0;
    while(i<=s->li){
        write(file,s->lines[i],strlen(s->lines[i]));
        write(file,"\n",1);
        i++;
    }
}

int execSucess(Struct s) {
    return s->sucess;
}

void printStruct(Struct st) {
    int i;    
    for(i=0;i<=st->li;i++){
        printf("%s\n",st->lines[i]);
    }
}
