#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argn, char* args) {
	const int BUFFSIZE = 50;
	int res = -1;
	char something[BUFFSIZE];
	memset(something, 0, BUFFSIZE);

	printf("Welcome in SimpleCharDriver! Write something and press ENTER: ");
	fgets (something, BUFFSIZE, stdin);
	printf("Writing string %s to device...\n", something);

	int fd = open("/dev/SimpleCharDriver", O_RDWR);
	if(fd < 0) {
		perror("Failed to open file /dev/SimpleCharDriver. Fail");
		return errno;
	}

	res = write(fd, something, sizeof(something));
	if(res < 0) {
		perror("Failed to write to /dev/SimpleCharDriver. Fail");
		return errno;
	}

	memset(something, 0, sizeof(something));
	res = read(fd, something, BUFFSIZE);
	if(res < 0) {
		perror("Failed to read from /dev/SimpleCharDriver. Fail");
		return errno;
	}
	printf("Read: %s\n", something);

	return 0;
}
