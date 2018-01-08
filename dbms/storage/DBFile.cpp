#include "DBFile.h"
#include <cstdlib>
#include <cstdio>
#ifdef DEBUG
#include <cstdlib>
#include <cstdio>
#endif // DEBUG
bool DBFile::open(const char *dbname, bool readOnly)
{
    int umasks = umask(0);
    if (!readOnly)
    {
        fd = ::open(dbname, O_CREAT | O_EXCL, 0x700);
    }
    if (fd < 0)
        fd = ::open(dbname, readOnly ? O_RDONLY : O_RDWR);
    if (fd < 0)
    {
        fd = 0;
#ifdef DEBUG
        printf("open file failure");
#endif // DEBUG
        return false;
    }
    size = lseek(fd, 0, SEEK_END);
    return true;
}

void DBFile::close()
{
    if (fd != 0)
    {
        flush();
        ::close(fd);
    }
}

void DBFile::read(void *block, Addr offset, int len)
{
    if (offset + len >= size)
    {
        int to = offset + len;
        int threshold = INCREASE_THRESHOLD * PAGE_SIZE;
        if (to - size < threshold)
        {

            if ((to & (~PAGE_MASK)) != to)
            {
                to = (to & (~PAGE_MASK)) + PAGE_SIZE;
            }
            int increment = to - size;
            bool suc = this->growing(increment);
#ifdef DEBUG
            if (!suc)
            {
                printf("read size is too large, and increased failed! addr= %lld, len = %d increament = %d\n", offset, len, increment);
                // printStack();
            }
#endif // DEBUG
        }
        else
        {
#ifdef DEBUG
            printf("read size is too large, and exceed the increase threshold! addr= %lld, len = %d\n", offset, len);
//printStack();
#endif // DEBUG
            return;
        }
    }
    pread(fd, block, len, offset);
}

void DBFile::write(void *block, Addr offset, int len)
{
    if (offset + len >= size)
    {
        int to = offset + len;
        int threshold = INCREASE_THRESHOLD * PAGE_SIZE;
        if (to - size < threshold)
        {

            if ((to & (~PAGE_MASK)) != to)
            {
                to = (to & (~PAGE_MASK)) + PAGE_SIZE;
            }
            int increment = to - size;
            bool suc = this->growing(increment);
#ifdef DEBUG
            if (!suc)
                printf("write size is too large, and increased failed! addr= %lld, len = %d increament = %d\n", offset, len, increment);
#endif // DEBUG
        }
        else
        {
#ifdef DEBUG
            printf("write size is too large, and exceed the increase threshold! addr= %lld, len = %d\n", offset, len);
#endif // DEBUG
            return;
        }
    }
    size_t wt = pwrite(fd, block, len, offset);
#ifdef DEBUG
    // printf("pwrite size %d offset %d, len %d\n",wt,offset,len);
#endif // DEBUG
}
bool DBFile::flush()
{
    return fdatasync(fd) == 0;
}
bool DBFile::growing(int increment)
{
    // fflush(fd);
    int res = ftruncate(fd, size + increment);
    if (res == 0)
    {
        size = size + increment;
        return true;
    }
    return false;
}
