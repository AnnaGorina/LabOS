#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <clocale>

int main(int argv, char* argc[])
{
	setlocale(LC_ALL, "Russian");

	if(argv < 3)
	{
		printf("Не хватает параметров\n");
		return -1;
	}

	FILE *file = fopen(argc[1], "r");
	
	if(file == 0)
	{
		printf("Ошибка открытия файла\n");
		return -2;
	}

	int byte = atoi(argc[2]);	
	unsigned char *data = new unsigned char [byte];

	int res = fread(data, sizeof(unsigned char), byte, file);

	if(res != byte)
	{
		printf("Ошибка чтения файла\n");
		return -3;
	}

	for(int i = 0; i < res; i++) printf("Символ[%i] = %c (0x%x)\n", i, data[i], data[i]);
	
	printf("Количество прочитанных символов: [%i]\n", res);
	fclose(file);
	return 0;
}
