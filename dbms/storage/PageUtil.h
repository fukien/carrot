#ifndef FILEBUFFER_H_INCLUDED
#define FILEBUFFER_H_INCLUDED
#include <map>
#include <queue>
#include <cstring>
#include "../common.h"
#include "DBFile.h"
#include "FreeBuffer.h"
/**
 * 页面管理类。
 * 负责向Freebuffer申请内存空间，以及向表文件中申请页面数据，组装成Page结构。
 * 同时负责帮助Page结构管理页面空闲区域（通过bitmap数组)，bitmap在内存中会实例化为一个数组，
 * 每一项为被连续使用的内存区域，包含块内偏移地址和使用长度。
 * 注意Page结构的构造和释放需要使用本类的方法，不能自行new一个Page
 */
typedef struct Used
{
    PageAddr addr;
    uint len;
}Used;
/**
 * 通过标记来模拟读写锁,由于一个页可以供多个进程读或单个进程写，所以分别使用int和bool标记
 *
 */
typedef struct Page
{
    Addr pageNo;
    Buffer* buffer;
    Byte* data;
    // 该页有多少字节被占用
    ushort usedByte;
    //该页的标志位,共16位，具体含义：
    //0x0～0x7（3位） 该页属于的段，具体定义参照Segment.h
    ushort flag;
    // 该页是否在内存中
    bool inMem;

    Used usedByteList[PAGE_HEAD_BODY/2];
    int usedLen;
    int readLock;
    bool writeLock;

    ushort maxLen;
} Page;
/*
class VisitStrategy
{
    virtual void beforeSharedReadPage(Page& page)=0;
    virtual void beforeOccupiedReadPage(Page& page)=0;
    virtual void beforeFinishRead(Page& page)=0;
    virtual void beforeFinishWrite(Page& page)=0;
    virtual void beforeWritePage(Page& page)=0;
    virtual void dropout(Page* page,uint& n)=0;

};*/
class PageUtil
{
    public:
        PageUtil(DBFile* dbfile,FreeBuffer* buffer);
        ~PageUtil();
        void buildPage(Page& page,Addr pageNo=0);
        Addr buildNewPage(Page& page);
        void releasePage(Page& page);
        void buildUsedByteList(Byte* iter,Page& page);
        void buildPageUsedByteMap(Page& page);
        void readPage(Addr pageNo,Page& page);
        void writePage(Addr pageNo,Page& page);
        Addr allocSpace(Page& page,int len);
        bool freeSpace(Page& page,PageAddr addr, int len);
        DBFile* getFile();
    private:
        DBFile* dbfile;
        FreeBuffer* freeBuffer;
        void listMove(int k,int offset,bool forward,Page& page);
        //  VisitStrategy* strategy;
};
#endif // FILEBUFFER_H_INCLUDED
