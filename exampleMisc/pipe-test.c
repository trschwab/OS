

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {
    char write_msg[BUFFER_SIZE] = "Greetings\n";
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    // create the pipe
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed\n");
        return(1);
    }

    // fork a child

    pid = fork();

    if (pid < 0) { //error
        fprintf(stderr, "Fork Failed\n");
        return(1);
    }

    if (pid > 0) { //parent
        close(fd[READ_END]); // close unused end of pipe
        
        //write
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);

        //close write end
        close(fd[WRITE_END]);

    } else {
        //child
        // does not write
        close(fd[WRITE_END]);

        //read
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("read: %s\n", read_msg);

        //close read end
        close(fd[READ_END]);
    }

    return(0);
}

