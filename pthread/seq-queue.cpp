#include<iostream>
#include<vector>
#include<semaphore.h>
#include<cassert>
#include<pthread.h>
 
using namespace std;
const int gCapcity = 10;
template<class T>
class RingQueue
{
public:
    RingQueue(const int& capcity = gCapcity)
    :_queue(capcity),_capacity(capcity)
    {
        sem_init(&_PSem,0,_capacity);
        sem_init(&_CSem,0,0);
        pthread_mutex_init(&_Pmutex,nullptr);
        pthread_mutex_init(&_Cmutex,nullptr);
        _PIndex = _CIndex = 0;
    }
    void Push(const T& in)
    {
        int n = sem_wait(&_PSem);
        assert(n == 0);
        pthread_mutex_lock(&_Pmutex);
        _queue[_PIndex++] = in;
        _PIndex %= _capacity;
        pthread_mutex_unlock(&_Pmutex);
        //3._CSem++
        sem_post(&_CSem);
    }
    void Pop(T* out)
    {
        int n = sem_wait(&_CSem);
        assert(n == 0);
        pthread_mutex_lock(&_Cmutex);
        *out = _queue[_CIndex++];
        _CIndex %= _capacity;
        pthread_mutex_unlock(&_Cmutex);
        //3._PSem++;
        sem_post(&_PSem);
    }
    ~RingQueue()
    {
        sem_destroy(&_PSem);
        sem_destroy(&_CSem);
        pthread_mutex_destroy(&_Pmutex);
        pthread_mutex_destroy(&_Cmutex);
    }
private:
    vector<T> _queue;
    int _capacity;
    sem_t _PSem;
    sem_t _CSem;
    int _PIndex;
    int _CIndex;
    pthread_mutex_t _Pmutex;
    pthread_mutex_t _Cmutex;
};


#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
 
void* ProductorRoutine(void* args)
{
    RingQueue<int>* rq = static_cast<RingQueue<int>*>(args);
    while(true)
    {
        int data;
        data = rand() % 10;
        rq->Push(data);
        cout << "producer " << data << endl;
        sleep(1);
    }
    return nullptr;
}
void* ConsumerRoutine(void* args)
{
    RingQueue<int>* rq = static_cast<RingQueue<int>*>(args);
    while(true)
    {
        int data;
        rq->Pop(&data);
        cout << "consumer"  << data << endl;
    }
    return nullptr;
}
int main()
{
    srand((unsigned int)time(nullptr));
    pthread_t tidP,tidC;
    RingQueue<int> * rq = new RingQueue<int>();
    pthread_create(&tidP,nullptr,ProductorRoutine,rq);
    pthread_create(&tidC,nullptr,ConsumerRoutine,rq);
    pthread_join(tidP,nullptr);
    pthread_join(tidC,nullptr);
    return 0;
}
