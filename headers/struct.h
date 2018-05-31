
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "runner.h"
#include "utilities.h"

typedef struct file *Struct;

Struct addCommand(char* comment,char* command,Struct st);
Struct initStruct();
void cleanUp(Struct s);
void writeFile(Struct s,int file);
Struct execCommands(Struct s);
int execSucess(Struct st);
void printStruct(Struct s);
