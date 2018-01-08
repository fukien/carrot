#include <queue>
#include <map>

#include "BufferManager.h"
#ifdef DEBUG
#include <cstdlib>
#include <cstdio>
#endif

BufferStrategy::BufferStrategy()
{
    //this->que = ques;
    //this->pageMap = pageMaps;
}
void BufferStrategy::initialize( std::queue<BufferFrame*>*& ques,std::map<Addr,BufferFrame*>*& pageMaps)
{
    this->que = ques;
    this->pageMap = pageMaps;
}
BufferStrategy::~BufferStrategy(){}

FIFOStrategy::FIFOStrategy():BufferStrategy()
{
    this->pageSet = 0;
    this->que = 0;
    this->pageMap = 0;
}
void FIFOStrategy::initialize( std::queue<BufferFrame*>*& ques,std::map<Addr,BufferFrame*>*& pageMaps)
{
    ques = new std::queue<BufferFrame*>();
    pageMaps = new std::map<Addr,BufferFrame*>();
    this->que = ques;
    this->pageMap = pageMaps;
    this->pageSet = new std::set<Addr>();
}
void  FIFOStrategy::release(std::queue<BufferFrame*>*& que,std::map<Addr,BufferFrame*>*& pageMap)
{
    delete que;
    delete pageMap;
    que = 0;
    pageMap = 0;
    this->que=0;
    this->pageMap=0;
    pageSet->clear();
}
FIFOStrategy::~FIFOStrategy()
{
    if(pageSet!=0)
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

void  FIFOStrategy::whenRead(BufferFrame* frame)
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
    //   frame->mark=0;
}

void FIFOStrategy::whenWrite(BufferFrame* frame)
{
    if(pageSet->find(frame->pageNo)==pageSet->end())
    {
        que->push(frame);
        pageSet->insert(frame->pageNo);
    }
    //           frame->mark=0;
}

void FIFOStrategy::electPageToDrop(std::vector<Addr>& vec,int number)
{
    while(number>0&&!que->empty())
    {
        BufferFrame* frame = que->front();
#ifdef DEBUG
        printf("page %lld was elected!\n",frame->pageNo);
#endif // DEBUG
        que->pop();
        number--;
        vec.push_back(frame->pageNo);
        pageSet->erase(frame->pageNo);
    }
}

StrategyInBuffer FIFOStrategy::getStrategy()
{
    return FIFO;
}


BufferManager::BufferManager(BufferStrategy* _strategy,PageUtil* _util):strategy(_strategy),util(util)
{
    this->strategy = strategy;
    this->util = _util;
    strategy->initialize(this->pageQue,this->mapping);
    waitForReadOrWrite = new  std::set<Addr>();
    flusherQueue = new  std::queue<BufferFrame*>();
    this->flag = true;
    //TODO: START Thread, otherwise the page will not flush to the disk.
    //flusher(this);
    pid = Thread::start(flusher,this,true);

#ifdef DEBUG
    if(pid<=0)
    {
        printf("thread start failure!");
    }
    printf("mgr construct");
#endif // DEBUG
}

