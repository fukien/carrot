#include "IndexSegment.h"
#include "../index/BPTree.h"
#include"../index/PrimaryHashIndex.h"
#ifdef DEBUG_INDEX
    #include <cstdio>
    #include <cstdlib>
#endif // DEBUG
void IndexSegment::initRootPage()
{

}
IndexSegment::IndexSegment(BufferManager* mgr,DirectorySegment* dir,DataSegment* dataseg,MetaDataSegment* metaseg):Segment(mgr),drs(dir),dts(dataseg),mts(metaseg)
{
    this->indexMeta = new IndexMeta();
    this->indexMetaAddr = drs->findFirstBlock(SegmentType::IndexSeg);
    if(indexMetaAddr<=0)
    {
        indexMetaAddr = drs->allocateBlock(SegmentType::IndexSeg,PageStatus::HalfPage);
        indexMeta->tid = mts->getMetaData()->tid;
        indexMeta->useLen = 0;
        indexMeta->blockNum=1;
        indexMeta->fieldNum=mts->getMetaData()->fieldNum;
        indexMeta->nextAddr=0;
        indexMeta->pageNo = PAGE_ID(indexMetaAddr);
        //indexMeta->indexList
        BufferFrame* frame = manager->requestPageForWrite(indexMetaAddr,false);
        transMetaToFrame(indexMeta,frame);
        frame->edit = true;
        manager->finishWrite(frame);
    }
    else
    {
      //  Addr tmpAddr = this->indexMetaAddr;
       // while(tmpAddr>0)
       // {
            BufferFrame* frame = manager->requestPageForRead(indexMetaAddr);
            transFrameToMeta(frame,this->indexMeta);
            manager->finishRead(frame);

        //}
    }
}
void IndexSegment::flush()
{
    BufferFrame* frame = manager->requestPageForWrite(this->indexMetaAddr,false);
    transMetaToFrame(this->indexMeta,frame);
    manager->finishWrite(frame);
}
IndexSegment::~IndexSegment()
{
    flush();
     for(int i=0;i<this->indexMeta->useLen;i++)
    {
            IndexMetaItem* item = &indexMeta->indexList[i];
            if(item->index!=0)
            {
                item->index->releaseAll();
                delete item->index;
                item->index=0;
            }
    }
    delete this->indexMeta;
    this->indexMeta = 0;
}

short IndexSegment::transFrameToMeta(BufferFrame* frame,IndexMeta* meta)
{
    Page* page = frame->page;
    ushort flag = page->flag&SegmentType::mask;
    if(flag!=SegmentType::IndexSeg)
    {
        #ifdef DEBUG_INDEX
            printf("warning: this page is not a index segment page!\n");
        #endif // DEBUG_INDEX
    }
    //warning: the pageNo will be overwritten in the following code.
    meta->pageNo = frame->pageNo;
    Byte* data = page->data;
    Byte* old = data;
    data+=PAGE_HEAD_LEN;
    data+=PAGE_ALIGN;
    int pos = 0;
    if(data[pos++]!=IndexMetaMagic)
    {
                #ifdef DEBUG_INDEX
            printf("warning: this position is not a indexMeta!\n");
            #endif // DEBUG_INDEX
    }
    meta->tid=data[pos++];
    meta->fieldNum=data[pos++];
    meta->blockNum=data[pos++];
    data+=pos;
    memcpy(&meta->pageNo,data,sizeof(Addr));
    data+=sizeof(Addr);
    memcpy(&meta->nextAddr,data,sizeof(Addr));
    data+=sizeof(Addr);
    memcpy(&meta->useLen,data,sizeof(int));
    data+=sizeof(int);
    for(int i=0;i<meta->useLen;i++)
    {
        short reads = this->readIndexMetaItem(&meta->indexList[i],data);
        meta->indexList[i].index = 0;
        data+=reads;
        if(reads!=12)
        {
            #ifdef DEBUG_INDEX
                printf("warning: an item is not equal to 12 when reading\n");
            #endif // DEBUG_INDEX
        }
    }
}

short IndexSegment::transMetaToFrame(IndexMeta* meta,BufferFrame* frame)
{
    Page* page = frame->page;
    Byte* data = page->data;
    page->usedByte = PAGE_BODY_LEN;
    page->usedLen=0;
    page->usedByteList[0].addr=0;
    page->usedByteList[0].len=0;
    ushort flag = page->flag;
    flag = flag&(~SegmentType::mask)|SegmentType::IndexSeg&(~PageStatus::mask)|PageStatus::HalfPage;
    page->flag = flag;
    data+=PAGE_HEAD_LEN;
    data+=PAGE_ALIGN;
    int pos = 0;
    data[pos++]=IndexMetaMagic;
    data[pos++]=meta->tid;
    data[pos++]=meta->fieldNum;
    data[pos++]=meta->blockNum;
    data+=pos;
    memcpy(data,&meta->pageNo,sizeof(Addr));
    data+=sizeof(Addr);
    memcpy(data,&meta->nextAddr,sizeof(Addr));
    data+=sizeof(Addr);
    memcpy(data,&meta->useLen,sizeof(int));
    data+=sizeof(int);
    for(int i=0;i<meta->useLen;i++)
    {
        if(i>=MAX_INDEX_NUM)break;
        short written = this->writeIndexMetaItem(&meta->indexList[i],data);
        data+=written;
        if(written!=12)
        {
            #ifdef DEBUG_INDEX
                printf("warning: an item is not equal to 12 when writing\n");
            #endif // DEBUG_INDEX
        }
    }

}

