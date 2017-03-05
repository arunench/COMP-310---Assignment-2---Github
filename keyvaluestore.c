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
#include <semaphore.h>

struct key_value{
	int key;
	char* value;
};

struct key_value kv;
kv.key = 1;
kv.value = "foo";


// This function creates a store if it is not yet created or opens the store if it is already created
int kv_store_create(char *name){

}

// This function takes a key-values pair and writes them to the store. The key and value strings can be length limited
int kv_store_write(char *key, char *value){

}

// This function takes a key and searches the store for the key-value pair.
char *kv_store_read(char *key){

}

// This function takes a key and returns all the values in the store. A NULL is returned if there is no records for the key.
char **kv_store_read_all(char *key){
	
}


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