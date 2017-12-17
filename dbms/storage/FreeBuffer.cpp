#include "FreeBuffer.h"
Buffer* FreeBuffer::allocBuffer()
{
    Buffer* ret = 0;
    if(head)
    {
        ret = head;
        head = head->next;
        ret->next = 0;
        return ret;
    }
    else
    {
        return newBuffer();
    }
}

FreeBuffer::FreeBuffer()
{
    head = 0;
}

FreeBuffer::~FreeBuffer()
{
    while(head!=0)
    {
        Buffer* tmp = head->next;
        delete head;
        head = tmp;
    }
}
void FreeBuffer::freeBuffer(Buffer* buffer)
{
    if(head=0)
    {
        head = buffer;
        buffer->next=0;
    }else
    {
        buffer->next = head;
        head = buffer;
    }
}

Buffer* FreeBuffer::newBuffer()
{
    Buffer* buffer = new Buffer();
    buffer->page = 0;
    buffer->state = 0;
    buffer->next = 0;
    return buffer;
}
