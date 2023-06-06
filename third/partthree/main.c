#include<iostream>
#include<unistd.h>`
using namespace std;
#include<pthread.h>
#include<semaphore.h>
sem_t provide;
sem_t smoke;
pthread_mutex_t mutex;
int tobacco=0;
int paper=0;
int match=0;
typedef struct smoker
{
	int id;
}smoker;
void* smoker1(void*p)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(paper==1&&match==1)
		{
		//	pthread_mutex_lock(&mutex);
			printf("Smoker 0 gets paper and match ans starts smoking\n");
			paper--;
			match--;
			sem_post(&provide);
			sleep(1);
		//	pthread_mutex_unlock(&mutex);
		}
		pthread_mutex_unlock(&mutex);
	}
}
void*smoker2(void *p)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(tobacco==1&&match==1)
		{
		//	pthread_mutex_lock(&mutex);
			printf("Smoker 1 gets tobacco and match and starts smoking\n");
			tobacco--;
			match--;
			sem_post(&provide);
			sleep(1);
	//		pthread_mutex_unlock(&mutex);
		}
		pthread_mutex_unlock(&mutex);
	}
}
void*smoker3(void *p)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(tobacco==1&&paper==1)
		{
			//pthread_mutex_lock(&mutex);
			printf("Smoker 2 gets tobacco and paper and starts smoking\n");
			tobacco--;
			paper--;
			sem_post(&provide);
			sleep(1);
		//	pthread_mutex_unlock(&mutex);
		}
		pthread_mutex_unlock(&mutex);
	}
}

void*provider(void*p)
{
	while(1)
	{
		sem_wait(&provide);
		pthread_mutex_lock(&mutex);
		srand((unsigned)time(NULL));
		int pos=rand()%3;
		if(pos==0)
		{
			tobacco++;
			paper++;
			printf("Provider provides tobacco and paper\n");
		}
		else if(pos==1)
		{
			tobacco++;
			match++;
			printf("Provider provides tobacco and match\n");
		}
		else
		{
			paper++;
			match++;
			printf("Provider provides paper and match\n");
		}
		pthread_mutex_unlock(&mutex);
	}
	
}
int main()
{
	sem_init(&provide,0,1);
	pthread_mutex_init(&mutex,NULL);
	smoker smokers[3];
	pthread_t ids[4];
	pthread_create(&ids[0],NULL,smoker1,NULL);
	pthread_create(&ids[1],NULL,smoker2,NULL);
	pthread_create(&ids[2],NULL,smoker3,NULL);
	pthread_create(&ids[3],NULL,provider,NULL);
	pthread_join(ids[0],NULL);
	pthread_join(ids[1],NULL);
	pthread_join(ids[2],NULL);
	pthread_join(ids[3],NULL);
	return 0;
}

