#include<iostream>
using namespace std;
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
pthread_mutex_t mutex;
sem_t empty,full;
int buff[10];
int buff_count=0;
void consumer()
{
	for(int i=0;i<10;i++)
	{
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		buff[buff_count]=0;
		buff_count--;
		cout<<"[consumer thread] buffer count "<<buff_count<<endl;
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
		sleep(3);
	}
	return;
}
void producer()
{
	for(int i=0;i<10;i++)
	{
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		buff[buff_count]=1;
		buff_count++;
		cout<<"[producer thread] buffer count "<<buff_count<<endl;
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
		sleep(2);
	}
	return;
}
int main(){
	pthread_t id1,id2;
	pthread_mutex_init(&mutex,NULL);
	sem_init(&empty,0,10);
	sem_init(&full,0,0);
	pthread_create(&id1,NULL,(void*(*)(void*))&consumer,NULL);
	pthread_create(&id2,NULL,(void*(*)(void*))&producer,NULL);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
	return 0;
}
