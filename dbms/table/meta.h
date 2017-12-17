#ifndef META_H_INCLUDED
#define META_H_INCLUDED
#include "../common.h"
#define MAX_TABLE_NAME_LEN 64
#define MAX_DATA_FORMAT 64
#define MAX_VARCHAR_LEN 255
#define TUPLE_MAGIC 0x57
#define FIELD_MAGIC 0x58
#define TABLE_MAGIC 0x59
#define FIELD_PART_MAGIC 0x60
#define FIELD_META_LEN (MAX_TABLE_NAME_LEN+8)
#define TUPLE_HEAD_LEN 12
class DataTypeFlag
{
public:
    static const Byte CHAR=0x01;
    static const Byte VARCHAR = 0x02;
    static const Byte INTEGER = 0x03;
    static const Byte LONG = 0x04;
    static const Byte FLOAT = 0x05;
    static const Byte DOUBLE = 0x06;
    static const Byte DATE = 0x7;
};

class Constraint
{
public:
    static const Byte primaryKey = 0x01;
    static const Byte unique = 0x02;
    static const Byte isAddition = 0x04;
};

//4 +64 + 4
typedef struct Field
{
    //magic 0x58
    Byte fid;// 属性在表中的位置
    Byte flag;
    Byte dataType;
    char fname[MAX_TABLE_NAME_LEN];
    int len;
    char dateFormat[MAX_DATA_FORMAT];
    // not serialize
    short offsetInTuple;  // 在表中的偏移量
}Field;

typedef struct FieldPart // 封装了一组列的元数据
{
    // magic 0x60
    //Byte fieldOffset;　
    Byte fieldOffset;
    Byte partNum;
    Byte tid; // 代表表id
    Addr nextPartAddr;//下一个part的Addr
    Field* fieldList;
    FieldPart* next;//指向下一个page
} FieldPart;

typedef struct TableMeta
{
    //magic 0x59
    Byte tid;//表的id
    Byte fieldNum;//属性的数量
    Byte blockNum;//该表所占的块数
    char tname[MAX_TABLE_NAME_LEN];
    FieldPart* head; //该表指向的第一个属性组
    Addr pageNo;
}TableMeta;


class DType
{
    public:
        DType(Byte dt,int len):dataType(dt),length(len){};
        Byte getDataType(){return dataType;}
        int getLength(){return length;}
    private:
        Byte dataType;
        int length;
};

namespace DataType
{
    static const DType CHAR(DataTypeFlag::CHAR,4);
    static const DType VARCAHR(DataTypeFlag::VARCHAR,MAX_VARCHAR_LEN);
    static const DType INTEGER(DataTypeFlag::INTEGER,4);
    static const DType LONG(DataTypeFlag::LONG,8);
    static const DType FLOAT(DataTypeFlag::FLOAT,4);
    static const DType DOUBLE(DataTypeFlag::DOUBLE,8);
    static const DType Date(DataTypeFlag::DATE,8);
}

//static Byte getTypeLength(int dataTypeFlag)
static Byte getTypeLength(Byte dataTypeFlag) // seems to be a bug
{
    switch(dataTypeFlag)
    {
        case DataTypeFlag::CHAR:
            return 4;
            break;
        case DataTypeFlag::DATE:
            return 16;
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

typedef struct Column
{
   // no magic
   Field* field;
   Byte* data;
}Column;

typedef struct Tuple
{
  //  ushort magic;//0x57
    Byte tid; //表编号
    PageAddr offset;//该元组在表中的偏移量
    long long int timeStamp;
    Column* column;// tuple 有多少个column

    TableMeta* meta;
    Addr tupleAddr;  //该元组在磁盘中的地址
}Tuple;
#endif // META_H_INCLUDED
