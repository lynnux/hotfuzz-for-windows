#ifndef PTHREAD_H
#define PTHREAD_H
#include <Windows.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct PortableThread PortableThread;
typedef PortableThread *pthread_t;

typedef long pthread_mutex_t;

static int pthread_mutex_init(pthread_mutex_t *m, void *) {
  *m = 0;
  return 0;
}
static int pthread_mutex_lock(pthread_mutex_t *m) {
  while (InterlockedCompareExchange(m, 1, 0) != 0)
    Sleep(0);
  return 0;
}
static void pthread_mutex_unlock(pthread_mutex_t *m) {
  InterlockedExchange(m, 0);
}
static int pthread_mutex_destroy(pthread_mutex_t *m) { return 0; }

typedef void *(__cdecl *PTHREAD_START_ROUTINE1)(void *);
int pthread_create(pthread_t *thread, void *,
                   PTHREAD_START_ROUTINE1 start_routine, void *arg);
int pthread_join(pthread_t thread, void **retval);

#define _SC_NPROCESSORS_ONLN
static unsigned int sysconf() {
  SYSTEM_INFO info;
  GetSystemInfo(&info);
  return info.dwNumberOfProcessors;
}

#ifdef __cplusplus
}
#endif

#endif /* PTHREAD_H */
