#include <stdio.h>
#include <unistd.h>
#include "daemon.h"

#define MAX_LINE 1024

void daemon_loop(int fd) {
	char buf[MAX_LINE + 1];
	ssize_t n;

	while ((n = read(fd, buf, MAX_LINE)) > 0) {
		buf[n] = 0;
		printf("[daemon] Received: %s", buf);
	}
}
