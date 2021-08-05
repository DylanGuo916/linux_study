// 多个线程读写临界资源出现问题
#include <stdio.h>
#include <pthread.h>

int ticket_num = 100;

void* sell_ticket(void* arg) {
  while (ticket_num > 0) {
    printf("%ld 正在卖第 %d 张门票\n", (long)pthread_self(), ticket_num);
    ticket_num--;
  }
  return NULL;
}

int main() {

  pthread_t tid1, tid2, tid3;
  
  pthread_create(&tid1, NULL, sell_ticket, NULL);
  pthread_create(&tid2, NULL, sell_ticket, NULL);
  pthread_create(&tid3, NULL, sell_ticket, NULL);

  // 回收子线程的资源，阻塞
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);

  // 设置线程分离
  // pthread_detach(tid1);
  // pthread_detach(tid2);
  // pthread_detach(tid3);

  pthread_exit(NULL);
  return 0;
}