#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


typedef enum { false, true } bool;

bool startsWith(const char *pre, const char *str);
int getNumber(char* line);
int contains(int value, int v[],int count);

