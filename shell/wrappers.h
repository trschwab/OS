#ifndef headerName
#define headerName

pid_t Fork(void);
int Pipe(int pipefd[2]);
int Read(int fd, void *buf, size_t count);
int Write(int fd, const void *buf, size_t count);
int Open(char *path, int flag);
int Close(int fd);
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
pid_t Waitpid(pid_t pid, int *status, int options);

#endif
