
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct file *Struct;

Struct addLine(Struct st, char* line);
Struct initStruct();
void writeFile(Struct s,int file);
char ** getLines(Struct s);
int getLi(Struct s);
int execSucess(Struct st);
void printStruct(Struct st);
