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
		time = clock();
		printf("Это родительский процесс:\n");
		printf(" pid родителя: %d\n fork родителя: %d\n",getpid(), pid);
		time = clock() - time;
		printf(" Время работы родителя: %f\n\n", (double)time/CLOCKS_PER_SEC);	
	}
	else if (pid == 0)
	{
		time = clock();
		printf("Это дочерний процесс:\n");
		printf(" pid ребенка: %d\n pid родителя: %d\n fork ребенка: %d\n",getpid(), getppid(), pid);
		time = clock() - time;
		printf(" Время работы ребенка: %f\n\n", (double)time/CLOCKS_PER_SEC);
	}
	
	return 0;
}
