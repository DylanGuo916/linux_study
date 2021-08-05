#include <pthread.h>
#include <stdio.h>
#include <string.h>

void* callback(void* arg) {
  printf("child thread id: %ld\n", pthread_self());
  return NULL;
}

int main() {
  pthread_t tid;

  int ret = pthread_create(&tid, NULL, callback, NULL);
  if (ret != 0)
    printf("error1: %s\n", strerror(ret));
  
  printf("main thread id: %ld\n", pthread_self());

  // 分离后，线程终止时，资源不再需要主线程回收，资源由操作系统自动回收，使主线程不必阻塞
  ret = pthread_detach(tid);
  if (ret != 0) 
    printf("error2: %s\n", strerror(ret));

  // 线程分离后，连接线程会发生什么？
  ret = pthread_join(tid, NULL);
  if (ret != 0)
    printf("error3: %s\n", strerror(ret));
  // 运行报错
  
  pthread_exit(NULL);
  return 0;
}