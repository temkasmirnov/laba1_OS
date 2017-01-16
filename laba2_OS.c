#include <time.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char* argv[])
{
	pid_t pid;
	clock_t time;
	pid = fork();
	if (pid >0)
	{
		//1 lab - parent
		time = clock();
		printf("Это родительский процесс:\n");
		printf(" pid родителя: %d\n fork родителя: %d\n",getpid(), pid);
		time = clock() - time;
		printf(" Время работы родителя: %f\n", (double)time/CLOCKS_PER_SEC);	

		//2 lab - parent
		FILE * file;
		file = fopen ("parent.txt", "wt");
		if (file == 0) 
		{
			printf("Ошибка в создании файла!\n");
		}
		else 
		{
			printf("Родительский файл создан!\n");
		}

		fprintf(file, "Это родитель, привет!\n");
		fclose(file);

	}
	
	
	else if (pid == 0)
	{
		//1 lab - child
		time = clock();
		printf("Это дочерний процесс:\n");
		printf(" pid ребенка: %d\n pid родителя: %d\n fork ребенка: %d\n",getpid(), getppid(), pid);
		time = clock() - time;
		printf(" Время работы ребенка: %f\n\n", (double)time/CLOCKS_PER_SEC);

		//2 lab - child
		FILE * file;
		file = fopen ("child.txt", "wt");
		if (file == 0) 
		{
			printf("Ошибка в создании файла!\n");
		}
		else 
		{
			printf("Дочерний файл создан!\n");
		}

		fprintf(file, "Это ребенок, привет!");
		fclose(file);
	}
	
	return 0;
}
