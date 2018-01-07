#include "DirectorySegment.h"
#ifdef DEBUG
#include <cstdlib>
#include <cstdio>
#endif // DEBUG
#include <cstdlib>
#include <cstdio>
Directory* DirectorySegment::allocateDirectory()
{
        Addr addr = getNewDirAddr();
        BufferFrame* frame = manager->allocNewBufferFrameForWrite();//manager->requestPageForWrite(addr,false);
        Directory* d = new Directory();
        d->baseAddr=PAGE_ADDR(frame->pageNo);
        d->next=0;
        d->offset=0;
        d->pageNo=frame->pageNo;
        d->tmpNextBlockAddr=0;
        d->maxAddr=1;
        d->edit=true;
        d->nextToken = 0;
        d->data[0]=SegmentType::DirectorySeg|PageStatus::HalfPage;
        this->transDirToFrame(d,frame);
        frame->edit=true;
        manager->finishWrite(frame);
        if(theLast!=0)
        {
            theLast->tmpNextBlockAddr = d->baseAddr;
            theLast->next = d;
            theLast = d;
        }
         mapping.insert(std::map<Addr,Directory*>::value_type(theLast->baseAddr+PAGE_ADDR(DIRPAGE_BODY),theLast));
      //  this->flushAll();
       // manager->flushAll();
        return d;
}
DirectorySegment::DirectorySegment(BufferManager* mgr):Segment(mgr)
{
    this->manager= mgr;
    head = 0;
    theLast = 0;
            #ifdef DEBUG
        printf("\nsize:%d\n",mgr->getPageUtil()->getFile()->size);
        #endif // DEBUG
    if(mgr->getPageUtil()->getFile()->size<PAGE_SIZE)
    {
        //分配第一块页面作为DirectorySegment
        #ifdef DEBUG
      //  printf("\nabd\n");
        #endif // DEBUG
        BufferFrame* frame = manager->allocNewBufferFrameForWrite();
        head = new Directory();
        head->baseAddr=0;
        head->next=0;
        head->offset=0;
        head->pageNo=frame->pageNo;
        head->tmpNextBlockAddr=0;
        head->maxAddr=1;
        head->nextToken=0;
        head->edit=true;
        head->data[0]=SegmentType::DirectorySeg|PageStatus::HalfPage;
        this->transDirToFrame(head,frame);
        frame->edit=true;
        manager->finishWrite(frame);
                #ifdef DEBUG
        //printf("\nefgh\n");
        #endif // DEBUG
        theLast = head;
        mapping.insert(std::map<Addr,Directory*>::value_type(head->baseAddr+PAGE_ADDR(DIRPAGE_BODY),head));
    }else
    {
        //读取第一块页面作为head
        head = new Directory();
        BufferFrame* frame= mgr->requestPageForRead(0);
        this->transFrameToDir(frame,head);
        mgr->finishRead(frame);
        theLast = head;
        mapping.insert(std::map<Addr,Directory*>::value_type(head->baseAddr+PAGE_ADDR(DIRPAGE_BODY),head));
        while(theLast->tmpNextBlockAddr!=0)
        {
            Directory* d = new Directory();
            frame = mgr->requestPageForRead(theLast->tmpNextBlockAddr);
            this->transFrameToDir(frame,d);
            mgr->finishRead(frame);
            mapping.insert(std::map<Addr,Directory*>::value_type(d->baseAddr+PAGE_ADDR(DIRPAGE_BODY),d));
            theLast->next=d;
            theLast = theLast->next;
        }
    }
}
    void DirectorySegment::flushOne(Directory* dir)
    {
        Addr addr = PAGE_ADDR(dir->pageNo);
        BufferFrame* frame = manager->requestPageForWrite(addr,false);
        transDirToFrame(dir,frame);
        frame->edit=true;
        manager->finishWrite(frame);
    }
    void DirectorySegment::flushAll(){
        Directory* d = head;
        while(d!=0)
        {
            flushOne(d);
            d = d->next;
        }
    }
