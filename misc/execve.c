#include <stdio.h>
#include <errno.h>
#include <sys/types.h> //fork , kill
#include <sys/wait.h>  //wait
#include <term.h>  // termcap
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

int		main(int argc, char **argv, char **envp)
{
	(void)argc;

	pid_t	pid;
	char	**arr;

	arr = (char**)malloc(4 * sizeof(char*));

	// arr[0] = argv[0];
	// arr[1] = "-la";
	// arr[2] = "/Users/rburton/";
	// arr[3] = NULL;

	arr[0] = argv[0];
	// arr[1] = "-la";
	// arr[2] = "/Users/rburton/";
	arr[1] = NULL;

	pid =  fork();

	if (pid == 0)
	{
		execve("/Users/rburton/.brew/bin/screenfetch", arr, envp);
		// execve(".brew/bin/screenfetch", arr, envp);
		// execve("/screenfetch", arr, envp);
		printf("ERROR EXECVE");
	}
	else
	{
		printf("1\n");
		wait(&pid);
		printf("2\n");
	}

	return(0);
}