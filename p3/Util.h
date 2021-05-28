#ifndef _UTIL_H_
#define _UTIL_H_

#include <iostream>

using namespace std;

enum Error{
  ERR_OPTION,
  ERR_EMPTY,
  ERR_LIST_NAME,
  ERR_TASK_NAME,
  ERR_DATE,
  ERR_TIME,
  ERR_ID,
  ERR_PROJECT_NAME
};

class Util{
  public:
    static void error(Error e);
};

#endif
