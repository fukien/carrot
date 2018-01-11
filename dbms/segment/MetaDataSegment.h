#ifndef METADATASEGMENT_H_INCLUDED
#define METADATASEGMENT_H_INCLUDED

#include "../common.h"
#include "../buffer/BufferManager.h"
#include "DirectorySegment.h"
#include "../table/meta.h"
#include "../table/TableUtil.h"
/**
 * the fieldmeta si 72Byte～136Byte，
 * 7K can have around 100 field.
 * so we think metaDataSegment only have one page.
 */
class MetaDataSegment
{
public:
    MetaDataSegment(BufferManager* mgr,DirectorySegment* dir);
    ~MetaDataSegment();
    bool createOrUpdate();
    TableMeta* getMetaData();
    void deleteFieldList();
private:
    BufferManager* manager;
    DirectorySegment* dir;
    TableMeta* tableMeta;
    Addr metaPageAddr;

    void transTableMetaToFrame(BufferFrame* frame);
    void transFrameToTableMeta(BufferFrame* frame);
    /*
    short readFieldMeta(Page* page,int offset,Field* field,short maxOffset);
    short writeFieldMeta(Page* page,int offset,Field* field, short maxOffset);
    short readFieldPartMeta(Page* page,int offset,FieldPart* fieldPart,short maxOffset);
    short wirteFieldPartMeta(Page* page,int offset,FieldPart* fieldPart,short maxOffset);
    */
};
#endif // METADATASEGMENT_H_INCLUDED
