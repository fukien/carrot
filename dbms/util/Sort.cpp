#include <stdio.h>
#include "../storage/PageUtil.h"
#incldue "Sort.h"
#include "../buffer/BufferManager.h"
#include "../segment/DataSegment.h"
#include "../segment/DirectorySegment.h"
#include "../segment/MetaDataSegment.h"
#include "../segment/Segment.h"
#include "../segment/TempSegment.h"

void Sort::orderpage(DirectorySegment *dtg, BufferManager *bfm, DataSegment *dts, int fid)
{
    //tempSegment temp=new tempSegment();
    Tuple *tuple = dts->buildEmptyTuple();
    dts->findFirstTuple(tuple);
    int i = 0;
    while (tuple->tupleAddr > 0)
    {
        //            if(this->temp->node->length==100ĵ)
        //            {
        //
        //            }
        //                break;
        tempitem *item = &this->temp->node->arr[i++];
        //Byte data[8];
        TableUtil::readColumn(item->value, &tuple->column[fid]);
        //memcpy(item->value,data);
        item->keyaddr = tuple->tupleAddr;
        temp->node->type = tuple->column[fid]->field->dataType;
        temp->node->length++;
        if (temp->length == 100)
        {
            int l = temp->node->length;
            for (int i = 1; i < l; i++)
            {
                int k;
                k = two - waysort(temp->node->arr, 0, i, temp->node->type);
                for (int j = l; j > k; j--)
                {
                    tempitem *item0 = &temp->node->arr[j];
                    tempitem *item1 = &temp->node->arr[j - 1];
                    //temp->node->arr[j]=temp->node->arr[j-1];
                    item0.keyaddr = item1.keyaddr;
                    item0.value = item1.value;
                }
            }
            BufferFrame *frame = new BufferFrame();
            transTemptoFrame(frame, temp);
            bfm->finishRead(frame);
            temp->next = creatTemp(bfm, dtg, dts);
            temp = temp->next;
        }
        dts->findNextTuple(tuple, tuple);
        if (tuple->tupleAddr == item->keyaddr)
        {
            break;
        }
    }
    //     int l=temp->node->length;
    //    for(int i=1;i<l;i++)
    //    {
    //        int k;
    //        k=two-waysort(temp->node->arr,0,i,temp->node->type);
    //        for(int j=l;j>k;j--)
    //        {
    //            tempitem *item0=&temp->node->arr[j];
    //            tempitem *item1=&temp->node->arr[j-1];
    //            //temp->node->arr[j]=temp->node->arr[j-1];
    //            item0.keyaddr=item1.keyaddr;
    //            item0.value=item1.value;
    //        }
    //    }
    //    BufferManager *manger=new BufferManager();
    //    BufferFrame* frame = new BufferFrame();
    //    transTemptoFrame(frame,temp);
    //    manager->finishRead(frame);
}
int two - waysort(tempitem *arr, int l, int r, int n, int type)
{
    if (l == r)
        return l;
    if (n > 0)
    {
        // if(a[n]==a[(l+r)/2])
        //   return (l+r)/2;
        //if(cmpData(&arr[n].value,&arr[(l+r)/2].value,type,getTypeLength(type))==-1)
        if (cmpData(&arr[n].value, &arr[(l + r) / 2].value, type, getTypeLength(type)) == -1)
        {
            two - waysort(arr, l, (l + r) / 2, n, type);
        }
        else
        {
            two - waysort(arr, (l + r) / 2, r, n, type);
        }
    }
}

Addr Sort::mutiplemerge(DirectorySegment *drt, BufferManager *bfm)
{
    Addr tempaddr = drt->findFirstBlock(TempMagic);
    BufferFrame *frame = 0;
    frame = bfm->requestPageForRead(tempaddr);
    tempnode *temp1 = new tempnode();
    transFrametoTemp(frame, temp1);
    tempaddr = temp1->next;
    frame = bfm->requestPageForRead(tempaddr);
    tempnode *temp2;
    transFrametoTemp(frame, temp2);
    //    tempnode *tempsort;
    //    Addr addroftemp=creatTemp(bfm,drt);
    //    frame=bfm->requestPageForWrite(addroftemp);
    //    transFrametoTemp(frame,tempsort);
    tempSegment *tempsegment;
    tempsegment = new tempSegment();
    Addr temaddr = tempsegment.creatTemp(bfm, drt);
    int point1, point2;
    point1 = 0;
    point2 = 0;
    tempitem *arr1, *arr2;
    arr1 = temp1->arr;
    arr2 = temp2->arr;
    int flag = 0;
    while (point1 < temp1->length && point2 < temp2->length)
    {
        if (arr1[point1].value < arr2[point2].value)
        {
            if (point1 + point2 >= 100)
            {
                flag = 1;
                break;
            }
            memcpy(tempsort->arr[point1 + point2], arr1[point1]);
            point1++;
        }
        else
        {
            if (point1 + point2 >= 100)
            {
                flag = 1;
                break;
            }
            memcpy(tempsort->arr[point1 + point2], arr2[point2]);
            point2++;
        }
    }
    if (flag == 1)
    {
    }
}

int cmpData(Byte *data1, Byte *data2, int dataType, int dataLen)
{
    if (dataLen == 0)
        dataLen = getTypeLength(dataType);
    double ad1 = 0, ad2 = 0;
    float af1 = 0, af2 = 0;
    int ai1 = 0, ai2 = 0;
    long al1 = 0, al2 = 0;
    char ac1[255], ac2[255];
    if (dataLen > 255)
        dataLen = 255;
    switch (dataType)
    {
    case DataTypeFlag::DOUBLE:
        memcpy(&ad1, data1, dataLen);
        memcpy(&ad2, data2, dataLen);
        return ad1 - ad2 > 0.0 ? 1 : -1;
        break;
    case DataTypeFlag::FLOAT:
        memcpy(&af1, data1, dataLen);
        memcpy(&af2, data2, dataLen);
        return af1 - af2 > 0.0 ? 1 : -1;
        break;
    case DataTypeFlag::INTEGER:
        memcpy(&ai1, data1, dataLen);
        memcpy(&ai2, data2, dataLen);
        return ai1 - ai2 > 0 ? 1 : -1;
        break;
    case DataTypeFlag::LONG:
        memcpy(&al1, data1, dataLen);
        memcpy(&al2, data2, dataLen);
        return al1 - al2 > 0 ? 1 : -1;
        break;
    case DataTypeFlag::DATE:
        return 8;
        break;
    case DataTypeFlag::CHAR:
    case DataTypeFlag::VARCHAR:
        memcpy(ac1, data1, dataLen);
        memcpy(ac2, data2, dataLen);
        return strcmp(ac1, ac2);
        break;
    }
}

static Byte getTypeLength(int dataTypeFlag)
{
    switch (dataTypeFlag)
    {
    case DataTypeFlag::CHAR:
        return 4;
        break;
    case DataTypeFlag::DATE:
        return 8;
        break;
    case DataTypeFlag::DOUBLE:
        return 8;
        break;
    case DataTypeFlag::FLOAT:
        return 4;
        break;
    case DataTypeFlag::INTEGER:
        return 4;
        break;
    case DataTypeFlag::LONG:
        return 8;
        break;
    case DataTypeFlag::VARCHAR:
        return 255;
        break;
    }
}
