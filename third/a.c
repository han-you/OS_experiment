#include <pthread.h>


void *a(void * c)
{
	return NULL;
}
int main()
{
	pthread_t id;
	pthread_create(&id,NULL,a,NULL);
	return 0;
}
