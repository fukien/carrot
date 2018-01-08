#ifndef TABLEUTIL_H_INCLUDED
#define TABLEUTIL_H_INCLUDED

#include <cstring>

#include "../common.h"
#include "meta.h"
#include "../storage/PageUtil.h"
/**
* read/write an object to the data.
* input: data Pointer, an object , max read/write size.
* return:  data written length.
*
*/
class TableUtil
{
public:
  static short readFieldMeta(Byte *data, Field *field, short maxOffset);
  static short writeFieldMeta(Byte *data, Field *field, short maxOffset);
  static short readFieldPartMeta(Byte *data, FieldPart *fieldPart, short maxOffset);
  static short wirteFieldPartMeta(Byte *data, FieldPart *fieldPart, short maxOffset);
  static short readTuple(Byte *data, Tuple *tuple, TableMeta *meta);
  static short writeTuple(Byte *data, Tuple *tuple, TableMeta *meta);
  static short readColumn(void *target, Column *column);
  static short writeColumn(void *target, Column *column);
  /**
    * TODO:
    * 1. build/release a tuple.
    * 2. estimate the tuple size.
    *
    */
  static short estimateTupleSize(TableMeta *meta);
  static Tuple *buildTuple(TableMeta *meta);
  static void releaseTuple(Tuple *&tuple, TableMeta *meta);
};

#endif // TABLEUTIL_H_INCLUDED
