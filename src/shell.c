#include <stdio.h> 		// standard in/output functions
#include <stdlib.h> 	// general utilities
#include <string.h> 	// string functions
#include <unistd.h> 	// unix sys calls
#include "shell.h" 		// include the header

#define MAX_LINE 1024

void shell_loop(int in_fd, int out_fd, int daemon_fd) {
	char buffer[MAX_LINE]; // declare array of MAX_LINE chars, buffer for user input

	while (1) {
		printf(""); 										// line start
		
		if (fgets(buffer, MAX_LINE, stdin) == NULL) {		// store input from keyboard stdin, up to MAX_LINE chars or "\n" enter, into buffer. Returns buffer with the chars input.
			break; 											// If storage fails, with cmd+d for example, then break loop
		} else {
			buffer[strcspn(buffer, "\n")] = 0;				// fgets adds a "\n" to the buffer, so replace it with null terminator
			
			if (strcmp(buffer, "exit") == 0) {				// If the submitted buffer is "exit", then break loop
				break;
			}
		}
		
		write(daemon_fd, buffer, strlen(buffer)); // Send command to daemon via the socket
		write(daemon_fd, "\n", 1); // Send termination signal
	}
}
