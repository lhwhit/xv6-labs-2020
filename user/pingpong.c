#include "kernel/types.h"
#include "user/user.h"
#define MAXLINE 128

int
main(int argc, char *argv[]) {
	int parent_fd[2], child_fd[2];
	pipe(parent_fd);
	pipe(child_fd);
	char buf[MAXLINE];

	if (fork()) { // Parent
		write(parent_fd[1], "ping", strlen("ping"));
		read(child_fd[0], buf, MAXLINE);
		printf("%d: received %s\n", getpid(), buf);
	} else { // Child
		read(parent_fd[0], buf, MAXLINE);
		printf("%d: received %s\n", getpid(), buf);
		write(child_fd[1], "pong", strlen("pong"));
	}
	exit(0);
}

