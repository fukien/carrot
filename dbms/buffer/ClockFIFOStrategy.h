#ifndef CLOCKFIFOSTRATEGY_H_INCLUDED
#define CLOCKFIFOSTRATEGY_H_INCLUDED
#include "BufferManager.h"
 class ClockFIFOStrategy:public BufferStrategy
 {
    public:
        ClockFIFOStrategy();
        void initialize( std::queue<BufferFrame*>*& que,std::map<Addr,BufferFrame*>*& pageMap);
        ~ClockFIFOStrategy();
        void release(std::queue<BufferFrame*>*& que,std::map<Addr,BufferFrame*>*& pageMap);
        void whenRead(BufferFrame* frame);
        void whenWrite(BufferFrame* frame);
        void electPageToDrop(std::vector<Addr>& vec,int number);
        StrategyInBuffer getStrategy();
    private:
        std::set<Addr>* pageSet;
 };


#endif // CLOCKFIFOSTRATEGY_H_INCLUDED
