#include <stdio.h>
#include <pthread.h>

void* fun1()
{

	while(1){
	
		printf("fun1\n");
		sleep(1);	

	}
}
void* fun2()
{

	while(1){
	
		printf("fun2\n");
		sleep(1);	

	}
}

int main()
{


	pthread_t th1;
	pthread_t th2;
	pthread_create(&th1,NULL,fun1,NULL);
	pthread_create(&th2,NULL,fun2,NULL);

	while(1);
	return 0;
	
}
