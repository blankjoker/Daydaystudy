
#ifndef ME_THREAD__
#define ME_THREAD__

#include <pthread.h>

struct me_thread;

typedef void *(*me_thread_main_function)(struct me_thread *thread, void *arg);

typedef struct me_thread {

    pthread_t thread;
    pid_t tid;
    char *name;
    void *arg;
    int quit_flag;
    pthread_attr_t attr;
    pthread_mutex_t lock;
    pthread_cond_t cond;
    pthread_condattr_t condattr;
    me_thread_main_function main_fun;
}me_thread_t;

typedef struct me_sync {

    pthread_mutex_t mutex;
    pthread_mutexattr_t attr;
}me_sync_t;

namespace nutshell {
    class Me_Thread;
}

class Me_Thread
{
private:
    /* data */
    // me_thread_t *thread;
    static Me_Thread *m_instance;

public:
    Me_Thread();
    virtual ~Me_Thread();

    /***************************thread function*****************************************/
    Me_Thread(const Me_Thread& other);
    Me_Thread& operator=(const Me_Thread& other);

    me_thread_t *me_thread_create(me_thread_main_function main_fun, void *arg, const char *name);
    void me_thread_release(me_thread_t *thread);
    const char *me_thread_get_name(me_thread_t *thread);
    int nme_thread_get_id(me_thread_t *thread);
    int me_thread_wait(me_thread_t *thread);
    int me_thread_wait_timeout(me_thread_t *thread, int timeout_ms);
    int me_thread_notify(me_thread_t *thread);
    int me_thread_join(me_thread_t *thread);
    int me_thread_terminate(me_thread_t *thread);
    int me_thread_stop(me_thread_t *thread);
    int me_thread_checkquit(me_thread_t *thread);

    /***************************thread sync mutex function******************************/
    me_sync_t *me_sync_create();
    void me_sync_start(me_sync_t *sync);
    void me_sync_end(me_sync_t *sync);
    int me_sync_start_try(me_sync_t *sync);
    void me_sync_destroy(me_sync_t *sync);

    void thread_test();

    static Me_Thread* instance();

};

#endif // ME_THREAD__
/* EOF */