#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>

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

int Open(char *path, int flag) {
    int n = open(path, flag);
    
    if(n == -1) {
        perror("Open failed");
        exit(-1);
    }
    return(n);
}

int Close(int fd) {
    int n = close(fd);

    if (n == -1 ) {
        perror("Close failed");
        exit(-1);
    }
    return(n);
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int n = bind(sockfd, addr, addrlen);
    
    if (n == -1) {
        perror("Bind failed");
        exit(-1);
    }
    return(n);
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int n = connect(sockfd, addr, addrlen);

    if (n == -1) {
        perror("Connect failed");
        exit(-1);
    }
    return(n);
}

int Listen(int sockfd, int backlog) {
    int n = listen(sockfd, backlog);

    if (n == -1) {
        perror("Listen failed");
        exit(-1);
    }
    return(n);
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int n = accept(sockfd, addr, addrlen);

    if (n == -1) {
        perror("Accept failed");
        exit(-1);
    }
    return(n);
}

int Waitpid(pid_t pid, int *status, int options) {
    pid_t n =  waitpid(pid, status, options);

    if (n == -1) {
        perror("Waidpid failed");
        exit(-1);
    }
    return(n);
}
