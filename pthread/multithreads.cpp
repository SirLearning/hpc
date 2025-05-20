#include <pthread.h>
#include <stdio.h>

int global_var = 123456;
void (*funptr)(int );

void threadcall(int index){
funptr = threadcall;
int local=9999;
printf("thread=%d\nlocal address=%p\nfunction address=%p\nglobal address=%p\n",index,&local,funptr,&global_var);fflush(stdout);
}

static void * threadfunc(void *arg){
int index = *((int*)(arg));
threadcall(index);
return NULL;
}

int main(){
pthread_t ids[4];
int thread_index[4]={0,1,2,3};

for(int ii = 0; ii < 4; ++ii){
pthread_create(&ids[ii],NULL,threadfunc,&thread_index[ii]);
}

for(int ii = 0; ii < 4; ++ii){
pthread_join(ids[ii],NULL);
}
return 0;
}
