#ifndef PTHREAD_H
#define PTHREAD_H
#include <Windows.h>
#include <functional>

typedef HANDLE pthread_t;

struct pthread_mutex_t {
  long locker_;
  pthread_mutex_t() : locker_(0) {}
  void lock() {
    while (InterlockedCompareExchange(&locker_, 1, 0) != 0)
      Sleep(0);
  }
  void unlock() { InterlockedExchange(&locker_, 0); }
};

int pthread_mutex_init(pthread_mutex_t *, void *) { return 0; }
int pthread_mutex_lock(pthread_mutex_t *m) { m->lock(); }
void pthread_mutex_unlock(pthread_mutex_t *m) { m->unlock(); }
int pthread_mutex_destroy(pthread_mutex_t *m) { return 0; }

int pthread_create(pthread_t *thread, void *, LPTHREAD_START_ROUTINE start_rtn,
                   void *arg) {
  *thread = CreateThread(NULL, 0, start_rtn, arg, 0, 0);
  return 0;
}
int pthread_join(pthread_t thread, void **retval) {
  WaitForSingleObject(thread, INFINITE);
  if(retval){
      DWORD code;
      GetExitCodeThread(thread, &code);
      *retval = 0;
      *((DWORD*)retval) = code;
  }
  CloseHandle(thread);
  return 0;
}

unsigned int get_CPU_core_num() {
  SYSTEM_INFO info;
  GetSystemInfo(&info);
  return info.dwNumberOfProcessors;
}

#endif /* PTHREAD_H */
