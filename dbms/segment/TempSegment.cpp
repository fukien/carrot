#include<stdio.h>
#include<string.h>
#include "../storage/PageUtil.h"
#include "../buffer/BufferManager.h"
#include "../common.h"
#include "Segment.h"
#include "IndexSegment.h"
#include "MetaDataSegment.h"
#include "DirectorySegment.h"
#include "TempSegment.h"
#define TempMagic 0x07
#define MAX_MAGIC_NUM 100

int brave=0;
void tempSegment::tempSegment(BufferManager* mgr,DirectorySegment* dir,DataSegment* dataseg)
{

}

Addr creatTemp(BufferManager* manager,DirectorySegment* dir)
{
    this->node= new tempnode();
    this->nodeaddr = dir->findFirstBlock(SegmentType::TempSeg);
    if(nodeaddr<=0)
    {
        nodeaddr = drs->allocateBlock(SegmentType::TempSeg,PageStatus::HalfPage);
        node->length=0;
        BufferFrame* frame = manager->requestPageForWrite(nodeaddr,false);
        transTemptoFrame(node,frame);
        frame->edit = true;
        manager->finishWrite(frame);
    }
    else
    {
      //  Addr tmpAddr = this->indexMetaAddr;
       // while(tmpAddr>0)
       // {
            BufferFrame* frame = manager->requestPageForRead(nodeaddr);
            transFrameToMeta(frame,this->node);
            manager->finishRead(frame);
        //}
    }
    return nodeaddr;
}


short tempSegment::findfristItem()
{

}
void tempSegment::transFrametoTemp(BufferFrame* frame,tempnode* node)
{
     Page* page = frame->page;
    ushort flag = page->flag&SegmentType::mask;
    if(flag!=SegmentType::TempMagic)
    {
        #ifdef DEBUG_INDEX
            printf("warning: this page is not a index segment page!\n");
        #endif // DEBUG_INDEX
    }
    //warning: the pageNo will be overwritten in the following code.
    node->nodeaddr= frame->pageNo;
    Byte* data = page->data;
    Byte* old = data;
    data+=PAGE_HEAD_LEN;
    data+=PAGE_ALIGN;
    int pos = 0;
//    if(data[pos++]!=TempMagic)
//    {
//                #ifdef DEBUG_INDEX
//            printf("warning: this position is not a indexMeta!\n");
//            #endif // DEBUG_INDEX
//    }
//    data+=pos;
    memcpy(&node->nodeaddr,data,sizeof(Addr));
    data+=sizeof(Addr);
    memcpy(&node->length,data,sizeof(int));
    data+=sizeof(int);
    memcpy(&node->type,data,sizeof(int));
    data+=sizeof(int);
   // memcpy(&node->fid,data,sizeof(int));
   // data+=sizeof(int);
    for(int i=0;i<node->length;i++)
    {
        short reads = this->readtempItem(&node->arr[i],data);
        //meta->indexList[i].index = 0;
        data+=reads;
    /*    if(reads!=12)
        {
            #ifdef DEBUG_INDEX
                printf("warning: an item is not equal to 12 when reading\n");
            #endif // DEBUG_INDEX
        }*/
    }
     memcpy(&node->nodeaddr,data,sizeof(Addr));
     data+=sizeof(Addr);
}


void tempSegment::transTemptoFrame(BufferFrame* frame,tempnode* node)
{
    Page* page = frame->page;
    Byte* data = page->data;
    page->usedByte = PAGE_BODY_LEN;
    page->usedLen=0;
    page->usedByteList[0].addr=0;
    page->usedByteList[0].len=0;
    ushort flag = page->flag;
    flag = flag&(~SegmentType::mask)|SegmentType::TempSeg&(~PageStatus::mask)|PageStatus::HalfPage;
    page->flag = flag;
    data+=PAGE_HEAD_LEN;
    data+=PAGE_ALIGN;
    int pos = 0;
    //data[pos++]=TempMagic;
    //data+=pos;
    memcpy(data,&node->nodeaddr,sizeof(Addr));
    data+=sizeof(Addr);
    memcpy(data,&node->length,sizeof(int));
    data+=sizeof(int);
    memcpy(data,&node->type,sizeof(int));
    data+=sizeof(int);
    for(int i=0;i<node->length;i++)
    {
        if(i>=MAX_TEMP_NUM)break;
        short written = this->writetempItem(&node->length[i],data);
        data+=written;
      /*  if(written!=12)
        {
            #ifdef DEBUG_INDEX
                printf("warning: an item is not equal to 12 when writing\n");
            #endif // DEBUG_INDEX
        }*/
    }
    memcpy(data,&node->nodeaddr,sizeof(Addr));
    data+=sizeof(Addr);
}

short writetempItem(tempitem* item,Byte* data)
{
    Byte* old = data;
    int pos = 0;
    //data[pos++]=TempMagic;
    //data+=pos;
    memcpy(data,&item->keyaddr,sizeof(Addr));
    data+=sizeof(Addr);
    memcpy(data,&item->value,sizeof(Byte)*8);
    data+=sizeof(Byte)*8;

    return data-old;
}

short tempSegment::readtempItem(tempitem* item,Byte* data)
{
    Byte* old = data;
    int pos =0;
    //if(data[pos++]!=TempMagic)
    {
        #ifdef DEBUG_INDEX
      //  printf("warning: read badly when reading the indexMetaItem!\n");
        #endif
    }
    //data+=pos;
    memcpy(&item->keyaddr,data,sizeof(Addr));
    data+=sizeof(Addr);
    memccpy(&item->value,data,sizeof(Byte)*8);
    data+=sizeof(Byte)*8;
    return data-old;
}

bool tempSegment::WriteIntoTemp(tempnode *node,tempitem *item)
{
    int l;
    l=node->length;
    if(l>=100)
        return false;
    node->arr[l].value=item.value;
    node->arr[l].keyaddr=item.keyaddr;
    l++;
    node->length=l;
    return true;
}
