/*****************************************************************
 * Description
 * Email huxiaoheigame@gmail.com
 * Created on 2024/01/22
 * Copyright (c) 2023 虎小黑
 ****************************************************************/

#include "graph.h"
#include <dlfcn.h>

typedef int (*pthread_mutex_lock_t)(pthread_mutex_t *mutex);
typedef int (*pthread_mutex_unlock_t)(pthread_mutex_t *mutex);

pthread_mutex_lock_t pthread_mutex_lock_f;
pthread_mutex_unlock_t pthread_mutex_unlock_f;

static Graph *tg = new Graph();
static std::list<uint64_t> path;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void init_hook()
{
    pthread_mutex_lock_f = (pthread_mutex_lock_t)dlsym(RTLD_NEXT, "pthread_mutex_lock");
    pthread_mutex_unlock_f = (pthread_mutex_unlock_t)dlsym(RTLD_NEXT, "pthread_mutex_unlock");
}

void lock_before(pthread_t thread_id, uint64_t lock_addr)
{
    pthread_mutex_lock_f(&mutex);
    for (auto v : tg->vertexs)
    {
        if (v.second->locks.contains(lock_addr))
        {
            tg->add_edge(thread_id, v.first);
        }
    }
    tg->search_for_cycle(path);
    pthread_mutex_unlock_f(&mutex);
}

void lock_after(pthread_t thread_id, uint64_t lock_addr)
{
    pthread_mutex_lock_f(&mutex);
    auto v = tg->get_vertex(thread_id);
    v->locks.insert(lock_addr);
    pthread_mutex_unlock_f(&mutex);
}

void unlock_after(uint64_t thread_id, uint64_t lock_addr)
{
    pthread_mutex_lock_f(&mutex);
    auto v = tg->get_vertex(thread_id);
    v->locks.erase(lock_addr);
    for (auto v : tg->vertexs)
    {
        if (v.second->wait_lock == lock_addr)
        {
            tg->remove_edge(thread_id, v.first);
            v.second->wait_lock = 0;
        }
    }
    pthread_mutex_unlock_f(&mutex);
}

int pthread_mutex_lock(pthread_mutex_t *mutex)
{
    pthread_t thread_id = pthread_self();
    lock_before(thread_id, (uint64_t)mutex);
    pthread_mutex_lock_f(mutex);
    lock_after(thread_id, (uint64_t)mutex);
    return 0;
}

int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    pthread_t thread_id = pthread_self();
    pthread_mutex_unlock_f(mutex);
    unlock_after(thread_id, (uint64_t)mutex);
    return 0;
}
