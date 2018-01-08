#ifndef DIRECTORYSEGMENT_H_INCLUDED
#define DIRECTORYSEGMENT_H_INCLUDED

#include <map>
#include "../common.h"
#include "Segment.h"

#define  DIRPAGE_BASE_LEN 8u // 每页的基地址长
#define DIRPAGE_NEXT_LEN 8u // 下一页的地址长
#define DIRPAGE_HEAD_LEN (DIRPAGE_BASE_LEN+DIRPAGE_NEXT_LEN) //目录块首部长
#define DIRPAGE_OFFSET (PAGE_HEAD_LEN+DIRPAGE_HEAD_LEN) //目录块数据相对于块首部偏移
#define DIRPAGE_BODY (PAGE_HEAD_BODY*8 - DIRPAGE_HEAD_LEN) //一块所承载的数据
//a list
// it seems to be not fit for using a array to store addr
// 1byte 数据,控制8K数据,则一个directory对象,可以控制7256*8K=56.6M数据
// 每次数据增量，取决于DBFile.h中INCREASE_THRESHOLD

class Directory
{
    public:
        Addr baseAddr;//　该页的第一个空块的地址
        Addr pageNo;//　代表本页的地址
        Byte* data;
        Directory* next;  // 下一个directory页的地址
        bool edit;
        Addr tmpNextBlockAddr;
        Directory():baseAddr(0),pageNo(0),next(0),edit(false)
        {
            data = new Byte[DIRPAGE_BODY];
            memset(data,0,DIRPAGE_BODY*sizeof(Byte));
            nextToken = 0;
        }
        ~Directory()
        {
            delete[] data;
        }
        int offset;
        Addr maxAddr;
        Addr nextToken;
    };

class DirectorySegment : public Segment
{
public:
    DirectorySegment(BufferManager* mgr);
    ~DirectorySegment();
/**
 * now let us design the page allocation/revocation algorithm
 * only when a block allocate or revoke need to invoke method here
 * other time we can use a notification(Full empty or not full) to edit the data.
 * We can find the following operation:
 * 1. allocate a block, mark the block, and return the addr.
 * 2. edit the block mark, full/not full, a notification function.
 * 3. revoke a block.
 * 4. find a not full block.DIRPAGE_BODY
 */
    Addr findFreeSapceBlock(Byte segmentType);
    Addr findFirstBlock(Byte segmentType);
    Addr findNextBlock(Addr addr,Byte segmentType);
    void updateSpaceMark(BufferFrame* frame,Byte segmentType,Byte pageStatus);
    void freeBlock(Addr addr);
    Directory* allocateDirectory();
    Addr allocateBlock(Byte segmentType,Byte pageStatus);
    Addr getNewDirAddr();
    void initRootPage();

private:
        Addr allocateBlockInOnePage(Directory* dir,Byte segmentType,Byte pageStatus);
    void transFrameToDir(BufferFrame* frame,Directory* dir);
    void transDirToFrame(Directory* dir,BufferFrame* frame);
    void flushOne(Directory* dir);

    void flushAll();

    Directory* findDirectory(Addr addr);
    Directory* head;
    Directory* theLast;
    std::map<Addr,Directory*> mapping;
};

#endif // DIRECTORYSEGMENT_H_INCLUDED
