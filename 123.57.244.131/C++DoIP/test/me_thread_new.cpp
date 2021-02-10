
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "me_thread.h"
using namespace std;

/***************************thread function*****************************************/

static void *me_thread_main(void *arg);

Me_Thread::Me_Thread()
{
    cout << "pthread function is successful" << endl;
}

Me_Thread::~Me_Thread()
{
    cout << "pthread function is destory" << endl;
}

Me_Thread* Me_Thread::m_instance = NULL;
Me_Thread* Me_Thread::instance()
{
    if (m_instance == NULL) {
        m_instance = new Me_Thread();
    }
    return m_instance;
}

me_thread_t* Me_Thread::me_thread_create(me_thread_main_function main_fun, void *arg, const char *name)
{
    int ret = -1;

    if (main_fun == NULL || name == NULL) {
        return NULL;
    }

    me_thread_t *thread;
    // thread = (me_thread_t *)malloc(sizeof *thread);
    thread = new me_thread_t;

    thread->quit_flag = 0;
    thread->arg = arg;
    thread->main_fun = main_fun;
    thread->thread = -1;
    thread->tid = -1;
    int str_size = strlen(name) + 1;
    // thread->name = (char *)malloc(str_size);
    thread->name = new char[str_size]; 
    // memset(thread->name, 0, str_size);
    memcpy(thread->name, name, strlen(name));

    ret = pthread_condattr_init(&thread->condattr);
    if (ret != 0) {
        delete []thread->name;
        delete thread;
        return NULL;
    }

    ret = pthread_condattr_setclock(&thread->condattr, CLOCK_MONOTONIC);
    if (ret != 0) {
        delete []thread->name;
        delete thread;
        return NULL;
    }


    ret = pthread_cond_init(&thread->cond, &thread->condattr);
    if (ret != 0) {
        delete []thread->name;
        delete thread;
        return NULL;
    }

    ret = pthread_mutex_init(&thread->lock, NULL);
    if (ret != 0) {
        delete []thread->name;
        delete thread;
        return NULL;
    }

    ret = pthread_attr_init(&thread->attr);
    if (0 != ret) {
        delete []thread->name;
        delete thread;
        return NULL;
    }

    ret = pthread_attr_setscope(&thread->attr, PTHREAD_SCOPE_SYSTEM);
    if (0 != ret) {
        delete []thread->name;
        delete thread;
        return NULL;
    }

    ret = pthread_create(&thread->thread, &thread->attr, me_thread_main, thread);
    if (ret != 0) {
        delete []thread->name;
        delete thread;
        return NULL;
    }

    return thread;
}

void Me_Thread::me_thread_release(me_thread_t *thread)
{
    pthread_cond_destroy(&thread->cond);
    pthread_mutex_destroy(&thread->lock);
    pthread_condattr_destroy(&thread->condattr);
    pthread_attr_destroy(&thread->attr);

    delete []thread->name;
    delete thread;
}

const char* Me_Thread::me_thread_get_name(me_thread_t *thread)
{
    return thread->name;
}

int Me_Thread::nme_thread_get_id(me_thread_t *thread)
{
    return thread->tid;
}

int Me_Thread::me_thread_wait(me_thread_t *thread)
{
    return pthread_cond_wait(&thread->cond, &thread->lock);
}

int Me_Thread::me_thread_wait_timeout(me_thread_t *thread, int timeout_ms)
{
    struct timespec *nptime;
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);

    nptime->tv_sec = now.tv_sec + timeout_ms / 1000;
    nptime->tv_nsec = now.tv_nsec + (timeout_ms % 1000) * 1000000;

    // bigger than one second
    if (nptime->tv_nsec >= 1000000000) {
        nptime->tv_sec++;
        nptime->tv_nsec -= 1000000000;
    }
 
    return pthread_cond_timedwait(&thread->cond, &thread->lock, nptime);
}

int Me_Thread::me_thread_notify(me_thread_t *thread)
{
    return pthread_cond_signal(&thread->cond);
}

int Me_Thread::me_thread_join(me_thread_t *thread)
{
    return pthread_join(thread->thread, NULL);
}

int Me_Thread::me_thread_terminate(me_thread_t *thread)
{
    int ret;

    thread->quit_flag = 1;

    ret = pthread_cancel(thread->thread);

    if (ret == 0) {
        ret = me_thread_join(thread);
    }

    me_thread_release(thread);

    return ret;
}

int Me_Thread::me_thread_stop(me_thread_t *thread)
{
    int ret;

    thread->quit_flag = 1;

    ret = me_thread_notify(thread);

    if (ret == 0) {
        ret = me_thread_join(thread);
    }

    me_thread_release(thread);

    return ret;
}

int Me_Thread::me_thread_checkquit(me_thread_t *thread)
{
    return thread->quit_flag;
}

static void *me_thread_main(void *arg)
{
    void *ret;
    me_thread_t *thread = (me_thread_t *)arg;

    thread->tid = getpid();

    ret = thread->main_fun(thread, thread->arg);

    return ret;
}

/***************************thread sync mutex function******************************/
me_sync_t* Me_Thread::me_sync_create()
{
    // me_sync_t *sync = (me_sync_t *)malloc(sizeof *sync);
    me_sync_t *sync = new me_sync_t;
    if (!sync) {
        return NULL;
    }

    pthread_mutexattr_init(&sync->attr);
    pthread_mutexattr_settype(&sync->attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&sync->mutex, &sync->attr);

    return sync;
}

void Me_Thread::me_sync_start(me_sync_t *sync)
{
    pthread_mutex_lock(&sync->mutex);
}

void Me_Thread::me_sync_end(me_sync_t *sync)
{
    pthread_mutex_unlock(&sync->mutex);
}

int Me_Thread::me_sync_start_try(me_sync_t *sync)
{
    return pthread_mutex_trylock(&sync->mutex);
}

void Me_Thread::me_sync_destroy(me_sync_t *sync)
{
    if (!sync) {
        return;
    }

    pthread_mutexattr_destroy(&sync->attr);
    pthread_mutex_destroy(&sync->mutex);

    delete sync;
}

void Me_Thread::thread_test()
{
    cout << "hi pthread ,are you OK" << endl;
}
/****************************************main function***************************************/
int main()
{
    Me_Thread::instance()->thread_test();
    return 0;
}