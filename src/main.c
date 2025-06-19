#include <stdio.h> // paste in stdio.h from system libraries
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include "shell.h" // paste in shell.h contents from current directory
#include "daemon.h"

int main() {
	printf("Welcome to the ServShell REPL.\n"); // For now, assume execution from the terminal
	
	int sv[2];	 										// Init socket vector for socket file descriptors
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) < 0) { 	// sys call to create two connected sockets, creates UNIX socket, stream-type, always protocol AF_UNIX, and sv is the vector for file descriptors
		perror("socketpair");
		exit(1); 										// Terminate program for now, TODO: better error handling
	}
	
	pid_t pid = fork(); 	// Create new process, save the process id
	if (pid < 0) { // pid < 0 if forking fails
		perror("fork");
		exit(1);
	}
	
	if (pid == 0) {			// Child: client, for now just stream text from terminal
		close(sv[0]);		// Close your access to parent's socket side
		shell_loop(sv[1]);
		close(sv[1]);
		exit(0);
	} else {				// Parent: shell daemon
		close(sv[1]);
		daemon_loop(sv[0]);
		close(sv[0]);
	}
	
	return 0;
}
