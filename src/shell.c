#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

#define MAX_LINE 1024

void shell_loop(void) {
	char line[MAX_LINE];

	while (1) {
		printf("> ");
		if (!fgets(line, MAX_LINE, stdin)) {
			// ctrl-d (EOF)
			break;
		}

		// Remove trailing newline
		line[strcspn(line, "\n")] = 0;

		if (strcmp(line, "exit") == 0) {
			break;
		}

		pid_t pid = fork();
		if (pid == 0) {
			// Child process
			char *args[] = {line, NULL};
			execvp(args[0], args);
			perror("execvp");
			exit(EXIT_FAILURE);
		} else if (pid > 0) {
			// Parent process
			wait(NULL);
		} else {
			perror("fork");
		}
	}
}
