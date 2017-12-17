#include "MetaDataSegment.h"
#ifdef DEBUG
#include <cstdlib>
#include <cstdio>
#endif // DEBUG
#include "../table/TableUtil.h"
    MetaDataSegment::MetaDataSegment(BufferManager* mgr,DirectorySegment* dir)
    {
        this->manager = mgr;
        this->dir=dir;
        this->tableMeta = new TableMeta();
        this->metaPageAddr = dir->findFirstBlock(SegmentType::MetaDataSeg);
        if(metaPageAddr==0)
        {
            // not found, allocate one
            this->metaPageAddr = dir->allocateBlock(SegmentType::MetaDataSeg,PageStatus::FullPage);
            BufferFrame* frame = manager->requestPageForWrite(this->metaPageAddr,false);
            tableMeta->blockNum=1;
            tableMeta->fieldNum=0;
            tableMeta->head=new FieldPart();
            tableMeta->pageNo=PAGE_ID(metaPageAddr);
            tableMeta->tid=0;
            tableMeta->head->fieldOffset=0;
            tableMeta->head->next=0;
            tableMeta->head->nextPartAddr=0;
            tableMeta->head->partNum=0;
            tableMeta->head->tid=0;
            tableMeta->head->fieldList = 0;
            this->transTableMetaToFrame(frame);
            frame->edit=true;
            manager->finishWrite(frame);
        }else
        {
            BufferFrame* frame = manager->requestPageForRead(this->metaPageAddr);
            this->transFrameToTableMeta(frame);
            manager->finishRead(frame);
            FieldPart* part = tableMeta->head;
            int ofst = 0;
            while(part!=0)
            {
                for(int k=0;k<part->partNum;k++)
                {
                    part->fieldList[k].offsetInTuple=ofst;
                    ofst+=part->fieldList[k].len;
                }
                part= part->next;
            }
        }
    }
    void MetaDataSegment::deleteFieldList()
    {
        while(tableMeta->head!=0)
        {
            if(tableMeta->head->fieldList!=0)
            {
                delete[] tableMeta->head->fieldList;
                tableMeta->head->fieldList=0;
            }
            FieldPart* part = tableMeta->head;
            tableMeta->head = part->next;
            delete part;
        }
    }
    MetaDataSegment::~MetaDataSegment()
    {
        BufferFrame* frame = manager->requestPageForWrite(this->metaPageAddr,false);
        this->transTableMetaToFrame(frame);
        frame->edit=true;
        manager->finishWrite(frame);
        deleteFieldList();
        delete tableMeta;
        this->tableMeta=0;
    }
void MetaDataSegment::transTableMetaToFrame(BufferFrame* frame)
{
    Page* page = frame->page;
    page->usedByte = PAGE_BODY_LEN;
    page->usedLen=1;
    page->usedByteList[0].addr=PAGE_HEAD_LEN;
    page->usedByteList[0].len=PAGE_BODY_LEN;
    ushort flag = page->flag;
    flag = flag&(~SegmentType::mask)|SegmentType::MetaDataSeg&(~PageStatus::mask)|PageStatus::FullPage;
    page->flag=flag;
    Byte* data = page->data;
    data+=PAGE_HEAD_LEN;
    data+=PAGE_ALIGN;
    int pos = 0;
    data[pos++]=TABLE_MAGIC;
    data[pos++]=tableMeta->tid;
    data[pos++]=tableMeta->fieldNum;
    data[pos++]=tableMeta->blockNum;
    data+=pos;
  //  strcpy(tableMeta->tname,"Hello World,aaaa");
    memcpy(data,tableMeta->tname,MAX_TABLE_NAME_LEN);
    data+=MAX_TABLE_NAME_LEN;
  //  data[0]='K';
    //we will trans some FieldPart follow.
    FieldPart* part = tableMeta->head;
    short m = data-page->data;
     //   data[0]='D';
    m = PAGE_SIZE-m;
    while(part!=0)
    {
        //part->tid=0x88;
        short w =TableUtil::wirteFieldPartMeta(data,part,m);
        data+=w;
        m-=w;
                #ifdef DEBUG
        printf("field part addr %llx, write %d byte\n",(PAGE_ADDR(frame->pageNo))+(data-page->data),w);
        #endif // DEBUG
        part = part->next;
    }
}
void MetaDataSegment::transFrameToTableMeta(BufferFrame* frame)
{
    ushort flag =  0&(~SegmentType::mask);
    flag|=SegmentType::MetaDataSeg;
    flag&=(~PageStatus::mask);
    flag|=PageStatus::FullPage;
    Page* page = frame->page;
    if((page->flag&flag)!=flag)
    {
 #ifdef DEBUG
            printf("this frame is not an metadata segment block! pageNo=%lld\n",frame->pageNo);
        #endif // DEBUG
        return ;
    }
    tableMeta->pageNo = frame->pageNo;
    Byte* data = page->data;
    Byte* old = data;
    data+=PAGE_HEAD_LEN;
    data+=PAGE_ALIGN;
    int pos = 0;
    if(data[0]!=TABLE_MAGIC)
    {
        #ifdef DEBUG
            printf("this table magic error! pageNo=%lld\n",frame->pageNo);
        #endif // DEBUG
        return ;
    }
    pos++;
    tableMeta->tid= data[pos++];
    tableMeta->fieldNum= data[pos++];
    tableMeta->blockNum=data[pos++];
    data+=pos;
    memcpy(tableMeta->tname,data,MAX_TABLE_NAME_LEN);
    data+=MAX_TABLE_NAME_LEN;
    //now let us consider whether should we new or delete.
    deleteFieldList();
    tableMeta->head = new FieldPart();
    tableMeta->head->next=0;
    tableMeta->head->nextPartAddr=0;
    short m = data-old;
    m = PAGE_SIZE-m;
    TableUtil::readFieldPartMeta(data,tableMeta->head,m);
}

