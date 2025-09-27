//Original Code

#include <stdio.h>

#include "mythreads.h"

int balance = 0;

void* worker(void* arg) {
    balance++; // unprotected access 
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    balance++; // unprotected access
    Pthread_join(p, NULL);
    return 0;
}

// Removing one of code
// #include <stdio.h>
// #include <pthread.h>
// #include "mythreads.h"

// int balance = 0;

// void* worker(void* arg) {
//     balance++; // ONLY thread 2 (worker) performs the write
//     return NULL;
// }

// int main(int argc, char *argv[]) {
//     pthread_t p;
//     Pthread_create(&p, NULL, worker, NULL);
//     // REMOVED: balance++; 
//     Pthread_join(p, NULL);
//     return 0;
// }

// Adding one lock to the code
// #include <stdio.h>
// #include <pthread.h>
// #include "mythreads.h"

// int balance = 0;
// pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // Mutex for synchronization

// void* worker(void* arg) {
//     pthread_mutex_lock(&lock); // Lock added here
//     balance++; 
//     pthread_mutex_unlock(&lock); // Lock released here
//     return NULL;
// }

// int main(int argc, char *argv[]) {
//     pthread_t p;
//     Pthread_create(&p, NULL, worker, NULL);
    
//     // Unprotected access remains here, conflicting with the protected access above
//     balance++; // STILL Unprotected access
    
//     Pthread_join(p, NULL);
//     return 0;
// }

//Adding two locks to the code
// #include <stdio.h>
// #include <pthread.h>
// #include "mythreads.h"

// int balance = 0;
// pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // Mutex for synchronization

// void* worker(void* arg) {
//     pthread_mutex_lock(&lock); // Acquire lock
//     balance++; 
//     pthread_mutex_unlock(&lock); // Release lock
//     return NULL;
// }

// int main(int argc, char *argv[]) {
//     pthread_t p;
//     Pthread_create(&p, NULL, worker, NULL);
    
//     pthread_mutex_lock(&lock); // Acquire lock
//     balance++; // Protected access
//     pthread_mutex_unlock(&lock); // Release lock

//     Pthread_join(p, NULL);
//     return 0;
// }