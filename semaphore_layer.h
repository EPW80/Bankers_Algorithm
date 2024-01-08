#include <semaphore.h>

//---------------------------- DO NOT TOUCH THIS CODE (lines 7 to 52) -------
// ABSTRACTION LAYER for differences in semaphores between Linux and macOS
//---------------------------- DO NOT TOUCH THIS CODE (lines 7 to 52) -------
#if defined __APPLE__
#include <dispatch/dispatch.h> // macOS ONLY
#endif

#if defined __APPLE__
#define semaphore_t dispatch_semaphore_t
#else
#define semaphore_t sem_t
#endif

semaphore_t semaphore_create(semaphore_t *semaphore, unsigned int level);
void semaphore_wait(semaphore_t *semaphore);
void semaphore_signal(semaphore_t *semaphore);
void semaphore_destroy(semaphore_t *semaphore);