DirectorySegment::~DirectorySegment()
{
        flushAll();
        Directory* d = head;
        while(d!=0)
        {
            Directory* tmp = d;
            d = d->next;
            delete tmp;
        }
        head = theLast = 0;
        mapping.clear();
}
void DirectorySegment::transFrameToDir(BufferFrame* frame,Directory* dir)
{
    //check frame
    ushort flag =  0&(~SegmentType::mask);
    flag|=SegmentType::DirectorySeg;
    flag&=(~PageStatus::mask);
    flag|=PageStatus::FullPage;
    Page* page = frame->page;
    if((page->flag&flag)!=flag)
    {
        #ifdef DEBUG
            printf("this frame is not an directory segment block! pageNo=%lld\n",frame->pageNo);
        #endif // DEBUG
    return ;
    }
    dir->pageNo=frame->pageNo;
    dir->offset=0;
    Byte* data = page->data;
    data+=PAGE_HEAD_LEN;
    data+=PAGE_ALIGN;
    memcpy(&dir->baseAddr,data,DIRPAGE_BASE_LEN);
    #ifdef DEBUG
    printf("\nfrom start %d:",page->data-data);
    for(int k=0;k<DIRPAGE_BASE_LEN;k++)
    {
        printf("0x%x ",data[k]);
    }
    printf("\nfrom end");
    #endif // DEBUG
    data+=DIRPAGE_BASE_LEN;
    memcpy(&dir->tmpNextBlockAddr,data,DIRPAGE_NEXT_LEN);
    data+=DIRPAGE_NEXT_LEN;
    //memcpy(data,dir->data,DIRPAGE_BODY);
    memcpy(dir->data,data,DIRPAGE_BODY);
}
void DirectorySegment::transDirToFrame(Directory* dir,BufferFrame* frame)
{
        Page* page = frame->page;
        page->usedByte=PAGE_BODY_LEN;
        page->usedLen=1;
        page->usedByteList[0].addr=PAGE_HEAD_LEN;
        page->usedByteList[0].len=PAGE_BODY_LEN;
        ushort flag = page->flag;
        flag = flag&(~SegmentType::mask)|SegmentType::DirectorySeg&(~PageStatus::mask)|PageStatus::FullPage;
        page->flag=flag;
        Byte* data = page->data;
     //   int add = 0;
        data+=PAGE_HEAD_LEN;
        data+=PAGE_ALIGN;
       // add+=PAGE_HEAD_LEN;
      //  printf("after page head len %d\n",add);
        memcpy(data,&dir->baseAddr,DIRPAGE_BASE_LEN);
            #ifdef DEBUG
            printf("\nto frame start %d:",page->data-data);
    for(int k=0;k<DIRPAGE_BASE_LEN;k++)
    {
        printf("0x%x ",data[k]);
    }
    printf("\nto end:");
    #endif // DEBUG
        data+=DIRPAGE_BASE_LEN;
      //  add+=DIRPAGE_BASE_LEN;
     //   printf("after page base len %d\n",add);
        if(dir->next=0)
        {
            // 此处为下一个页面地址，必须是pageNo<<page_addr_len, 这个概念和base_addr概念不同，base_addr是基地址
            // 对于某些分配策略，有page_addr(pageNo)=base_addr
            Addr target = PAGE_ADDR(dir->next->pageNo);
            memcpy(data,&target,DIRPAGE_NEXT_LEN);
        }else
        {
            Addr target = 0;
            memcpy(data,&target,DIRPAGE_NEXT_LEN);
        }
        data+=DIRPAGE_NEXT_LEN;
       // add+=DIRPAGE_NEXT_LEN;
    //     printf("after page next len %d\n",add);
        memcpy(data,dir->data,DIRPAGE_BODY);
     //   add+=DIRPAGE_BODY;
     //   printf("\nadd page size %d\n",add);
        frame->edit=true;
}

void DirectorySegment::initRootPage()
{

}
/**
* findFreeSpaceBlock
* it is only just for test now.
* only when each page update space mark before flush,
* can the method be invoked efficiently.
*/
Addr DirectorySegment::findFreeSapceBlock(Byte segmentType)
{
//    segmentType = segmentType&0xff;
    Directory* dir = head;
    while(dir!=0)
    {
        Addr base = dir->baseAddr;
        for(int i=0;i<DIRPAGE_BODY;i++)
        {
            Byte item = dir->data[i];
                            #ifdef DEBUG
//            if(i<5)
  //           printf("%llx item %llx\n",item&SegmentType::mask,segmentType);
                             #endif // DEBUG
            Byte st = item&SegmentType::mask;
            segmentType = segmentType;
            if(st==segmentType)
            {
                Byte b = item&PageStatus::mask;
                if(b==PageStatus::EmptyPage||b==PageStatus::HalfPage)
                {
                    Addr offset = PAGE_ADDR(i);
                    return (base+offset);
                }
            }
        }
        dir  = dir->next;
    }
    return -1;
}

