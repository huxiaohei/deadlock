/*****************************************************************
 * Description
 * Email huxiaoheigame@gmail.com
 * Created on 2024/01/23
 * Copyright (c) 2023 虎小黑
 ****************************************************************/

#include "deadlock.h"
#include <thread>

pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_4 = PTHREAD_MUTEX_INITIALIZER;

void *thread_rountine_1(void *args)
{
    pthread_t thread_id = pthread_self();

    std::cout << thread_id << " lock " << &mutex_1 << std::endl;
    pthread_mutex_lock(&mutex_1);
    sleep(1);
    std::cout << thread_id << " lock " << &mutex_1 << std::endl;
    pthread_mutex_lock(&mutex_2);

    pthread_mutex_unlock(&mutex_2);
    std::cout << thread_id << " unlock " << &mutex_2 << std::endl;

    pthread_mutex_unlock(&mutex_1);
    std::cout << thread_id << " unlock " << &mutex_1 << std::endl;

    return (void *)(0);
}

void *thread_rountine_2(void *args)
{
    pthread_t thread_id = pthread_self();

    std::cout << thread_id << " lock " << &mutex_2 << std::endl;
    pthread_mutex_lock(&mutex_2);
    sleep(1);
    std::cout << thread_id << " lock " << &mutex_3 << std::endl;
    pthread_mutex_lock(&mutex_3);

    pthread_mutex_unlock(&mutex_3);
    std::cout << thread_id << " unlock " << &mutex_3 << std::endl;

    pthread_mutex_unlock(&mutex_2);
    std::cout << thread_id << " unlock " << &mutex_2 << std::endl;

    return (void *)(0);
}

void *thread_rountine_3(void *args)
{
    pthread_t thread_id = pthread_self();

    std::cout << thread_id << " lock " << &mutex_3 << std::endl;
    pthread_mutex_lock(&mutex_3);
    sleep(1);
    std::cout << thread_id << " lock " << &mutex_4 << std::endl;
    pthread_mutex_lock(&mutex_4);

    pthread_mutex_unlock(&mutex_4);
    std::cout << thread_id << " unlock " << &mutex_4 << std::endl;

    pthread_mutex_unlock(&mutex_3);
    std::cout << thread_id << " unlock " << &mutex_3 << std::endl;

    return (void *)(0);
}

void *thread_rountine_4(void *args)
{
    pthread_t thread_id = pthread_self();

    std::cout << thread_id << " lock " << &mutex_4 << std::endl;
    pthread_mutex_lock(&mutex_4);
    sleep(1);
    std::cout << thread_id << " lock " << &mutex_1 << std::endl;
    pthread_mutex_lock(&mutex_1);

    pthread_mutex_unlock(&mutex_1);
    std::cout << thread_id << " unlock " << &mutex_1 << std::endl;

    pthread_mutex_unlock(&mutex_4);
    std::cout << thread_id << " unlock " << &mutex_4 << std::endl;

    return (void *)(0);
}

int main()
{

    init_hook();

    std::cout << "start" << std::endl;
    pthread_t tid1, tid2, tid3, tid4;

    pthread_create(&tid1, NULL, thread_rountine_1, NULL);
    pthread_create(&tid2, NULL, thread_rountine_2, NULL);
    pthread_create(&tid3, NULL, thread_rountine_3, NULL);
    pthread_create(&tid4, NULL, thread_rountine_4, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);

    return 0;
}
