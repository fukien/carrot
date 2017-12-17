#include "PageUtil.h"
#ifdef DEBUG
#include <cstdio>
#include <cstdlib>
#endif

Addr PageUtil::buildNewPage(Page& page)
{
    Addr size = dbfile->size;
    Addr truncat= size&(~PAGE_MASK);
    Addr pageNo = PAGE_ID(truncat);
    Byte buf[PAGE_SIZE];
    memset(buf,0u,PAGE_SIZE);
    dbfile->write(buf,truncat,PAGE_SIZE);
    buildPage(page,pageNo);
    return truncat;
}
PageUtil::PageUtil(DBFile* dbfiles,FreeBuffer* buffers)
{
    this->dbfile = dbfiles;
    this->freeBuffer=buffers;
}
PageUtil::~PageUtil()
{
    this->dbfile = 0;
    this->freeBuffer= 0;
}
// TODO: 空闲空间分配，策略目前为first-fit,找第一个最合适的，试图寻找其中的maxlen（即一次可申请的最大连续空间），
//或者利用一种类似dp的增量方法每次不必全块扫描就可以知道maxLen，注释代码勿删
Addr PageUtil::allocSpace(Page& page,int len)
{
    //3 steps:
    //1 if useLen==0  && len<pageSize-pageHead => useByteList[useLen].addr=page_head_len, .size = len
    //2 if useLen!=0  find the best fit.
    //3 if not found and have left
    //4 if no left
    PageAddr addr = PAGE_HEAD_LEN+PAGE_ALIGN;
    int k = 0;
    int findk = 0;
    for(;k<page.usedLen;k++)
    {
        int pos = page.usedByteList[k].addr;
        int length = page.usedByteList[k].len;
        if(pos-addr>=len){
                if(findk==0){
                        findk = k;
                        break;
                }
                //if(pos-addr>page.maxLen)page.maxLen=pos-addr;
        }
        addr = pos+length;
    }
    /*
    if(k!=findk&&k==page.usedLen)
    {
        if(PAGE_SIZE-addr>page.maxLen)page.maxLen=PAGE_SIZE-addr;
    }*/
    if(findk!=0)k = findk;
    if(k<page.usedLen)
    {
        listMove(k,1,true,page);
        /*
        for(int j=page.usedLen-1;j>=k;j--)
        {
            page.usedByteList[j+1].addr=page.usedByteList[j].addr;
            page.usedByteList[j+1].len=page.usedByteList[j].len;
        }*/
                //page.usedLen++;
        page.usedByteList[k].addr=addr;
        page.usedByteList[k].len=len;

        page.usedByte+=len;
        return addr;
    }else if(PAGE_SIZE-addr>=len)
    {
        page.usedByteList[page.usedLen].addr=addr;
        page.usedByteList[page.usedLen].len=len;
        page.usedLen++;
        page.usedByte+=len;
        return addr;
    }
    return -1;
}
void PageUtil::listMove(int k,int offset,bool forward,Page& page)
{
    if(forward)
    {
        // p[k]-p[k+offset-1] is empty
        for(int j=page.usedLen-1;j>=k;j--)
        {
            page.usedByteList[j+offset].addr=page.usedByteList[j].addr;
            page.usedByteList[j+offset].len=page.usedByteList[j].len;
        }
        page.usedLen+=offset;
    }else
    {
        // p[k]-p[k+offset-1] was overlapped
        for(int j=k;j<page.usedLen-offset;j++)
        {
            page.usedByteList[j].addr=page.usedByteList[j+offset].addr;
            page.usedByteList[j].len=page.usedByteList[j+offset].len;
        }
        page.usedLen-=offset;
    }
}
//TODO : 删除一个区间，跨越多个连续的list
bool PageUtil::freeSpace(Page& page,PageAddr addr,int len)
{
    int k = 0;
    int pos =0;
    int length =0;
    // judgement: addr>=pos && pos+length>=addr+len
    // situation 1: addr==pos && len==length , drop the space , and move the left  [j]=[j+1]
    // situation 2: addr==pos && len<length, [k].addr=addr+len,[k].len=length-len
    //situation 3: addr>pos && pos+length=addr+len: [k].addr=pos,[k].len=length-len
    //situation 4:addr>pos && pos+length>addr+len
    //[k].addr=pos,[k].len=  addr-pos
    //move forward [j+1]=[j]
    //[k+1].addr = addr+len,[k+1].len=pos+length-(addr+len)
    //  move forward:  s4
    // move backward: s1
    // not move s2 s3
    for(;k<page.usedLen;k++)
    {
        pos = page.usedByteList[k].addr;
        length = page.usedByteList[k].len;
        if(addr>=pos&&pos+length>=addr+len)
        {
            break;
        }
    }
    if(k<page.usedLen)
    {
        if(addr==pos && len<length)
        {
            page.usedByteList[k].addr=pos+len;
            page.usedByteList[k].len = length-len;
            return true;
        }else if(addr>pos&& pos+length==addr+len)
        {
            page.usedByteList[k].addr=pos;
            page.usedByteList[k].len = length-len;
            return true;
        }else if(addr==pos&& pos+length==addr+len)
        {
            listMove(k,1,false,page);
            return true;
        }else if(addr>pos && pos+length>addr+len)
        {
            page.usedByteList[k].addr=pos;
            page.usedByteList[k].len = addr-pos;
            listMove(k+1,1,true,page);
            page.usedByteList[k+1].addr=addr+len;
            page.usedByteList[k+1].len = pos+length-(addr+len);
            return true;
        }
        page.usedByte-=len;
    }
    // 如果没找到，一定有k=pageUsedLen,循环不会进入
    /*
    for(int j=k;j<page.usedLen;j++)
    {
        page.usedByteList[j].addr=page.usedByteList[j+1].addr;
        page.usedByteList[j].len=page.usedByteList[j+1].len;
    }
    if(pos==addr)
    {
        page.usedLen--;
        page.usedByte-=length;
        return true;
    }*/
    return false;
}
void PageUtil::buildUsedByteList(Byte* iter,Page& page)
{
 int len =0;
    bool currentIsUsed = false;
    PageAddr addr = PAGE_HEAD_LEN+PAGE_ALIGN;
    for(int i=0;i<PAGE_HEAD_BODY;i++)
    {
        Byte b = *(iter++);
        Byte mask = 0x1;
        while(mask!=0x0)
        {
            if((b&mask)!=0)
            {
                if(!currentIsUsed)
                {
                    currentIsUsed=true;
                    page.usedByteList[len].addr=addr;
                }
                page.usedByteList[len].len++;
            }else
            {
                if(currentIsUsed)
                {
                    len++;
                    currentIsUsed=false;
                }
            }
            mask<<=1;
            addr++;
        }
    }
    page.usedLen=len;
}
void PageUtil::readPage(Addr pageNo,Page& page)
{
    dbfile->read(page.data,pageNo*PAGE_SIZE,PAGE_SIZE);
    Byte* iter = page.data;
    memcpy(&page.usedByte,iter,sizeof(ushort));
    iter+=sizeof(ushort)/sizeof(Byte);
    memcpy(&page.flag,iter,sizeof(ushort));
    iter+=sizeof(ushort)/sizeof(Byte);
    buildUsedByteList(iter,page);
    page.inMem=true;
}
void PageUtil::buildPageUsedByteMap(Page& page)
{
    //clear the map
    for(int i=PAGE_HEAD_LEN;i<PAGE_HEAD_BODY;i++)
    {
        page.data[i]=0u;
    }
    //rebuild the map
    for(int i=0;i<page.usedLen;i++)
    {
        PageAddr addr = page.usedByteList[i].addr;
        int len = page.usedByteList[i].len;
        PageAddr offset = addr-PAGE_HEAD_LEN-PAGE_ALIGN;
        PageAddr pos = offset/8+PAGE_USED+PAGE_FLAG;
        offset = offset%8;
        Byte b = 0x1u;
        b<<= offset;
        for(int j=0;j<len;j++)
        {
            page.data[pos]|= b;
    #ifdef DEBUG
   //     printf("pos=0x%x, offset = 0x%x,page.data[pos]=0x%x \n",pos,offset,page.data[pos]);
    #endif // DEBUG
            b<<=1;
            offset++;
            if(offset==8)
            {
                offset = 0;
                b=0x1u;
                pos++;
            }
        }
    }
}
void PageUtil::writePage(Addr pageNo,Page& page)
{
    #ifdef DEBUG
    printf("pageNo = %lld was writing\t",pageNo);
    #endif // DEBUG
    Byte* iter = page.data;
    memcpy(iter,&page.usedByte,sizeof(ushort));
    iter+=sizeof(ushort);
    memcpy(iter,&page.flag,sizeof(ushort));
    iter+=sizeof(ushort);
    buildPageUsedByteMap(page);
    dbfile->write(page.data,pageNo*PAGE_SIZE,PAGE_SIZE);
}

void PageUtil::buildPage(Page& page,Addr pageNo)
{
    page.pageNo = pageNo;
    Buffer* buffer = freeBuffer->allocBuffer();
    buffer->page=&page;
    page.buffer=buffer;
    page.data= buffer->data;
    page.usedByte=0;
    page.usedLen=0;
}

void PageUtil::releasePage(Page& page)
{
    page.data=0;
    page.buffer->page=0;
    freeBuffer->freeBuffer(page.buffer);
    page.buffer=0;
    page.inMem=false;
}

DBFile* PageUtil::getFile()
{
    return this->dbfile;
}
