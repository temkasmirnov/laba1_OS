#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

int main (int argc, char* argv[])
{
	pid_t pid;
	unsigned int start_t = clock();
	pid = fork();
	if(pid >0)
	{
		unsigned int end_t1 = clock();
		unsigned int search_t1 = end_t1 - start_t;
		printf("Родитель:\n его pid = %d и время работы fork() равно %d\n",getpid(),search_t1);
	}
	
	return 0;
}
