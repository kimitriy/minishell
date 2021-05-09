#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int     main()
{
    int			res;
	struct stat	buf;
	
	res = stat("/Users/rburton/.brew/bin/screenfetch", &buf);
	// res = stat("/Users/rburton/f", &buf);

	printf("res: %d\n", res);

	if (buf.st_mode & R_OK)
		printf("read ");
	if (buf.st_mode & W_OK)
		printf("write ");
	if (buf.st_mode & X_OK)
		printf("execute");

	// printf("buf.st_mode: %hu\n", buf.st_mode);
    return(0);
}