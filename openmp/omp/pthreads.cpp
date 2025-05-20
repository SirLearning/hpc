#include <stdio.h>
#include <pthread.h>
static void *threadfunc(void *){
 printf("Hello World.\n");
return NULL;
}

int main() {
  pthread_t ids[4];
  for(int ii = 0; ii < 4; ++ii){
     pthread_create(&ids[ii],NULL,threadfunc,NULL);
  }

  for(int ii = 0; ii < 4; ++ii){
    pthread_join(ids[ii],NULL);
  }
  return 0;
}


