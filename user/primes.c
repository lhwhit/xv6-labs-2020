#include "kernel/types.h"
#include "user/user.h"

void source() {
	int i;
	for (i = 2; i < 36; i++) {
		write(1, &i, sizeof(i));
	}
}

void cull(int p) {
	int n;
	while (read(0, &n, sizeof(n))) {
		if (n % p != 0) {
			write(1, &n, sizeof(n));
		}
	}
}

void redirect(int k, int pd[]) {
	close(k);  // close Standard input/output file. 0/1=input/output
	dup(pd[k]); // redirect pd[k] to Standard input/output file
	close(pd[0]); // close pd[0]
	close(pd[1]); // close pd[1]
}

void sink() {
	int pd[2];
	int p;
	if (read(0, &p, sizeof(p))) {  // read an int from Standard input file
		printf("prime %d\n", p);   // output prime
		pipe(pd);  // create a pipe
		if (fork()) { // create a process.
			redirect(0, pd);
			sink();
		} else {
			redirect(1, pd);
			cull(p);
		}
	}
}

int main(int argc, char *argv[]) {
	int pd[2];
	pipe(pd); // create a pipe

	if (fork()) {  // parent process
		redirect(0, pd);  // redirect pd[0] to Standard input file
		sink();
	} else {
		redirect(1, pd); // redirect pd[1] to Standard output file
		source(); // send 2-35 to Standard output file
	}
	exit(0);
}

