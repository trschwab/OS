
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

pid_t Fork(void);
int Read(int fd, void *buf, size_t count);
int Pipe(int pipefd[2]);
int Write(int fd, const void *buf, size_t count);

int main(void) {
    char write_msg[BUFFER_SIZE] = "Greetings\n";
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    // create the pipe
    Pipe(fd);

    // fork a child

    pid = Fork();

    if (pid < 0) { //error
        fprintf(stderr, "Fork Failed\n");
        return(1);
    }

    if (pid > 0) { //parent
        close(fd[READ_END]); // close unused end of pipe
        
        //write
        int i=-1;
        do {
            i++;
        } while(Write(fd[WRITE_END], &write_msg[i], 1));

        //close write end
        close(fd[WRITE_END]);

    } else {
        //child
        // does not write
        close(fd[WRITE_END]);

        //read
        //

        int i=-1;
        do {
            i++;
            int chk = Read(fd[READ_END], &read_msg[i], 1);
            if (chk != 0) {
                printf("%c", read_msg[i]);
            }
        } while (read_msg[i] != '\0');
        
        printf("\n");

        //close read end
        close(fd[READ_END]);
    }

    return(0);
}

pid_t Fork(void) {  
    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed");
    exit(-1);
    }
    return(pid);
}

int Pipe(int pipefd[2]) {
    int n = pipe(pipefd);
    if (n == -1) {
        perror("Pipe Failed");
        exit(-1);
    }
    return(n);
}

int Read(int fd, void *buf, size_t count) {
    int n = read(fd, buf, count);

    if(n == -1) {
        perror("Read failed");
        exit(-1);
    }
    return(n);
}

int Write(int fd, const void *buf, size_t count) {
    int n = write(fd, buf, count);

    if(n == -1) {
        perror("Write failed");
        exit(-1);
    }
    return(n);
}

