#include "DataUtil.h"
#include "../table/meta.h"
#include <cstdlib>
#include <cstdio>
void DataUtil::parseFromString(void *data, char *str, Byte dataTypeFlag, int len)
{
    double *a1 = 0;
    float *a2 = 0;
    int *a3 = 0;
    long long *a4 = 0;
    switch (dataTypeFlag)
    {
    case DataTypeFlag::DOUBLE:
        a1 = reinterpret_cast<double *>(data);
        *a1 = atof(str);
        break;
    case DataTypeFlag::FLOAT:
        a2 = reinterpret_cast<float *>(data);
        *a2 = atof(str);
        break;
    case DataTypeFlag::INTEGER:
        a3 = reinterpret_cast<int *>(data);
        *a3 = atoi(str);
        break;
    case DataTypeFlag::LONG:
        a4 = reinterpret_cast<long long *>(data);
        *a4 = atoll(str);
        break;
    case DataTypeFlag::CHAR:
        memcpy(data, str, len);
        break;
    case DataTypeFlag::VARCHAR:
        memcpy(data, str, len);
        break;
    case DataTypeFlag::DATE:
        break;
    }
}
void DataUtil::toString(char *str, void *data, Byte dataTypeFlag)
{
    float af = 0.0;
    double ad = 0.0;
    int ai = 0.0;
    long al = 0l;
    switch (dataTypeFlag)
    {
    case DataTypeFlag::DOUBLE:
        memcpy(&ad, data, getTypeLength(dataTypeFlag));
        sprintf(str, "%llf", data);
        break;
    case DataTypeFlag::FLOAT:
        memcpy(&af, data, getTypeLength(dataTypeFlag));
        sprintf(str, "%f", af);
        break;
    case DataTypeFlag::INTEGER:
        memcpy(&ai, data, getTypeLength(dataTypeFlag));
        sprintf(str, "%d", ai);
        break;
    case DataTypeFlag::LONG:
        memcpy(&al, data, getTypeLength(dataTypeFlag));
        sprintf(str, "%lld", al);
        break;
    case DataTypeFlag::CHAR:
        sprintf(str, "%s", data);
        break;
    case DataTypeFlag::VARCHAR:
        sprintf(str, "%s", data);
        break;
    case DataTypeFlag::DATE:
        break;
    }
}
void DataUtil::str2col(char *str, Column &col)
{
    parseFromString(col.data, str, col.field->dataType, col.field->len);
}
void DataUtil::col2str(Column &col, char *str)
{
    toString(str, col.data, col.field->dataType);
}
short DataUtil::col2data(Column &column, void *target)
{
    TableUtil::readColumn(target, &column);
}
short DataUtil::data2col(void *dat, Column &column)
{
    TableUtil::writeColumn(dat, &column);
}

int DataUtil::cmpData(Byte *data1, Byte *data2, int dataType, int dataLen)
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
        if (ad1 == ad2)
            return 0;
        return (ad1 - ad2) > 0.0 ? 1 : -1;
        break;
    case DataTypeFlag::FLOAT:
        memcpy(&af1, data1, dataLen);
        memcpy(&af2, data2, dataLen);
        //   printf("compare %f and %f result %d\n",af1,af2,(af1-af2)>0.0?1:-1);
        if (af1 == af2)
            return 0;
        return (af1 - af2) > 0.0 ? 1 : -1;
        break;
    case DataTypeFlag::INTEGER:
        memcpy(&ai1, data1, dataLen);
        memcpy(&ai2, data2, dataLen);
        if (ai1 == ai2)
            return 0;
        //printf("cmp %d %d\n",ai1,ai2);
        return (ai1 - ai2) > 0 ? 1 : -1;
        break;
    case DataTypeFlag::LONG:
        memcpy(&al1, data1, dataLen);
        memcpy(&al2, data2, dataLen);
        if (al1 == al2)
            return 0;
        return (al1 - al2) > 0 ? 1 : -1;
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
