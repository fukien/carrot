#include "Thread.h"
//---------------------------------------------------------------------------
namespace std {}
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
pthread_t Thread::start(void (*starter)(void*),void* arg,bool boost)
   // Create a new thread
{
   // Avoid a warning, boost is not supported for Unix currently
   if (boost)
      arg=arg;

   // Initialize some attributes
   pthread_t tid=0;
   pthread_attr_t pattrs;
   pthread_attr_init(&pattrs);
   // Not required for Linux and valgrind does not like it
#ifndef __linux__
   pthread_attr_setscope(&pattrs,PTHREAD_SCOPE_SYSTEM);
#endif
   int result=pthread_create(&tid,NULL,reinterpret_cast<void*(*)(void*)>(starter),arg);
   pthread_attr_destroy(&pattrs);
   if (result!=0)
      return false;
   pthread_detach(tid);

   return true;
}
//---------------------------------------------------------------------------
uint64_t Thread::guessPhysicalAvailable()
   // Guess the physical available memory
{

   long long pageCount=sysconf(_SC_PHYS_PAGES);
   long long pageSize=sysconf(_SC_PAGESIZE);

   return (pageCount*pageSize)>>2; // Guess 25%
}
//----------------------------------------------------------------------Thread-----
void Thread::sleep(unsigned time)
   // Wait x ms
{
   if (!time) {
      sched_yield();
   } else {
      struct timespec a,b;
      a.tv_sec=time/1000; a.tv_nsec=(time%1000)*1000000;
      nanosleep(&a,&b);
   }
}
//---------------------------------------------------------------------------
long Thread::threadID()
   // Threadid
{
   union { pthread_t a; long b; } c;
   c.b=0;
   c.a=pthread_self();
   return c.b;
}
//---------------------------------------------------------------------------
void Thread::yield()
   // Activate other threads
{
   sched_yield();
}
//---------------------------------------------------------------------------
uint64_t Thread::getTicks()
   // Get the current time in ms
{

   timeval t;
   gettimeofday(&t,0);
   return static_cast<uint64_t>(t.tv_sec)*1000+(t.tv_usec/1000);
}
