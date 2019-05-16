/*
 * corrupt.c
 *
 When multiple processes are writing to the same file at the same time without any coordination,
  you should assume that the file will become corrupted. This situation is a race condition 
  similar to multiple threads accessing a shared data structure in memory at the same time. 
  The program corrupt.c demonstrates this scenario with four processes writing to the same file:

 * Demonstrate file corruption with four processes writing to the same
 * file at the same time without synchronization or coordination.
 *
 * % gcc corrupt.c
 * % ./a.out
 * % cat file.out
 *
 * Geoff Voelker
 * May 2018
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int
main (int argc, char *argv[])
{
    int i, fd;

    fd = open ("file.out", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0)
	printf ("Failed to open output file\n");

    fork();
    fork();
    
    for (i = 0; i < 4; i++) {
	char *ptr, *str = "4 processes writing to the same file\n";

	for (ptr = str; *ptr; ptr++) {
	    if (write (fd, ptr, 1) < 0) {
		printf ("Failed to write to output file\n");
		return -1;
	    }
	}
    }
    
    close (fd);
    return 0;
}

