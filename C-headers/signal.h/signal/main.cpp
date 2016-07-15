#include <stdio.h>      /* printf */
#include <signal.h>     /* signal, raise, sig_atomic_t */

sig_atomic_t signaled = 0;

void my_handler (int param)
{
  signaled = 1;
}

int main ()
{
  void (*prev_handler)(int);

  prev_handler = signal (SIGINT, my_handler);

  /* ... */
  raise(SIGINT);
  /* ... */

  printf ("signaled is %d.\n",signaled);


  return 0;
}
