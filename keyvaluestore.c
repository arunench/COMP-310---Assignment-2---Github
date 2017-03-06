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

char kv_db[256*256*256 + (3*256)]; 
char *addr;
int KV_SIZE = sizeof(kv_db);
int NUMBER_OF_PODS = 256;
int NUMBER_OF_ENTRIES = 256;
int ENTRY_SIZE = 256;
int fd;



// This function creates a store if it is not yet created or opens the store if it is already created
int kv_store_create(char *name){



	fd = shm_open(name, O_CREAT|O_RDWR, S_IRWXU); 

	addr = mmap(NULL, KV_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	for (int i = 0; i < KV_SIZE; i++){
		addr[i] = NULL;
	}


	if (fd < 0){
		printf("Error.. opening shm\n");
		return -1;
	}
	else{
		
		printf("Creating memory object...\n");
		printf("This is the file descriptor: %d\n", fd);
		printf("Truncating the file descriptor to appropriate size\n");
		ftruncate(fd, KV_SIZE);
		close(fd);
	}

	printf("This is the size of the database in bytes: %d\n", KV_SIZE);
	return 0;
}

// This function takes a key-values pair and writes them to the store. The key and value strings can be length limited
int kv_store_write(char *key, char *value){

	int key_size = strlen(key);
	int pod_num = hash_func(key);
	printf("Intserting the key: %s, with value: %s\n", key, value);
	printf("Inserting at pod %d\n", pod_num);
	int location_wr = pod_num * NUMBER_OF_ENTRIES * ENTRY_SIZE + 3; 
	int i = location_wr;

	while(i < (location_wr + 256*256)){

		if (addr[i] == NULL){

			int offset = i;
			printf("At index %d we insert the characters\n", i);

			for (int j = 0; j < strlen(value); j++){
				addr[i+j] = value[j];
				printf("At index %d we insert the character %c\n", i+j, addr[i+j]);
			}

			memcpy(addr + offset, value, ENTRY_SIZE);
			printf("Copied into memory\n");
			return 0;

		}

		else{

			printf("This is whats in that memory location %c\n", addr[i]);
			i = i + 256;
			printf("That memory location is already full, need to increment to next data entry. Will check memory space %d\n", i);

		}
		
	}
		
	return 0;
}

// This function takes a key and searches the store for the key-value pair.
char *kv_store_read(char *key){

}

// This function takes a key and returns all the values in the store. A NULL is returned if there is no records for the key.
char **kv_store_read_all(char *key){
	
}

// int createIndex(kv_db){

// 	for (int i=0; i<KV_SIZE; i = i + (256*256)){
		
// 		kv_db[i] = 0;
// 	}

// }

int findIndex(){

	printf ("Size of database: %zu\n", sizeof(kv_db));
}

int hash_func(char *word){
    int hashAddress = 5381;
    for (int counter = 0; word[counter]!='\0'; counter++){
        hashAddress = ((hashAddress << 5) + hashAddress) + word[counter];
    }
    return hashAddress % NUMBER_OF_PODS < 0 ? -hashAddress % NUMBER_OF_PODS : hashAddress % NUMBER_OF_PODS;
}

// This program illustrates the three major activities we need to perform with POSIX shared memory,
// setting up, writing, and reading
int main (int argc, char **argv){

	kv_store_create("achell");
	kv_store_write("Arunen", "Today");
	kv_store_write("Arunen", "Green");

}