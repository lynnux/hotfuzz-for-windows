// https://github.com/robinrowe/libunistd/blob/master/unistd/pthread.cpp
#include "pthread.h"
#include <system_error>
#include <thread>
struct PortableThread : public std::thread {
    void *ret;

   public:
    PortableThread(const void *attr, PTHREAD_START_ROUTINE1 start_routine,
                   void *arg)
        : std::thread([this, start_routine](
                          void *arg) { this->ret = start_routine(arg); },
                      arg) {}
};
extern "C" {
int pthread_create(pthread_t *pthread, void *attr,
                   PTHREAD_START_ROUTINE1 start_routine, void *arg) {
    PortableThread *t = 0;
    try {
        t = new PortableThread(attr, start_routine, arg);
    } catch (const std::system_error &e) {
        // printf("Caught system_error %s\n", e.what());
        return -1;
    }
    *pthread = t;
    return 0;
}

int pthread_join(pthread_t thread, void **retval) {
    if (!thread) {
        return -1;
    }

    try {
        thread->join();
        *retval = thread->ret;
    } catch (const std::system_error &e) {
        delete thread;
        // printf("Caught system_error %s\n", e.what());
        return -1;
    }
    delete thread;
    return 0;
}
}
