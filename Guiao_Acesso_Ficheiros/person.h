#ifndef PERSON_H
#define PERSON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define FILENAME "file_pessoas"

typedef struct person{
    char name[200];
    int age;
} Person;

int new_person(char *name, int age);

int list_n_persons(int N);

int person_change_age(char *name, int age);

int person_change_age_v2(int position, int age);
#endif