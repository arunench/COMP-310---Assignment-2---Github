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

int main (int argc, char **argv){

	char *str = argv[1];
	//Shared memory is created under the name "myshared"
	int fd = shm_open("arunenshared", O_CREAT|O_RDWR, S_IRWXU); 
	printf("Creating memory object...\n");
	//Map the shared memory object starting at an address
	//By specifying a NULL calue for the first argument of the mmap(), we are letting the kernel pick the starting location
	//For the shared memory object in the virtual address space
	char *addr = mmap(NULL, strlen(str), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
	
	//The ftruncatre() call is used to resize the shared memory object to fit the string (first argument)
	ftruncate(fd, strlen(str));

	close(fd);
	
	//We copy the bytes into the shared memory region
	memcpy(addr, str, strlen(str));

}