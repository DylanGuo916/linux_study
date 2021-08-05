#include <pthread.h>
#include <stdio.h>

// 全局变量，所有线程共享资源
int ticket_num = 100;

// 创建一个互斥锁
pthread_mutex_t mutex;

void *sell_ticket(void *arg) {

  // 买票
  while (1) {
    // 加锁
    pthread_mutex_lock(&mutex);

    // 进入临界区
    if (ticket_num > 0) {
      printf("%ld 正在卖第 %d 张门票\n", (long)pthread_self(), ticket_num);
      ticket_num--;
    } else {
      pthread_mutex_unlock(&mutex); // 容易忽略这个出口，忘记释放锁，所以推荐用RAII去封装锁对象！！
      break;
    }

    // 解锁
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main() {

  // 初始化互斥量
  pthread_mutex_init(&mutex, NULL);

  // 创建3个子线程
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

  // 释放互斥量资源
  pthread_mutex_destroy(&mutex);
  return 0;
}