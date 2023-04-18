/* program ex03-01.c */
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
	int filedes, fdnew1, fdnew2;
	ssize_t nread;
	off_t newpos;

	char buffer[1024];
	char content[] = "Hello my friend!\n";

	if((filedes = open("data.txt", O_RDWR)) == -1) {
		perror("data.txt");
		exit(-1);
	}
	else {
		//while((nread = read(filedes, buffer, 1024)) > 0) printf("%s", buffer);
		nread = read(filedes, buffer, 1024);
	       	printf("%s", buffer);
		if(write(filedes, content, strlen(content)) < strlen(content)) {
			close(filedes);
			exit(-1);
		}
		newpos = lseek(filedes, (off_t)0, SEEK_SET);
		while((nread = read(filedes, buffer, 1024)) > 0) printf("%s", buffer);

		close(filedes);
	}

	if((fdnew1 = open("newdata1.txt", O_RDWR | O_CREAT, 0644)) == -1) {
		perror("newdata1.txt");
		exit(-1);
	}
	if((fdnew2 = creat("newdata2.txt", 0644)) == -1) {
		perror("newdata2.txt");
		exit(-1);
	}

	close(fdnew1); close(fdnew2);
	unlink("newdata2.txt");

	return 0;
}
