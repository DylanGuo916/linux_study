/*
  #include <pthread.h>
  void pthread_exit(void *retval);
    功能：终止一个线程，在哪个线程中调用，就表示终止哪个线程
    参数：
    retval:需要传递一个指针，作为一个返回值，可以在pthread_join()中获取到。
    
  pthread_t pthread_self(void);
    功能：获取当前的线程的线程ID

  int pthread_equal(pthread_t t1, pthread_t t2);
    功能：比较两个线程ID是否相等
    不同的操作系统，pthread_t类型的实现不一样，有的是无符号的长整型，有的
    是使用结构体去实现的。
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void* callback(void* arg) {
  printf("child thread starts, thread id: %ld\n", pthread_self());
  printf("child thread exit\n");
  return NULL;
} 
int main() {
  
  printf("main thread start, thread id: %ld\n", pthread_self());

  pthread_t tid;
  pthread_create(&tid, NULL, callback, NULL);

  printf("main thread sleep for 5s\n");
  sleep(5);

  printf("main thread start running\n");
  for (int i = 0; i < 5; ++i)
    printf("%d\n", i);
  
  printf("main thread exit\n");
  pthread_exit(NULL);
  return 0;
}