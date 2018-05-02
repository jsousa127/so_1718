
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "headers/runner.h"

typedef struct file *Struct;

Struct addLine(Struct st, char* line);
Struct initStruct();
Struct populate(Struct s, int file);
void writeFile(Struct s,int file);
char ** getLines(Struct s);
Struct execCommands(Struct s);
int execSucess(Struct st);
void printStruct(Struct st);
