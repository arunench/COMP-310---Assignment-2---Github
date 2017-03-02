//Arunen Chellan
//Assignment 2
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// This program illustrates the three major activities we need to perform with POSIX shared memory,
// setting up, writing, and reading
int main (int argc, char **argv){

	char *str = argv[1];
	struct stat s;
	// Shared memory is created under the name "myshared"
	int fd = shm_open("achell", O_CREAT|O_RDWR, S_IRWXU); 
	if (fd < 0){
		printf("Error.. opening shm\n");
	}

	printf("Creating memory object...\n");

	// fstat() system call allows us to determine the length of the shared memory object
	// This length is used in the mmap() so that we can map only that portion into the virtual address space
	if (fstat(fd, &s) == -1)
		printf("Error fstat\n");
	// Map the shared memory object starting at an address
	// By specifying a NULL calue for the first argument of the mmap(), we are letting the kernel pick the starting location
	// For the shared memory object in the virtual address space
	char *addr = mmap(NULL, s.st_size, PROT_READ, MAP_SHARED, fd, 0); 
	
	// The ftruncatre() call is used to resize the shared memory object to fit the string (first argument)
	// ftruncate(fd, strlen(str));

	close(fd);
	
	// We copy the bytes into the shared memory region
	// memcpy(addr, str, strlen(str));

	write(STDOUT_FILENO, addr, s.st_size);

}