bool MetaDataSegment::createOrUpdate()
{
        BufferFrame* frame = manager->requestPageForWrite(this->metaPageAddr,false);
        this->transTableMetaToFrame(frame);
        manager->finishWrite(frame);
}
    TableMeta* MetaDataSegment::getMetaData(){
            return tableMeta;
    }
/*
short MetaDataSegment::readFieldMeta(Page* page,int offset,Field* field,short maxOffset)
    {
        Byte* data = page->data;
        data+=offset;
        Byte* old = data;
        if(maxOffset<FIELD_META_LEN)return 0;
        Byte magic = *data;
        if(magic!=FIELD_MAGIC)
        {
            return -1;
        }
        data++;
        Byte fid = *data++;
        Byte flag = *data++;
        Byte dataType = *data++;
        char name[MAX_TABLE_NAME_LEN];
        memcpy(name,data,MAX_TABLE_NAME_LEN);
        int len = 0;
        data += MAX_TABLE_NAME_LEN;
        memcpy(&len,data,sizeof(int));
        data += sizeof(int);
        field->fid=fid;
        field->flag = flag;
        field->dataType = dataType;
        memcpy(field->fname,name,MAX_TABLE_NAME_LEN);
        field->len=len;
        return data-old;
    }
 short MetaDataSegment::writeFieldMeta(Page* page,int offset,Field* field, short maxOffset)
    {
        if(maxOffset<FIELD_META_LEN)return 0;
        Byte* data = page->data;
        data+=offset;
        Byte* old = data;
        int pos =0;
        data[pos++]=FIELD_MAGIC;
        data[pos++]=field->fid;
        data[pos++]=field->flag;
        data[pos++]=field->dataType;
        data+=pos;
        memcpy(data,field->fname,MAX_TABLE_NAME_LEN);
        data+=MAX_TABLE_NAME_LEN;
        memcpy(data,&field->len,sizeof(int));
        data+=sizeof(int);
        return data-old;
    }
short MetaDataSegment::readFieldPartMeta(Page* page,int offset,FieldPart* part,short maxOffset)
    {
        Byte* data = page->data;
        data+=offset;
        Byte* old = data;
            Byte magic = *data++;
            if(magic!=FIELD_PART_MAGIC)
            {
                printf("read part error! magic %x",magic);
                return 0;
            }
            Byte fieldOffset = *data++;
            Byte partNum = *data++;
            Byte tid = *data++;
            Addr nextAddr = 0;
            memcpy(&nextAddr,data,8);
            data+=8;
           short m = maxOffset-12;
            part->fieldOffset = fieldOffset;
            part->partNum = partNum;
            part->tid=tid;
            part->nextPartAddr=nextAddr;
            part->fieldList = new Field[partNum];
            for(int i=0;i<partNum;i++)
            {
                short w = readFieldMeta(page,data-page->data,&part->fieldList[i],m);
                m-=w;
                data+=w;
                if(w==0)
                {
                    printf("Field Meta read failed! current offset %d\n",data-old);
                }
            }
            return data-old;
    }

short MetaDataSegment::wirteFieldPartMeta(Page* page,int offset,FieldPart* part,short maxOffset)
    {
        Byte* data = page->data;
        data+=offset;
        Byte* old = data;
        short maximalOffset = part->partNum*FIELD_META_LEN+12;
        if(maxOffset<maximalOffset)return 0;
        int pos = 0;
        printf("field part magic pos %x\n",(data+pos)-page->data);
        data[pos++]=FIELD_PART_MAGIC;
        data[pos++]=part->fieldOffset;
        data[pos++]=part->partNum;
        data[pos++]=part->tid;
        data+=pos;
        memcpy(data,&part->nextPartAddr,8);
        data+=8;
        int ma= maxOffset-12;
        for(int i=0;i<part->partNum;i++)
        {
            short w = writeFieldMeta(page,data-page->data,&part->fieldList[i],ma);
            ma-= w;
            data+=w;
            if(w==0)
            {
                printf("Field Meta write failed! current offset %d\n",data-old);
            }
        }
        return data-old;

    }*/
