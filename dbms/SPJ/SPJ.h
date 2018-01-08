#ifndef  SPJ_H_INCLUDED
#define SPJ_H_INCLUDED
#include "../common.h"
#include "../buffer/BufferManager.h"
#include "../table/meta.h"
#include "../segment/DirectorySegment.h"
#include "../table/TableUtil.h"
#include"../table/Table.h"
#include"../index/Index.h"
#include <string>
using namespace std;

class  OperatorType
{
    public:
     static const Byte SELECTION = 1;// for test
     static const Byte PROJECTION=2;
     static const Byte JOIN = 3;
};

typedef struct{
    int fieldNum;
    string*fieldName;
    Byte *dataType;
    void* *data; // each element is void*, one  dimension array
    int*len;
    Byte use;//label the item if have been changed, the last item is 0, all that before is 1
}SPJItem;

class SPJ{
public:
    virtual void getNext(SPJItem*item);
    virtual void getFirst(SPJItem * item);
    virtual void init(char* tablename);
    virtual void init(SPJ*spj);
    virtual void releaseSPJItem(SPJItem*item);
    virtual SPJItem* buildSPJItem();
    SPJ();
    static const Byte TABLEINITIAL=1;
    static const Byte ITERATORINITIAL=2;
    static const Byte HYBRIDINITIAL=3;
    friend class Projection;
    friend class Selection;
private:
        Tuple*currentTuple;//now the tuple
        Byte operatorType;
        Table*table;
        Index*index;
        IndexIterator* indexIterator;
};
#endif // SPJ_H_INCLUDED
