#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "wrappers.c"
#include "ishell.h"

int main(void) {
    char buf[MAXLINE];
    char *command[MAXLINE]; 
    char *semi;
    char prev[MAXLINE]; 
    char *log[30];
    int iteration = -1;
    printf("ishell> ");
    while(fgets(buf, MAXLINE, stdin) != NULL) {
        iteration++;
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = 0;
            log[iteration] = malloc(sizeof(buf));
            log[iteration] = strcpy(log[iteration], buf);
            }
        if (strcmp(buf, "exit") == 0) {
            run("echo ");
            break;
        }
        /*
         * adding funcionality where !n executes the nth command
         *
        if ((buf[0] == '!') && ((int) buf[1] >= (int) '0') && ((int) buf[1] <= (int) '9')) {
            int n = atoi(&buf[1]);
            printf("n %d\n", n);
            printf("comm %s\n", log[n]);
            run(log[n]);
        }
        */
        if (strcmp(buf, "history") == 0) {
            int i = 0;
            while(log[i] != NULL) {
                printf("%s\n", log[i]);
                i++;
            }
            run("echo ");
        } else if (strcmp(buf, "previous") == 0) {
            run(prev);
        } else if ((buf[0] == '\t') && (buf[1] == '\t')) { 
            run("ls");
            strcpy(prev, "ls");
        } else {
            int i = 0;
            semi = ";";
            command[i] = strtok(buf, semi); 
            run(*command);
            strcpy(prev, *command);
            command[i] = strtok(NULL, semi);
            while (*command != NULL) {
                run(*command);
                strcpy(prev, *command);
                command[i] = strtok(NULL, semi);
            }
        } 
        printf("ishell> ");
        }
    exit(0);
}

void run(char buf[MAXLINE]) {
    pid_t pid;
    pid = Fork();
    if (pid == 0) { // child 
        char *args[MAXLINE];
        int i = 0;
        char *s = " ";
        //tokenize buf by spaces
        args[i] = strtok(buf, s);
        while(args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, s);
        } 
        if (execvp(args[0], args) == -1) {
            exit(-1);
        }
        exit(0);
    }
    int status;
    pid = Waitpid(pid, &status, 0);
    const int error = WEXITSTATUS(status);
    if (error == 0) {
            printf("[ishell: program terminated successfully]\n");
    } else {
            printf("[ishell: program terminated abnormally][%d]\n", error);
    }
}


