#include <stdio.h>
#include "first.h"
#include "second.h"

int main(int argc, char** argv)
{
  int ret = 0;
  ret += staticlibfirst_function(1);
  ret += staticlibsecond_function(2);
  ret += staticlibduplicate_function(3);
  printf("ret = %d\n", ret);
  return ret;
}
