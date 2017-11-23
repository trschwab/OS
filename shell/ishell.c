#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "wrappers.c"

#define MAXLINE 25

int main(void) {
    char buf[MAXLINE];
    //char *prevArg;//[MAXLINE];
    pid_t pid;
    int status; 
    char *args[MAXLINE];
    //char *commands[MAXLINE];
    char *s = " ";
    //char *semi = ";"; 
    printf("ishell> ");
    while(fgets(buf, MAXLINE, stdin) != NULL) {
        /*
        if ((prevArg[0] ==  '\n') && (buf[0] == '\n')) {
            //problem 3
            printf("okay\n");
            }
            */
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = 0;
            }
        pid = Fork();
        if (pid < 0) {
            perror("fork error");
        } else if (pid == 0) { // child
            int i = 0;
            //strcpy(prevArg, buf);
            args[i] = strtok(buf, s);
            while(args[i] != NULL) {
                i++;
                args[i] = strtok(NULL, s);
            } 
            execvp(args[0], args);
            printf("[ishell: program terminated abnormally][%d]\n", WEXITSTATUS(status));
            //int wif = WIFEXITED(status);
            //printf("child wif is %d\n", wif);
            exit(0);
        }
        //parent
        pid = Waitpid(pid, &status, 0);
        int wif = WIFEXITED(status);
        printf("wif is %d\n", wif);
        int exitStatus = WEXITSTATUS(status);
        printf("the exitstat is : %d\n", WEXITSTATUS(status));
        /*
        if (error != -1) {
                printf("[ishell: program terminated successfully]\n");
            } else {
                printf("[ishell: program terminated abnormally][%d]\n", error);
            }
        */
        printf("ishell> ");
    }
    exit(0);
}
