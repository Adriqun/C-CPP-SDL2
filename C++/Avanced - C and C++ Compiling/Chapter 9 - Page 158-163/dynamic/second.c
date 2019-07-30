#include <stdio.h>

static int local_function(int x)
{
  printf("second: %s\n", __FUNCTION__);
  return 0;
}

int dynamiclibsecond_function(int x)
{
  printf("%s\n", __FUNCTION__);
  local_function(x);
  return x + 1;
}

int dynamiclib_duplicate_function(int x)
{
  printf("%s\n", __FUNCTION__);
  local_function(x);
  return x + 2;
}
