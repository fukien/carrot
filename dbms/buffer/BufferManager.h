#ifndef BUFFER_MANAGER_INCLUDED
#define BUFFER_MANAGER_INCLUDED
/**
 * 缓冲区最大页面数（页面阈值）
 */
#define MAX_PAGE_IN_MEMORY 1024*16
/**
 * 单次置换的页面百分比
 */
#define SWAP_RATE 0.05
#define  BREAD 0x88
#define BWRITE 0x89
#define WRITE_DIRTY 0x90
#define EMPTY 0x91

#include <queue>
#include <map>
#include <set>

#include "../common.h"
#include "../storage/DBFile.h"
#include "../storage/PageUtil.h"
#include "../util/Thread.h"
// A page status:
// 1 shared: only for read
// 2 exclusive but not write:
// 3 write but not flush: dirty
// 4 flush but still in memory
// 5 flushed and not in memory
/**
 * 缓冲区管理
 * BufferFrame将一个Page封装，并记录页面调度时可能用到的信息
 */
/**
 * We do not consider transaction temporarily.
 * One page has no locks,
 * and only has 3 state:
 * Read, WriteDirty and Empty
 * Read means not  be modified.
 * WriteDirty means the modified page not flush to the disk.
 * Empty means the page is already released and wait for the new data load in.
 */
class BufferFrame
{
public:
    DBFile* dbfile;
    Page* page;
    Addr pageNo;
    int status;
    int requestForUse;
    long long mark;
    double mark2;
    bool edit;

    /// Compare
      bool operator==(const BufferFrame& i) const { return (pageNo==i.pageNo); }
      /// Compare
      bool operator<(const BufferFrame& i) const { return (pageNo<i.pageNo); }
};
/**
 * FIFO Strategy
 * each BufferManager will use a  strategy.
 * The basic implementation is a FIFO strategy.
 * It will be used when the segment requests a page, and releases a page.
 * The FIFO strategy will be used when requesting a page that not in the main memory,
 * at this time, the class will elect some unnecessary pages and drop it.
 * If it is necessary, flush the page to disk.
 * So we need a map to map pageID and the realPage.
 * and a queue to process the page sequence.
 */
 class BufferStrategy
 {
public:
    virtual void whenRead(BufferFrame* frame)=0;
    virtual void whenWrite(BufferFrame* frame)=0;
    virtual void electPageToDrop(std::vector<Addr>& vec,int number)=0;
    virtual void release(std::queue<BufferFrame*>*& que,std::map<Addr,BufferFrame*>*& pageMap)=0;
    BufferStrategy();
    virtual void initialize( std::queue<BufferFrame*>*& que,std::map<Addr,BufferFrame*>*& pageMap)=0;
    ~BufferStrategy();
    virtual StrategyInBuffer getStrategy()=0;
protected:
    std::queue<BufferFrame*>* que;
    std::map<Addr,BufferFrame*>* pageMap;
 };

 class FIFOStrategy:public BufferStrategy
 {
public:
    FIFOStrategy();
    void initialize( std::queue<BufferFrame*>*& que,std::map<Addr,BufferFrame*>*& pageMap);
    ~FIFOStrategy();
    void release(std::queue<BufferFrame*>*& que,std::map<Addr,BufferFrame*>*& pageMap);
    void whenRead(BufferFrame* frame);
    void whenWrite(BufferFrame* frame);
    void electPageToDrop(std::vector<Addr>& vec,int number);
    StrategyInBuffer getStrategy();
private:
    std::set<Addr>* pageSet;
 };

 /**
  * BufferManager
  * is responsible to use the strategy,
  * and determine whether the page should be remove.
  * for example, if a page was being read, but select to be drop, we should wait it.
  * for another example, if a page should be drop but was writeDirty, we should flush it.
  * A page reading:
  * invoke requestPageForRead, if page not in memory, put the page to mapping and pageQue, and invoke whenReading.
  * when finishing reading ,invoke requestPageForRead, if page in waitForReadOrWrite, it means the page need to be flush
  * and then remove the page from the set, and add the page to flusher queue.
  * So does A page writing.
  */
class BufferManager
{
public:
    BufferManager(BufferStrategy* _strategy,PageUtil* _util);
    BufferFrame* requestPageForRead(Addr pageAddr);
    BufferFrame* requestPageForWrite(Addr pageAddr,bool asyc);
    void finishRead(BufferFrame* frame);
    void finishWrite(BufferFrame* frame);
    static void flusher(void* ptr);
    void flushAll();
    /**
    * allocate a new bufferFrame
    * the method will be invoked when the file need increasing
    * or no more freed BufferFrame in the file.
    * The method will cause the file increasing.
    */
  BufferFrame* allocNewBufferFrameForWrite();
    PageUtil* getPageUtil();
    std::queue<BufferFrame*>* getFlusherQueue();
    bool flag;
    ~BufferManager();
        pthread_t pid;
private:
    std::map<Addr,BufferFrame*>* mapping;
    std::queue<BufferFrame*>* pageQue;
    std::set<Addr>* waitForReadOrWrite;
    std::queue<BufferFrame*>* flusherQueue;
    PageUtil* util;
    BufferStrategy* strategy;
    void buildBufferFrame(BufferFrame*& frame, Addr pageNo);
    void releaseBufferFrame(BufferFrame*& frame);
    void dropout(int drop);
};

#endif // BUFFER_MANAGER_INCLUDED
