#include <pthread.h>
#include <stdio.h>
static long long int sum=0;
pthread_mutex_t sum_mutex;

static void * threadfunc(void *arg){

for(int ii = 0;ii<100000; ++ii){
pthread_mutex_lock(&sum_mutex);
++sum;
pthread_mutex_unlock(&sum_mutex);
}
return NULL;
}

int main(){
pthread_t ids[4];

pthread_mutex_init(&sum_mutex,NULL);

for(int ii = 0; ii< 4; ++ii){
pthread_create(&ids[ii],NULL,threadfunc,NULL);
}

for(int ii = 0; ii < 4; ++ii){
pthread_join(ids[ii],NULL);
}

printf("sum=%ld\n",sum);fflush(stdout);
return 0;

}
