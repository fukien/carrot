#include"../PageUtil.h"
#include "../Table.h"
#include "../DirectorySegment.h"
#include "../Segment.h"
#include "../IndexSegment.h"

class Sort
{
public:
    tempnode *
    temp;
//    BufferFrame *bfm;
//    BufferManager *fbm;
    void singlesort(DirectorySegment *dtg,BufferManager *bfm,DataSegment *dts,int fid);
    Addr mutiplemerge(DirectorySegment *dtg,BufferManager *bfm);
};
