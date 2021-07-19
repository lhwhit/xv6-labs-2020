#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) 
{
	if (argc != 2) {
		printf("Parameters error.\n");
		printf("Usage: sleep <n>\n");
	} else {
		int x = atoi(argv[1]);
		sleep(x);
	}
	exit(0);
}

