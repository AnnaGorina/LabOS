#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argv, char* argc[])
{
	if(argv < 2)
	{
		printf("not enough params\n");
		return -1;
	}	
	
	struct stat buff;

	int first_file, second_file;
	first_file = open(argc[1], O_RDWR, 0600);

	if(first_file < 0)
	{
		printf("error with open file\n");
		return -2;
	}

	fstat(first_file, &buff);

	char* data = (char *)mmap(NULL, buff.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, first_file, 0);

	second_file = creat(argc[2], 0400);

	if(second_file < 0)
	{
		printf("error witn creat file\n");
		return -3;
	}

	ftruncate(second_file, buff.st_size);

	write(second_file, data, buff.st_size);

	close(second_file);
	close(first_file);

	munmap(data, buff.st_size);

	printf(argc[1], argc[2]);
	return 0;
}
