#include "headers/struct.h"

struct file {
    char* lines[128];
    int indexes[128];
    int li,ii,sucess;
};

Struct initStruct() {
    Struct st = malloc(sizeof(struct file));
    st->li = -1;
    st->ii = -1;
    st->sucess = 0;
    return st;  
}

Struct populate(Struct s, int file) {
    int n,flag=0;
    char buf[2048];
    char* token;
    
    n = read(file,buf,2048);
    token = strtok(buf,"\n");
    
    while(token != NULL)  {    
        if(!strcmp(token,"<<<"))
                flag=1;
        if(!flag)
                s = addLine(s,token);
        if(!strcmp(token,">>>"))
                flag=0;
        token = strtok(NULL, "\n");

    }
    
    return s;
}

Struct addLine(Struct st, char* line) {
    char* new = malloc(strlen(line));
    strcpy(new,line);
    st->li++;
    st->lines[st->li] = new;
     
    if(line[0]=='$'){
            st->ii++;
            st->indexes[st->ii] = st->li;
    }
    return st;
}

Struct execCommands(Struct s) {
    int n;
printf("%d\n",s->ii);
    for(n=0;n<=s->ii;n++) {
         
        if(!runCommand(s->lines[s->indexes[n]],n))
            break;
        if(n==(s->ii)) s->sucess = 1;
    }

    return s;
}

void writeOutput(int file, int n) {
    char buf[1024],aux[2];
    int count,path;
    sprintf(aux,"%d",n);
    path = open(aux,O_RDONLY);
    count = read(path,buf,1024);
    printf("%d",count);
    write(file,"<<<\n",4);
    write(file,buf,count);
    write(file,">>>\n",4);
}

void writeFile(Struct s, int file) {
    int i=0,n;
    while(i<=s->li){   
        write(file,s->lines[i],strlen(s->lines[i]));
        write(file,"\n",1);
        if((n=contains(i,s->indexes,s->ii))>=0){
                writeOutput(file,n);
        }
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
