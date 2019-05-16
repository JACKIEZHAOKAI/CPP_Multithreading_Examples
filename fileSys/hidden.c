/*
 * hidden.c
 *
 * Demonstrate delayed file block deletion when processes are
 * actively using a deleted file.
 *

 File systems do not free up blocks storing file data until all processes using a file have closed it. 
 As a result, removing a file can remove the directory entry for the file 
 (i.e., it no longer shows up in a directory listing) but the file itself still exists 
 (i.e., processes using the file can still read and write data in the file). 


 * % cp hidden.c file.in
 * % gcc hidden.c
 * % ./a.out
 * Opened file.in for reading
 * Type enter:
 * 
 *[1]+  Stopped                 ./a.out
 * % rm file.in
 * % ls file.in
 * ls: cannot access file.in: No such file or directory
 * % fg
 *
 * Geoff Voelker
 * May 2018
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int
main (int argc, char *argv[])
{
    char buff[256];
    int r, fd;

    fd = open ("file.in", O_RDONLY);
    if (fd < 0) {
	printf ("Failed to open input file\n"); return -1;
    }
    printf ("Opened file.in for reading\n");

    printf ("Type enter:\n");
    if (read (STDIN_FILENO, buff, 256) <= 0) {
	printf ("Failed to read from stdin\n"); return -1;
    }

    // suspend and delete file

    printf ("Reading from file.in\n");
    r = read (fd, buff, 16);
    if (r <= 0) {
	printf ("Failed to read from input file\n"); return -1;
    }

    buff[r] = '\0';
    printf ("%s\n", buff);

    return 0;
}

