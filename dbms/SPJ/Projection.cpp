#include "Projection.h"
#include <cstdio>
#include <iostream>

using namespace std;

Projection::Projection(int type, int initial) : SPJ()
{
        this->operatorType = type;
        this->table = 0;
        this->currentTuple = 0;
        this->initialType = initial;
        this->columns = 0;
        this->dataType = 0;
        this->spj = 0;
        this->fieldList = 0;
        this->fieldflag = false;
}
void Projection::destroy()
{
        if (this->initialType == SPJ::TABLEINITIAL)
        {
                if (this->currentTuple != 0)
                        this->table->releaseEmptyTuple(this->currentTuple);
                delete (this->dataType);
                delete (this->fieldList);
        }
        else
        {
                delete (this->dataType);
                delete (this->fieldList);
        }
}
void Projection::initProjection(Table *table, string columnName[], int columnNum)
{
        this->table = table;
        if (columnNum == -1)
        {
                columnNum = this->table->getTableMeta()->fieldNum;
                this->fieldList = new int[columnNum];
                for (int i = 0; i < columnNum; i++)
                        this->fieldList[i] = i;
                this->fieldflag = true;
        }
        else
        {
                this->fieldList = new int[columnNum];
        }
        this->columns = columnName;
        this->columnNum = columnNum;
        this->dataType = new Byte[columnNum];
}

void Projection::releaseSPJItem(SPJItem *item)
{
        for (int i = 0; i < item->fieldNum; i++)
        {
                delete item->data[i];
        }
        delete item->data;
        delete (item->dataType);
        //  delete(item->fieldName);
        delete (item->len);
        delete (item);
}

SPJItem *Projection::buildSPJItem()
{
        SPJItem *item = new SPJItem();
        item->fieldNum = this->columnNum;
        item->fieldName = new string[this->columnNum];
        item->data = new void *[this->columnNum];
        for (int i = 0; i < item->fieldNum; i++)
                item->data[i] = 0;
        item->len = new int[this->columnNum];
        item->dataType = new Byte[this->columnNum];
        item->use = 0;
        return item;
}
void Projection::getNext(SPJItem*item){

        item->use=0;
        if(this->initialType==SPJ::TABLEINITIAL){
            Tuple *tuple=this->currentTuple;
            Addr oldAddr = tuple->tupleAddr;
            table->findNextTuple(this->currentTuple,tuple);
            //Addr newAddr = tuple->tupleAddr;
           // printf("old:%d new:%d\n",oldAddr,newAddr);
            if(tuple->tupleAddr!=0&&tuple->tupleAddr!=oldAddr){
                 fillItem(item,tuple);
            }
           // printf("fuck\n");
            //table->releaseEmptyTuple(this->currentTuple);
            //this->currentTuple=tuple;
        }else if(this->initialType==SPJ::ITERATORINITIAL){
               SPJItem*sourceItem =this->spj->buildSPJItem();
               spj->getNext(sourceItem);
               if(sourceItem->use!=0)
               fillItem(item,sourceItem);
               this->spj->releaseSPJItem(sourceItem);
        }
}
void Projection::getFirst(SPJItem *item)
{
        item->use = 0;
        if (this->initialType == SPJ::TABLEINITIAL)
        {
                Tuple *tuple = table->buildEmptyTuple();
                this->table->findFirstTuple(tuple);
                if (tuple->tupleAddr != 0)
                        fillItem(item, tuple);
                this->currentTuple = tuple;
        }
        else if (this->initialType == SPJ::ITERATORINITIAL)
        {
                SPJItem *sourceItem = this->spj->buildSPJItem();
                spj->getFirst(sourceItem);
                if (this->columnNum == -1)
                {
                        item = sourceItem;
                }
                else if (sourceItem->use != 0)
                {
                        fillItem(item, sourceItem);
                        this->spj->releaseSPJItem(sourceItem);
                }
        }
}
void Projection::fillItem(SPJItem *item, Tuple *tuple)
{
        int fieldNum = tuple->meta->head->partNum;
        if (this->fieldflag == false)
        {
                map<string, int> mp;
                for (int i = 0; i < this->columnNum; i++)
                {
                        mp[this->columns[i]] = 0;
                }
                int cnt = 0;
                for (int i = 0; i < fieldNum; i++)
                {
                        string ss = tuple->column[i].field->fname;
                        if (mp.count(ss) > 0)
                        {
                                if (item->data[cnt] == 0)
                                        item->data[cnt] = new Byte[tuple->column[i].field->len];
                                memcpy(item->data[cnt], tuple->column[i].data, tuple->column[i].field->len);
                                item->fieldName[cnt] = ss;
                                item->len[cnt] = tuple->column[i].field->len;
                                this->fieldList[cnt] = i;
                                item->dataType[cnt++] = tuple->column[i].field->dataType;
                        }
                }
                this->fieldflag = true;
        }
        else
        {
                for (int i = 0; i < this->columnNum; i++)
                {
                        if (item->data[i] == 0)
                                item->data[i] = new Byte[tuple->column[this->fieldList[i]].field->len];
                        memcpy(item->data[i], tuple->column[this->fieldList[i]].data, tuple->column[this->fieldList[i]].field->len);
                        item->fieldName[i] = this->columns[i];
                        item->len[i] = tuple->column[this->fieldList[i]].field->len;
                        item->dataType[i] = tuple->column[this->fieldList[i]].field->dataType;
                }
        }
        item->use = 1;
}
void Projection::fillItem(SPJItem *item, SPJItem *sourceItem)
{
        item->fieldNum = sourceItem->fieldNum;
        if (this->fieldflag == false)
        {
                map<string, int> mp;
                for (int i = 0; i < this->columnNum; i++)
                {
                        mp[this->columns[i]] = 0;
                }
                int cnt = 0;
                for (int i = 0; i < item->fieldNum; i++)
                {
                        string ss = sourceItem->fieldName[i];
                        if (mp.count(ss) > 0)
                        {
                                if (item->data[cnt] == 0)
                                        item->data[cnt] = new Byte[sourceItem->len[i]];
                                memcpy(item->data[cnt], sourceItem->data[i], sourceItem->len[i]);
                                item->dataType[cnt] = sourceItem->dataType[i];
                                item->fieldName[cnt] = sourceItem->fieldName[i];
                                this->fieldList[cnt] = i;
                                item->len[cnt++] = sourceItem->len[i];
                        }
                }
                this->fieldflag = true;
        }
        else
        {
                for (int i = 0; i < this->columnNum; i++)
                {
                        if (item->data[i] == 0)
                                item->data[i] = new Byte[sourceItem->len[this->fieldList[i]]];
                        memcpy(item->data[i], sourceItem->data[this->fieldList[i]], sourceItem->len[this->fieldList[i]]);
                        item->dataType[i] = sourceItem->dataType[this->fieldList[i]];
                        item->fieldName[i] = sourceItem->fieldName[this->fieldList[i]];
                        item->len[i] = sourceItem->len[this->fieldList[i]];
                }
        }
        item->use = sourceItem->use;
}
void Projection::initProjection(SPJ *spj, string columnName[], int columnNum)
{
        this->spj = spj;
        this->columns = columnName;
        this->columnNum = columnNum;
        this->dataType = new Byte[columnNum];
        this->fieldList = new int[columnNum];
}
