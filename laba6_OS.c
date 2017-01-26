#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <semaphore.h>

sem_t mutex;

//используются системные вызовы для работы с файлами

void* writing()
{
	time_t rawtime; 
	struct tm *timeinfo;
	int file;
	int num_str = 1;
	char str[100];

	while(1)
	{
		sem_wait(&mutex);
			
		time(&rawtime);
		timeinfo = localtime(&rawtime);

		//открываем/создаем файл в режиме добавления, только на запись
		file = open("time.txt", O_CREAT|O_WRONLY|O_APPEND, 0700);
		sprintf(str, "string #%d:\t%d:%d:%d\n", num_str,timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
		write(file, str, strlen(str));
		num_str++; 		
		
		sem_post(&mutex);
		sleep(1);
	}
	pthread_exit(0);
}

void* reading()
{
	int file;
	int str_read = 0;
	int str_write = 0;
	char str[100];
	while(1)
	{
		sem_wait(&mutex);
		
		//открываем/создаем файл только на чтение
		file = open("time.txt", O_CREAT|O_RDONLY, 0700);
		
		while ((str_read = read(file, str, 128)) > 0)
		{
		    str_write = write (1, str, str_read);
		}	
		printf("&&&&&&&&&&&&&&&&&&&&\n");
		
		sem_post(&mutex);
		sleep(5);
	}
	pthread_exit(0);  
}

int main (int argc, char* argv[])
{
	pthread_t writer;
	pthread_t readers [10];

	int i;
	
	sem_init(&mutex, 0 , 5);

	if(pthread_create(&writer, NULL, writing, NULL)<0)
	{	
		printf("ERROR: create writer thread false\n");
		return -1;
	}

	for (i = 0; i<10; ++i)
	{
		if(pthread_create(&readers[i], NULL, reading, NULL)<0)
		{	
			printf("ERROR: create reading thread %d false\n", i);
			return -1;
		}
	}
	
	if(pthread_join(writer, NULL)<0)
	{	
		printf("ERROR: joining writer thread false\n");
		return -1;
	}

	for (i = 0; i<10; ++i)
	{
		if(pthread_join(readers[i], NULL)<0)
		{	
			printf("ERROR: joining reading thread %d false\n", i);
			return -1;
		}
	}

	sem_destroy(&mutex);
	
	return 0;
}
