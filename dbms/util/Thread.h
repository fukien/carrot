#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
class Thread
{
   public:
    /// Create a new thread
    static pthread_t start(void (*starter)(void*),void* arg,bool boost=false);
   /// Available physical memory
    static uint64_t guessPhysicalAvailable();
   /// Wait x ms
   static void sleep(unsigned time);
   /// Get the thread id
   static long threadID();
   /// Activate the next thread
   static void yield();
   /// Get the current time in milliseconds
   static uint64_t getTicks();
};
#endif // THREAD_H_INCLUDED
