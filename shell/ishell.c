// extra feature added was indefinite commands per line separated by semicolons as opposed to two

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
    printf("ishell> ");
    while(fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = 0;
            }
        if ((buf[0] == '\t') && (buf[1] == '\t')) { 
            run("ls");
        } else {
            int i = 0;
            semi = ";";
            command[i] = strtok(buf, semi);
            run(*command);
            command[i] = strtok(NULL, semi);
            while (*command != NULL) {
                run(*command);
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


