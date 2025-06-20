#include <stdio.h> // paste in stdio.h from system libraries
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include "shell.h" // paste in shell.h contents from current directory
#include "daemon.h"

int main() {
	printf("Welcome to the ServShell REPL.\n"); // For now, assume execution from the terminal
	
	int sv[2];	 										// Init socket vector for socket file descriptors
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) < 0) { 	// Sys call to create two connected sockets, creates UNIX socket, stream-type, always protocol AF_UNIX, and sv is the vector for file descriptors
		perror("socketpair");
		exit(1); 										// Terminate program at error for now, TODO: better error handling?
	}
	
	pid_t pid = fork(); 	// Create new process
	
	if (pid < 0) { 			// pid < 0 if forking fails
		perror("fork");
		exit(1);			// Terminate program at error for now, TODO: better error handling?
	}
	
	if (pid == 0) {			// The process is the child: used as the client
		close(sv[0]);		// Close client access to parent's socket side
		
		shell_loop(
			STDIN_FILENO,   // input/output from a wrapper program or terminal if ran as CLI
			STDOUT_FILENO,
			sv[1] 			// file descriptor as secret address to daemon
		);

		close(sv[1]);		// Close the shell after loop
		exit(0);
	} else {				// Parent: shell daemon
		close(sv[1]);
		daemon_loop(sv[0]);
		close(sv[0]);
	}
	
	return 0;
}
