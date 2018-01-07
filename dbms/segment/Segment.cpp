#include "Segment.h"
Segment::Segment(BufferManager* mgr)
{
    this->manager=mgr;
}

Segment::~Segment()
{
    this->manager=0;
}
