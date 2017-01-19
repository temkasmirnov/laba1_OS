#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;

struct fibon
{
	long double first;
	long double second;
};

//функция подсчёта чисел Фибоначчи
void* fibonachi (void* arg)
{
	struct fibon new_num;
	new_num.first = 0;
	new_num.second = 1;
		
	long double new = 0; 
	int i = 0;
	pthread_mutex_lock(&mutex);
	for (i; i<99; i++)
	{
		new = new_num.first + new_num.second;
		printf("%.Lf ", new_num.first);
		new_num.first = new_num.second;
		new_num.second = new;
	}
	printf("\n -----------------------------------------------\n");
	pthread_mutex_unlock(&mutex);	
	pthread_exit(0);
}

int main (int argc, char* argv[])
{
	pthread_t threads [10];

	int i = 0;
	printf("\n");
	for (i; i<10; ++i)
	{
		if(pthread_create(&threads[i], NULL, fibonachi, &i)<0)
		{	
			printf("ERROR: create thread %d false\n", i);
			return -1;
		}
	}

	for (i = 0; i<10; ++i)
	{
		if (pthread_join(threads[i], NULL)<0)
		{
			printf("ERROR: joining thread %d false\n",i);
			return -1;
		}
	}
	return 0;
}
