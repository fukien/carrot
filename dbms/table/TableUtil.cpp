#include "TableUtil.h"
#include <cstdlib>
#include <cstdio>
/**
 * we do not consider the date format temporarily.
 */
short TableUtil::readFieldMeta(Byte* data,Field* field,short maxOffset)
    {
        Byte* old = data;
        if(maxOffset<FIELD_META_LEN)return 0;
        Byte magic = *data;
        if(magic!=FIELD_MAGIC)
        {
            printf("read part error! magic %x",magic);
            return -1;
        }
        data++;
        Byte fid = *data++;
        Byte flag = *data++;
        Byte dataType = *data++;
        char name[MAX_TABLE_NAME_LEN];
        memcpy(name,data,MAX_TABLE_NAME_LEN);
                //printf("\ntable name %s\n",name);
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
 short TableUtil::writeFieldMeta(Byte* data,Field* field, short maxOffset)
    {
        if(maxOffset<FIELD_META_LEN)return 0;
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
short TableUtil::readFieldPartMeta(Byte* data,FieldPart* part,short maxOffset)
    {
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
                short w = readFieldMeta(data,&part->fieldList[i],m);
                m-=w;
                data+=w;
                if(w==0)
                {
                    printf("Field Meta read failed! current offset %d\n",data-old);
                }
            }
            return data-old;
    }
    /**
    *
    */
short TableUtil::wirteFieldPartMeta(Byte* data,FieldPart* part,short maxOffset)
    {
        Byte* old = data;
        short maximalOffset = part->partNum*FIELD_META_LEN+12;
        if(maxOffset<maximalOffset)return 0;
        int pos = 0;
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
            short w = writeFieldMeta(data,&part->fieldList[i],ma);
            ma-= w;
            data+=w;
            if(w==0)
            {
                printf("Field Meta write failed! current offset %d\n",data-old);
            }
        }
        return data-old;
    }

short TableUtil::readTuple(Byte* data,Tuple* tuple,TableMeta* meta)
{
    Byte* old = data;
    Byte magic = *data++;
    if(magic!=TUPLE_MAGIC)
    {
        printf(" tuple magic error! it is not a tuple! tuple offset %x\n",tuple->offset);
        return 0;
    }
    tuple->tid = *data++;
    memcpy(&tuple->offset,data,sizeof(PageAddr));
    data+=sizeof(PageAddr);
    memcpy(&tuple->timeStamp,data,8);
    data+=8;
    for(int k =0;k<meta->fieldNum;k++)
    {
        Column* c = &tuple->column[k];
        memcpy(c->data,data,c->field->len);
        data+=c->field->len;
    }
    return data-old;
}
short TableUtil::writeTuple(Byte* data,Tuple* tuple,TableMeta* meta)
{
    Byte* old = data;
    int pos = 0;
    data[pos++]= TUPLE_MAGIC;
    data[pos++]=tuple->tid;
    data+=pos;
    memcpy(data,&tuple->offset,sizeof(PageAddr));
    data+=sizeof(PageAddr);
    memcpy(data,&tuple->timeStamp,8);
    data+=8;
    //for
    for(int k =0 ;k<meta->fieldNum;k++)
    {
        Column* c = &tuple->column[k];
        memcpy(data,c->data,c->field->len);
        data+=c->field->len;
    }
    return data-old;
}
short TableUtil::readColumn(void* target,Column* column)
{
    int dt = column->field->dataType;
 //   if(dt!=DataTypeFlag::CHAR&&dt!=DataTypeFlag::VARCHAR)
    memcpy(target,column->data,column->field->len);
 //   else
//    strcpy(reinterpret_cast<char*>(target),reinterpret_cast<char*>(column->data));
    /*
    switch(column->field->dataType)
    {
        case DataTypeFlag::CHAR:
            memcpy()
            break;
        case DataTypeFlag::DATE:break;
        case DataTypeFlag::DOUBLE:break;
        case DataTypeFlag::FLOAT:break;
        case DataTypeFlag::INTEGER:break;
        case DataTypeFlag::LONG:break;
        case DataTypeFlag::VARCHAR:break;
    }*/
}
 short TableUtil::writeColumn(void* target,Column* column)
 {
    int dt = column->field->dataType;
  //  if(dt!=DataTypeFlag::CHAR&&dt!=DataTypeFlag::VARCHAR)
     memcpy(column->data,target,column->field->len);
    // else
     {
       //  strcpy(reinterpret_cast<char*>(column->data),reinterpret_cast<char*>(target));
     }
     /*
    switch(column->field->dataType)
    {
        case DataTypeFlag::CHAR:break;
        case DataTypeFlag::DATE:break;
        case DataTypeFlag::DOUBLE:break;
        case DataTypeFlag::FLOAT:break;
        case DataTypeFlag::INTEGER:break;
        case DataTypeFlag::LONG:break;
        case DataTypeFlag::VARCHAR:break;
    }*/
 }
 short TableUtil::estimateTupleSize(TableMeta* meta)
{
    short offset = TUPLE_HEAD_LEN;
    FieldPart* part = meta->head;
    while(part!=0)
    {
        for(int k=0;k<part->partNum;k++)
        {
            Field* fd = &part->fieldList[k];
            offset += fd->len;
        }
        part = part->next;
    }
    return offset;
}
Tuple* TableUtil::buildTuple(TableMeta* meta)
{
    Tuple* t = new Tuple();
    t->meta = meta;
    t->tid = meta->tid;
    t->timeStamp = 0;
    t->offset = 0;
    t->tupleAddr =0;
    t->column = new Column[meta->fieldNum];
    int pos = 0;
    FieldPart* part = meta->head;
    while(part!=0)
    {
        for(int k=0;k<part->partNum;k++)
        {
            Column* col = &t->column[pos];
            col->field=&part->fieldList[k];
            col->data = new Byte[col->field->len];
            pos++;
        }
        part = part->next;
    }
    return t;
}
void TableUtil::releaseTuple(Tuple*& tuple,TableMeta* meta)
{
    for(int k=0;k<meta->fieldNum;k++)
    {
        if(tuple->column[k].data!=0)
        {
            delete tuple->column[k].data;
            tuple->column[k].data = 0;
        }
    }
    delete[] tuple->column;
    tuple->column = 0;
    delete tuple;
    tuple = 0;
}
