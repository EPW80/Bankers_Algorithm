#include "semaphore_layer.h"
// #include <stdio.h>
// #include <pthread.h>
// #include <semaphore.h>
// #include <stdlib.h>
// #include <unistd.h>

//---------------------------- DO NOT TOUCH THIS CODE (lines 7 to 52) -------
// ABSTRACTION LAYER for differences in semaphores between Linux and macOS
//---------------------------- DO NOT TOUCH THIS CODE (lines 7 to 52) -------
semaphore_t semaphore_create(semaphore_t *semaphore, unsigned int level) {
#if defined __APPLE__
   return dispatch_semaphore_create((long long)(level));
#else
   sem_init(semaphore, 0, level);
   return *semaphore;
#endif
}

void semaphore_wait(semaphore_t *semaphore) {
#if defined __APPLE__
   dispatch_semaphore_wait(*semaphore, DISPATCH_TIME_FOREVER);
#else
   sem_wait(semaphore);
#endif
}

void semaphore_signal(semaphore_t *semaphore) {
#if defined __APPLE__
   dispatch_semaphore_signal(*semaphore);
#else
   sem_post(semaphore);
#endif
}

void semaphore_destroy(semaphore_t *semaphore) {
#if defined __APPLE__
   dispatch_release(*semaphore);
#else
   sem_destroy(semaphore);
#endif
}
