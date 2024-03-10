#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

#define MAX_RAND 100
#define ROWS 10
#define COLUMNS 1000


void createMatrix();

void printMatrix();

// ex.5
int valueExists(int value);

// ex.6
void linesWithValue(int value);