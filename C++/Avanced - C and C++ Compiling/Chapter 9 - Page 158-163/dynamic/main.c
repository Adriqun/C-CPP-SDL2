#include <stdio.h>
#include "first.h"
#include "second.h"

int main(int argc, char** argv)
{
  int ret = 0;
  ret += dynamiclibfirst_function(1);
  ret += dynamiclibsecond_function(2);
  ret += dynamiclib_duplicate_function(3);
  printf("ret = %d\n", ret);
  return ret;
}