Addr DirectorySegment::findFirstBlock(Byte segmentType)
{
    //segmentType = segmentType&0xff;
    Directory* dir = head;
    while(dir!=0)
    {
        Addr base = dir->baseAddr;
        for(int i=0;i<DIRPAGE_BODY;i++)
        {
            Byte item = dir->data[i];
            //item = item&0xff;
                #ifdef DEBUG
            if(i<5)
             printf("%llx item %llx\n",item&SegmentType::mask,segmentType);
                             #endif // DEBUG
            if((item&SegmentType::mask)==segmentType)
            {
                    Addr offset = PAGE_ADDR(i);
                    return base+offset;
            }
        }
        dir  = dir->next;
    }
     return 0;
}
Addr DirectorySegment::findNextBlock(Addr addr,Byte segmentType)
{
    Directory* dir = head;
    bool findit = false;
    Addr ofst = 0;
    PageAddr bias  =0;
    while(dir!=0)
    {
        Addr base = dir->baseAddr;
        Addr ofst = addr-base;
        if(ofst>0)
        {   bias = PAGE_ID(ofst);
            if( bias<DIRPAGE_BODY&&ofst>=0)
            {
                #ifdef DEBUG
                printf("ofst find!%x\n", bias);
                #endif
                findit = true;
                break;
            }
        }
        dir  = dir->next;
    }
    if(findit)
    {
         bias&=PAGE_MASK;
         bias++;
        while(dir!=0)
        {
            Addr basea = dir->baseAddr;
            for(int i= bias;i<DIRPAGE_BODY;i++)
            {
                Byte item = dir->data[i];
                if((item&SegmentType::mask)==segmentType)
                {
                    Addr offset = PAGE_ADDR(i);
                    #ifdef DEBUG
                    printf("ofst %x\n", bias);
                    #endif
                    return basea+offset;
                }
            }
             bias=0;
            dir = dir->next;
        }
    }
     return 0;
}
void DirectorySegment::updateSpaceMark(BufferFrame* frame,Byte segmentType,Byte pageStatus)
{
    Addr pageNo = frame->pageNo;
    Addr addr = PAGE_ADDR(pageNo);
    Directory* dir = findDirectory(addr);
    int offset =PAGE_ID(addr-dir->baseAddr);
    if(offset>=DIRPAGE_BODY)
    {
        printf("error! the block is out of range! missing its control block!");
    }
    dir->data[offset]=segmentType|pageStatus;
    if(dir->data[offset]==0)dir->maxAddr--;
}
Addr DirectorySegment::getNewDirAddr()
{
    Directory* dir = head;
    while(dir!=0)
    {
        if(dir->next!=0)
        {
            dir = dir->next;
        }else
        {
            return dir->baseAddr+(PAGE_ADDR(DIRPAGE_BODY));
        }
    }
    return 0;
}
Directory* DirectorySegment::findDirectory(Addr addr)
{
    std::map<Addr,Directory*>::iterator iter =  mapping.lower_bound(addr);
    Directory* dir  = iter->second;
    if(dir->baseAddr<=addr&&(dir->baseAddr+PAGE_ADDR(DIRPAGE_BODY))>addr){
          //  printf("hit it!\n");
            return dir;
    }
    printf(" not hit it!\n");
   dir = head;
    while(dir!=0)
    {
        if(dir->next!=0)
        {
            if(dir->next->baseAddr>addr)
            {
               return dir;
            }
            else
            {
                dir = dir->next;
            }
        }else
        {
            return dir;
        }
    }
}
/**
* current strategy:
* step by step.
* future strategy:
* use map.upper_bound
* try to process the control block deletion
*/
void DirectorySegment::freeBlock(Addr addr)
{
    Directory* dir = findDirectory(addr);
    // test the range
    int offset =PAGE_ID(addr-dir->baseAddr);
    if(offset>=DIRPAGE_BODY)
    {
        printf("error! the block is out of range! missing its control block!");
    }
    dir->data[offset] = 0;
    dir->maxAddr--;
}
Addr DirectorySegment::allocateBlockInOnePage(Directory* dir,Byte segmentType,Byte pageStatus)
{
        if(dir->maxAddr<DIRPAGE_BODY)
        {
            if(dir->nextToken>0&&dir->nextToken<DIRPAGE_BODY)
            {
                if(dir->data[dir->nextToken]==0)
                {
                    dir->data[dir->nextToken]=segmentType|pageStatus;
                    Addr pageOffset = PAGE_ADDR(dir->nextToken);
                    dir->maxAddr++;
                    dir->nextToken=dir->nextToken+1;
                        #ifdef DEBUG
                    printf("\tbase Addr %lld i=%lld pageOffset %llx\t",dir->baseAddr,dir->nextToken,pageOffset);
        #endif // DEBUG
                    return dir->baseAddr+pageOffset;
                }else
                {
                    dir->nextToken  = 0;
                }
            }
            for(int i=0;i<DIRPAGE_BODY;i++)
            {
                if(dir->data[i]==0)
                {
                    dir->data[i]=segmentType|pageStatus;
                    Addr pageOffset = PAGE_ADDR(i);
                    dir->maxAddr++;
                    dir->nextToken=i+1;
                        #ifdef DEBUG
                    printf("\tbase Addr %lld i=%lld pageOffset %llx\t",dir->baseAddr,i,pageOffset);
        #endif // DEBUG
                    return dir->baseAddr+pageOffset;
                }
            }
        }
        return -1;
}
/**
* TODO:
* 细化扫描时分配管理
* 对每个directory对象:
* 1.建立一个链表，来管理碎片区域
* 2.用maxAddr记录最大项
*
* 分配步骤：
* 链表非空，优先分配链表中元素
* 链表为空，分配maxAddr指向元素
* TODO:
*test
*/
Addr DirectorySegment::allocateBlock(Byte segmentType,Byte pageStatus)
{
    Directory* dir = head;
    Addr allocAddrs = allocateBlockInOnePage(theLast,segmentType,pageStatus);
    if(allocAddrs>=0)return allocAddrs;
    while(dir!=0)
    {
        Addr allocAddr = allocateBlockInOnePage(dir,segmentType,pageStatus);
        if(allocAddr>=0)return allocAddr;
        //Addr base = dir->baseAddr;
        //TODO: not found, it means these block is full,try to marked it.
               // printf("dir->maxAddr=%d dirpage=%d\n",dir->maxAddr,DIRPAGE_BODY);
        dir=dir->next;
    }
    // not found, it means a new directory block need allocating.
    // check it!
    #ifdef DEBUG
    printf("******************************************************************\n");
    printf("allocate new directory\n");
    printf("******************************************************************\n");
    #endif // DEBUG
    allocateDirectory();
        #ifdef DEBUG
    printf("******************************************************************\n");
    printf("allocate new directory %x and head %x\n",theLast,head);
    printf("******************************************************************\n");
    #endif // DEBUG
    Addr pgno = theLast->pageNo;
   // printf("\n\npageno=%d dirbody %d\n\n",pgno,DIRPAGE_BODY);
    if(pgno%DIRPAGE_BODY!=0)
    {
        printf("allocate the directory block error! page number = %d\n",pgno);
    }
 //   printf("\n\n1pageno=%d dirbody %d\n\n",pgno,DIRPAGE_BODY);
  //  if(theLast->next!=0)theLast= theLast->next;
  //  printf("recursively\n");
    return this->allocateBlock(segmentType,pageStatus);
   // printf("\n\n2pageno=%d dirbody %d\n\n",pgno,DIRPAGE_BODY);
    dir = theLast;
 //   printf("\n\n3pageno=%d dirbody %d\n\n",pgno,DIRPAGE_BODY);
    Addr bases = dir->baseAddr;
 //   printf("\n\n4pageno=%d dirbody %d\n\n",pgno,DIRPAGE_BODY);
     for(int k=0;k<DIRPAGE_BODY;k++)
    {
        printf("k=%d\n",k);
                                                #ifdef DEBUG
        printf("\t3　check base Addr %lld i=%lld pageOffset %llx\t data %x i=%d\t\t",dir->baseAddr,k, PAGE_ADDR(k),dir->data[k],k);
        #endif // DEBUG
            if(dir->data[k]==0)
            {
                dir->data[k]=segmentType|pageStatus;
                Addr pageOffset = PAGE_ADDR(k);
                dir->maxAddr++;
                                        #ifdef DEBUG
        printf("\t3base Addr %lld i=%lld pageOffset %llx\t",dir->baseAddr,k,pageOffset);
        #endif // DEBUG
                return bases+pageOffset;
            }
    }
    printf("unreachable\n");
    // unreachable
    return 0;

}
