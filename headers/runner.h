#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

char* runSingle(char* cmd);
char* runPiped(char* input, char* cmd);
