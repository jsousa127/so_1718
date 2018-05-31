#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>   
#include "struct.h"

Struct parseFile(char* file_path, Struct s);
