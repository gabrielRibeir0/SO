#include "person.h"

int new_person(char *name, int age){
    Person p;
    p.age = age;
    strcpy(p.name, name);

    int fd = open(FILENAME, O_CREAT | O_WRONLY, 0664); //ou int fd = open(FILENAME, O_CREAT | O_APPEND, 0664); e não é preciso lseek()
    off_t offset = lseek(fd, 0, SEEK_END);
    write(fd, &p, sizeof(Person));

    int n = offset / sizeof(Person) + 1;
    char output[25];
    int output_size = sprintf(output, "Registo %d\n", n);
    write(1, output, output_size);

    close(fd);
    return 0;
}

int list_n_persons(int N){
    Person p;
    int fd = open(FILENAME, O_RDONLY, 0644);

    int output_size, i = 0;
    char output[250];
    while(i < N  && read(fd, &p, sizeof(Person)) > 0){
        output_size = sprintf(output, "Name: %s | Age: %d\n", p.name, p.age);
        write(1, output, output_size);
        i++;
    }

    close(fd);
    return i;
}

int person_change_age(char *name, int age){
    Person p;
    int fd = open(FILENAME, O_RDWR, 0664);

    char output[250];
    int output_size, old_age;
    while(read(fd, &p, sizeof(Person)) > 0){
        if(strcmp(name, p.name) == 0){
            old_age = p.age;
            p.age = age;
            lseek(fd, -sizeof(Person), SEEK_CUR);
            write(fd, &p, sizeof(Person));

            output_size = sprintf(output, "Person <Name: %s | Age: %d> age changed to %d\n", p.name, old_age, p.age);
            write(1, output, output_size);
        }
    }

    close(fd);
    return 0;
}

int person_change_age_v2(int position, int age){
    Person p;
    int fd = open(FILENAME, O_RDWR, 0664);

    char output[250];
    int output_size, old_age, i = 0;
    while(i < position - 1){
        lseek(fd, sizeof(Person), SEEK_CUR);
        i++;
    }

    read(fd, &p, sizeof(Person));
    old_age = p.age;
    p.age = age;
    lseek(fd, -sizeof(Person), SEEK_CUR);
    write(fd, &p, sizeof(Person));

    output_size = sprintf(output, "Person <Name: %s | Age: %d> age changed to %d\n", p.name, old_age, p.age);
    write(1, output, output_size);

    close(fd);
    return 0;
}