#ifndef DATAUTIL_H_INCLUDED
#define DATAUTIL_H_INCLUDED
#include <stdlib.h>
#include <cstdio>
#include "../common.h"
#include "../table/meta.h"
#include "../table/TableUtil.h"

//typedef unsigned char Byte; // %u
class DataUtil
{
    public:
        static void parseFromString(void * data, char* str, Byte dataTypeFlag, int len);
        static void toString( char* str, void* data, Byte dataTypeFlag);
        static void str2col(char* str, Column& col);
        static void col2str(Column& col, char* str);
        static short col2data(Column& column, void* target);
        static short data2col(void* dat, Column& column);
        static int cmpData(Byte* data1, Byte* data2, int dataType, int dataLen=0);
};

#endif // DATAUTIL_H_INCLUDED