short IndexSegment::writeIndexMetaItem(IndexMetaItem* item,Byte* data)
{
    Byte* old = data;
    int pos = 0;
    data[pos++]=IndexItemMagic;
    data[pos++]=item->fid;
    data[pos++]=item->indexType;
    data[pos++]=item->indexLen;
    data+=pos;
    memcpy(data,&item->indexAddr,sizeof(Addr));
    data+=sizeof(Addr);
    return data-old;
}
short IndexSegment::readIndexMetaItem(IndexMetaItem* item,Byte* data)
{
    Byte* old = data;
    int pos =0;
    if(data[pos++]!=IndexItemMagic)
    {
        #ifdef DEBUG_INDEX
        printf("warning: read badly when reading the indexMetaItem!\n");
        #endif
    }
    item->fid = data[pos++];
    item->indexType=data[pos++];
    item->indexLen=data[pos++];
    data+=pos;
    memcpy(&item->indexAddr,data,sizeof(Addr));
    data+=sizeof(Addr);
    return data-old;
}
Index* IndexSegment::createIndex(Byte fid,Byte indexType)
{
// 创建完毕后拿地址
    IndexMetaItem* item = &this->indexMeta->indexList[this->indexMeta->useLen];
    item->fid = fid;
    item->indexLen = this->mts->getMetaData()->head->fieldList[fid].len;
    item->indexType=indexType;
    switch(indexType)
    {
    case IndexType::eptidx:
        item->index = new Index(this,fid,0);
        item->indexAddr = item->index->getRootAddr();
        item->index->create();
        break;
    case IndexType::bptidx:
        item->index = new BPTree(this,fid,0,item);
        item->indexAddr = item->index->getRootAddr();
        item->index->create();
        break;
    case IndexType::hashidx:
        printf("create index now");
        item->index=new  PrimaryHashIndex(this,fid,0);
        item->indexAddr=item->index->getRootAddr();
        item->index->create();
        break;
    }
    this->indexMeta->useLen++;
    return item->index;
}
Index* IndexSegment::loadIndex(IndexMetaItem* item)
{
    Index* indx = 0;
    switch(item->indexType)
    {
        case IndexType::eptidx:
            indx = new Index(this,item->fid,item->indexAddr);
            indx->load();
            break;
        case IndexType::bptidx:
            indx = new BPTree(this,item->fid,item->indexAddr,item);
            indx->load();
            break;
        case IndexType::hashidx:
            indx=new PrimaryHashIndex(this,item->fid,0);
            indx->load();
            break;
    }
    return indx;
}
Index* IndexSegment::findIndex(Byte fid,Byte indexType)
{
    #ifdef DEBUG_INDEX
    printf("indexMeta size:%d\n",this->indexMeta->useLen);
    #endif // DEBUG_INDEX
    for(int i=0;i<this->indexMeta->useLen;i++)
    {
            #ifdef DEBUG_INDEX
    printf("indexMeta [%d] fid %d type %d\n",i,indexMeta->indexList[i].fid,indexMeta->indexList[i].indexType);
    #endif // DEBUG_INDEX
        if(indexMeta->indexList[i].fid==fid&&indexMeta->indexList[i].indexType==indexType)
        {

            IndexMetaItem* item = &indexMeta->indexList[i];
            if(item->index==0)
            {
                item->index = loadIndex(item);
                return item->index;
            }
            else
            {
                return item->index;
            }
        }
    }
}
void IndexSegment::dropIndex(Byte fid,Byte indexType)
{
    IndexMetaItem* item = 0;
    for(int i=0;i<this->indexMeta->useLen;i++)
    {
        if(indexMeta->indexList[i].fid==fid&&indexMeta->indexList[i].indexType==indexType)
        {
            item = &indexMeta->indexList[i];
            for(int j=i;j<this->indexMeta->useLen-1;j++)
            {
                IndexMetaItem* k1 = &indexMeta->indexList[j];
                IndexMetaItem* k2 = &indexMeta->indexList[j+1];
                k1->fid = k2->fid;
                k1->index = k2->index;
                k1->indexAddr = k2->indexAddr;
                k1->indexLen = k2->indexLen;
                k1->indexType = k2->indexType;
            }
            break;
        }
    }
    if(item!=0)
    {
        if(item->index==0)
        {
            item->index = loadIndex(item);
        }
        if(item->index!=0)
        {
            item->index->destroyMySelf();
        }
        this->indexMeta->useLen--;
    }
}
