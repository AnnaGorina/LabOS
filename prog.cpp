#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <new>
#include <linux/stat.h>

#define FIFO "FiFO"

int main(int argc, char* argv[])
{
	srand(time(NULL));
	int N = atoi(argv[1]);
	int fd[2];
	pipe(fd);
	pid_t process = fork();

	if(process < 0) std::cout << "ERROR" << std::endl;
	else if(process > 0)
	{
		umask(0);
		mknod(FIFO, S_IFIFO|0666, 0);

		int file = open(FIFO, O_RDWR);

		int* array = new int [N];

		for(int i = 0; i < N; i ++)
		{
			array[i] = rand()%1000;
			std::cout << array[i] << " ";
		}

		std::cout << std::endl;

		write(file, array, N*sizeof(int));
		while(!read(fd[0], array, N*sizeof(int)));

		for(int i = 0; i < N; i ++) std::cout << array[i] << " ";
		std::cout << std::endl;
		close(file);
		unlink(FIFO);
		close(fd[0]);
		delete[] array;
	}
	else
	{
		int file = open(FIFO, O_RDWR);
		int* sort = new int [N];
		while(!read(file, sort, N*sizeof(int)));

		for(int i = 0; i < N; i ++)
		{
			for(int j = 0; j < N; j ++)
			{
				if(sort[j] < sort[j+1])
				{
					int a = sort[j];
					sort[j] = sort[j+1];
					sort[j+1] = a;
				}
			}
		}
		write(fd[1], sort, N*sizeof(int));

		close(file);
		close(fd[1]);
		delete[] sort;
	}
	return 0;
}
# LabOS
