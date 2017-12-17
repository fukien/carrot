#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <string>
#include <vector>
#include<fstream>
/*#include <cstring>

#include "../common.h"
#include "meta.h"
#include "../storage/PageUtil.h"**/
/**
* read and analysis the test case for the program,and organize the test process.
* input: file address
* return:  the result for the test case.
*
*/
using namespace std;

class Test
{
        private:
            ifstream *file; // 文件读操作流
        public:
            void open(char * filename);
            vector<string> findNext(vector<string>& mp);
            void close();
};

#endif // TEST_H_INCLUDED

