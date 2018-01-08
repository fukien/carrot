#ifndef DBFILE_H_INCLUDED
#define DBFILE_H_INCLUDED
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../common.h"

#define INCREASE_THRESHOLD 100
/**
 * 数据文件类
 * 负责数据IO、以及控制数据的增长(宏定义INCREASE_THRESHOLD)
 *
 */
class DBFile
{
public:
  bool open(const char *dbname, bool readOnly);
  virtual void read(void *block, Addr offset, int len);
  //virtual void write(void* block,　Addr offset, int len);
  virtual void write(void *block, Addr offset, int len);
  virtual bool growing(int size);
  virtual bool flush();
  virtual void close();
  int size;

private:
  int fd;
};

#endif // DBFILE_H_INCLUDED
