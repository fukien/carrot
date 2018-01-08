#ifndef SEGMENT_H_INCLUDED
#define SEGMENT_H_INCLUDED
#include "../common.h"
#include "../buffer/BufferManager.h"

class SegmentType
{
public:
    static const  Byte EmptySeg=0x00; // A Segment type for unallocated.
    static const  Byte DirectorySeg=0x01; // A Segment to list all block uses. => required.
    static const  Byte MetaDataSeg=0x02; // A Segment to store meta data. =>required
    static const  Byte StatisticsSeg=0x03; //A Segment to store statistics
    static const  Byte DataSeg=0x04;// A Segment to store the data => required
    static const  Byte BlobSeg=0x05;// A Segment to store the big data  => maybe required
    static const  Byte IndexSeg=0x06;// A Segment to Store the index. => required
    static const  Byte mask = 0x0f;
};

class PageStatus
{
    public:
        static const  Byte EmptyPage = 0x00;
        static const  Byte HalfPage =0x10;
        static const  Byte FullPage = 0x20;
        static const  Byte mask = 0xf0;
};

class Segment
{
    public:
        Segment(BufferManager* mgr);
        ~Segment();
    protected:
        BufferManager* manager;
        BufferFrame* rootPage;
        virtual void initRootPage()=0;
};

#endif // SEGMENT_H_INCLUDED
