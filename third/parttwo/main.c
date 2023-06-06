using namespace std;
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<iostream>
typedef struct philosopher
{
	int val; 
}philosopher;
sem_t forks[5];
void* haveDinner(void *p)
{
	philosopher*person=(philosopher*)p;
	while(1)
	{
		if(person->val==4)
		{
		        sem_wait(&forks[(person->val+1)%5]); 
			sem_wait(&forks[person->val]);
		}
		else
		{
	 		sem_wait(&forks[person->val]);
			sem_wait(&forks[(person->val+1)%5]); 
		}
		printf("philosopher %d gets forks %d and forks %d and is having dinner\n",person->val,person->val,(person->val+1)%5);
        printf("philosopher %d finishes eating\n",person->val);
		sem_post(&forks[person->val]);
		sem_post(&forks[(person->val+1)%5]);
		sleep(3);
	}
}


int main()
{
	for(int i=0;i<5;i++) sem_init(&forks[i],0,1);
	pthread_t ids[5];
	philosopher person[5];
	for(int i=0;i<5;i++)
	{
		person[i].val=i;
	}
	for(int i=0;i<5;i++)
	{
		pthread_create(&ids[i],NULL,(void*(*)(void*))haveDinner,&person[i]);
	}
	for(int i=0;i<5;i++)
	{
		pthread_join(ids[i],NULL);
	}
	return 0;
}

