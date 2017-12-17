 #include "ClockFIFOStrategy.h"
 #ifdef DEBUG
 #include <cstdlib>
 #include <cstdio>
#endif
void ClockFIFOStrategy::initialize( std::queue<BufferFrame*>*& ques,std::map<Addr,BufferFrame*>*& pageMaps)
{
    ques = new std::queue<BufferFrame*>();
    pageMaps = new std::map<Addr,BufferFrame*>();
    this->que = ques;
    this->pageMap = pageMaps;
    this->pageSet = new std::set<Addr>();
}
ClockFIFOStrategy::ClockFIFOStrategy():BufferStrategy()
{
     this->que=0;
     this->pageMap =0;
     this->pageSet=0;
}
void  ClockFIFOStrategy::release(std::queue<BufferFrame*>*& ques,std::map<Addr,BufferFrame*>*& pageMaps)
{
     if(this->pageSet!=0)
     {
         pageSet->clear();
        delete pageSet;
     }
     pageSet = 0;
    if(this->que!=0)
    {
        delete this->que;
        this->que = 0;
    }
    if(this->pageMap!=0)
    {
        delete this->pageMap;
        this->pageMap =0;
    }

}
 ClockFIFOStrategy::~ClockFIFOStrategy()
 {
     if(this->pageSet!=0)
     {
         pageSet->clear();
        delete pageSet;
     }
     pageSet = 0;
    if(this->que!=0)
    {
        delete this->que;
        this->que = 0;
    }
    if(this->pageMap!=0)
    {
        delete this->pageMap;
        this->pageMap =0;
    }
 }

 void  ClockFIFOStrategy::whenRead(BufferFrame* frame)
 {
   //  printf("1");
    if(pageSet->find(frame->pageNo)==pageSet->end())
    {
     //   printf("2");
    que->push(frame);
     //   printf("3");
    pageSet->insert(frame->pageNo);
      //  printf("4");
    }
    frame->mark=0;
 }

  void ClockFIFOStrategy::whenWrite(BufferFrame* frame)
  {
            if(pageSet->find(frame->pageNo)==pageSet->end())
            {
                que->push(frame);
                pageSet->insert(frame->pageNo);
            }
            frame->mark=0;
  }

  void ClockFIFOStrategy::electPageToDrop(std::vector<Addr>& vec,int number)
  {
     //int size = que->size();
      int modk = 0;
        while(number>0&&!que->empty())
        {
            BufferFrame* frame = que->front();

            que->pop();
            number--;
            if(frame->mark!=0||modk>MAX_PAGE_IN_MEMORY/2)
            {
            vec.push_back(frame->pageNo);
            pageSet->erase(frame->pageNo);
            #ifdef DEBUG
printf("page %lld was elected!\n",frame->pageNo);
#endif // DEBUG
            }else
            {
                modk++;
                frame->mark=1;
                que->push(frame);
                //++;
            }
        }
  }
StrategyInBuffer ClockFIFOStrategy::getStrategy()
{
        return ClOCK;
}
