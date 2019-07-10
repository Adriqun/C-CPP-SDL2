#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#define PI (3.1415926536)
typedef double (*PSINE_FUNC)(double x);

int main(int argc, char **argv)
{
   void *pHandle;
   pHandle = dlopen ("libsh.so", RTLD_LAZY);
   if(!pHandle) {
     fprintf(stderr, "1. %s\n", dlerror());
     return -1;
   }

   PSINE_FUNC func = (PSINE_FUNC)dlsym(pHandle, "runme");
   if (!func) {
     fprintf(stderr, "2. %s\n", dlerror());
     dlclose(pHandle);
     pHandle = NULL;
     return -1;
   }

   printf(" = %f\n", func(PI/2));
   dlclose(pHandle);
   pHandle = NULL;
   return 0;
 }