BufferManager::~BufferManager()
{

    if(strategy==0)
    {
#ifdef DEBUG
        printf(" strategy was released early!");
#endif // DEBUG
    }

    /**
     * we considered whether we should delete the que, because the thread may not be flush it finished.
     */
    flushAll();
    while(!this->flusherQueue->empty());
    strategy->release(this->pageQue,this->mapping);
    this->pageQue=0;
    this->mapping=0;
    flag = false;
    // if(pid>0)pthread_join(pid,NULL);
    while(!this->flag);
    delete waitForReadOrWrite;
    waitForReadOrWrite = 0;
    delete flusherQueue;
    flusherQueue = 0;
#ifdef DEBUG
    printf("mgr destroy");
#endif // DEBUG
}
void BufferManager::dropout(int drop)
{
    std::vector<Addr> vec;
    std::map<Addr,BufferFrame*>::iterator iter;
    strategy->electPageToDrop(vec,drop);//static_cast<int>(MAX_PAGE_IN_MEMORY*SWAP_RATE)
    // the page need to be send to flusher.
    // but some pages is still being read or written.
    // we send these pages to the other queue.
    // so we fetch each page and check the status.
    size_t vecLen = vec.size();
    for(size_t i=0;i<vecLen;i++)
    {
        Addr pageNumber = vec[i];
        iter = mapping->find(pageNumber);
        if(iter!=mapping->end())
        {
            BufferFrame* rw = iter->second;
            if(rw->page->readLock>0||rw->page->writeLock)
            {
                // only when the page finishes read or write,
                // can the mapping erase the item.
                this->waitForReadOrWrite->insert(rw->pageNo);
            }else
            {
                this->flusherQueue->push(rw);
#ifdef DEBUG
                printf("\npush the page no=%lld to the queue, frame.edit = %d\n",rw->pageNo,rw->edit);
#endif // DEBUG
                mapping->erase(iter);
            }
            iter = mapping->end();
        }else
        {
#ifdef DEBUG
            printf("move pageNo=%lld caused page error",pageNumber);
#endif // DEBUG
        }
    }
}
BufferFrame* BufferManager::requestPageForRead(Addr pageAddr)
{
    Addr pageNo = PAGE_ID(pageAddr);
#ifdef DEBUG
    //    printf(" read addr %lld\n",pageAddr);
#endif // DEBUG
    BufferFrame* frame = 0;
    std::map<Addr,BufferFrame*>::iterator iter;
    iter= mapping->find(pageNo);
    if(iter==mapping->end())
    {
        //Not Found
        //If Full, swap the page;
        if(mapping->size()>=MAX_PAGE_IN_MEMORY&&pageQue->size()>=MAX_PAGE_IN_MEMORY/2)
        {
            dropout(static_cast<int>(MAX_PAGE_IN_MEMORY*SWAP_RATE));
        }
        // TODO:check it!
        // Now, the page is free, and then alloc a page and push it.
        this->buildBufferFrame(frame,pageNo);
        util->readPage(pageNo,*frame->page);
        frame->page->readLock++;
        frame->requestForUse=BREAD;
        mapping->insert(std::map<Addr,BufferFrame*>::value_type(pageNo,frame));
        strategy->whenRead(frame);
        return frame;
    }else
    {
        frame = iter->second;
        frame->page->readLock++;
        strategy->whenRead(frame);
        return frame;
    }
}
BufferFrame* BufferManager::allocNewBufferFrameForWrite()
{
    Page p;
    Addr  addr = util->buildNewPage(p);
    return requestPageForWrite(addr,false);
}
BufferFrame* BufferManager::requestPageForWrite(Addr pageAddr,bool asyc)
{
    Addr pageNo = PAGE_ID(pageAddr);
    BufferFrame* frame = 0;
    std::map<Addr,BufferFrame*>::iterator iter;
    iter= mapping->find(pageNo);
    if(iter==mapping->end())
    {
        //Not Found
        //If Full, swap the page;
        if(mapping->size()>=MAX_PAGE_IN_MEMORY&&pageQue->size()>=MAX_PAGE_IN_MEMORY/2)
        {
            dropout(static_cast<int>(MAX_PAGE_IN_MEMORY*SWAP_RATE));
        }
        // Now, the page is free, and then alloc a page and push it.
        this->buildBufferFrame(frame,pageNo);
        util->readPage(pageNo,*frame->page);
        // because the page was build just now, others will not write it!
        frame->page->writeLock=true;
        frame->requestForUse=BWRITE;
        mapping->insert(std::map<Addr,BufferFrame*>::value_type(pageNo,frame));
        strategy->whenWrite(frame);
        return frame;
    }else
    {
        frame = iter->second;
        frame->requestForUse=BWRITE;
        if(!frame->page->writeLock)
        {
            frame->page->writeLock=true;
            strategy->whenWrite(frame);
            return frame;
        }else
        {
            // TODO: it is indeed need a  write lock!
            if(!asyc)
            {
                while(true)
                {
                    while(frame->page->writeLock);
                    if(!frame->page->writeLock)
                    {   frame->page->writeLock=true;
                        return frame;
                    }
                }
            }else
            {
                return 0;
            }
        }
    }
}
void BufferManager::finishWrite(BufferFrame* frame)
{
    frame->page->writeLock=false;
    std::set<Addr>::iterator setIter = this->waitForReadOrWrite->find(frame->pageNo);
    if(setIter!=this->waitForReadOrWrite->end())
    {
        if(frame->page->readLock==0&&!frame->page->writeLock)
        {

            this->waitForReadOrWrite->erase(setIter);
            std::map<Addr,BufferFrame*>::iterator mapIter = mapping->find(frame->pageNo);
            if(mapIter!=mapping->end())
            {
                mapping->erase(mapIter);
            }else
            {
#ifdef DEBUG
                printf("pageNo %lld is missing when finish read",frame->pageNo);
#endif // DEBUG
            }
            this->flusherQueue->push(frame);
        }
    }
}
void BufferManager::finishRead(BufferFrame* frame)
{
    frame->page->readLock--;
    std::set<Addr>::iterator hsetIter = this->waitForReadOrWrite->find(frame->pageNo);
    // find the page in the wait set, we need to push it to the flush set.
    if(hsetIter!=this->waitForReadOrWrite->end())
    {
        if(frame->page->readLock==0&&!frame->page->writeLock)
        {
            this->waitForReadOrWrite->erase(hsetIter);
            std::map<Addr,BufferFrame*>::iterator mapIter = mapping->find(frame->pageNo);
            if(mapIter!=mapping->end())
            {
                mapping->erase(mapIter);
            }else
            {
#ifdef DEBUG
                printf("pageNo %lld is missing when finish read",frame->pageNo);
#endif // DEBUG
            }
            this->flusherQueue->push(frame);
        }
    }
}
void BufferManager::buildBufferFrame(BufferFrame*& frame, Addr pageNo)
{
    frame = new BufferFrame();
    frame->pageNo=pageNo;
    frame->page=new Page();
    this->util->buildPage(*frame->page,pageNo);
    frame->requestForUse=EMPTY;
    frame->status=EMPTY;
    frame->edit =false;
    //util->readPage(pageNo,frame->page);
}
void BufferManager::releaseBufferFrame(BufferFrame*& frame)
{
#ifdef DEBUG
    printf("release frame pageNo %llx\t",frame->pageNo);
#endif // DEBUG
    this->util->releasePage(*frame->page);
    delete frame->page;
    frame->page=0;
    frame->pageNo=-1;
    delete frame;
    frame = 0;

}
void BufferManager::flusher(void* ptr)
{
    BufferManager* mgr = static_cast<BufferManager*>(ptr);
#ifdef DEBUG
    printf("do flusher");
#endif // DEBUG
    while(mgr->flag)
    {
        //
        std::queue<BufferFrame*>* que = mgr->getFlusherQueue();
        while(!que->empty())
        {
            BufferFrame* frame = que->front();
            que->pop();
#ifdef DEBUG
            printf("tget a page from a queue no=%llx\t",frame->pageNo);
#endif // DEBUG

            if(frame->edit)
            {
                mgr->getPageUtil()->writePage(frame->pageNo,*frame->page);
            }
            mgr->releaseBufferFrame(frame);
            frame = 0;
        }
    }
    mgr->flag=true;
    mgr->pid=0;
}
/*
   BufferFrame* BufferManager::allocNewBufferFrame()
   {

   }*/
void BufferManager::flushAll()
{

    while(this->pageQue->size()>0)
    {
#ifdef DEBUG
        printf("a loop of dropping  size = %ld\n",this->pageQue->size());
#endif // DEBUG
        dropout(this->pageQue->size());
    }
    //printf("not implement!");
}

PageUtil* BufferManager::getPageUtil()
{
    return util;
}
std::queue<BufferFrame*>* BufferManager::getFlusherQueue()
{
    return this->flusherQueue;
}
