#ifndef BITONICSORT_H
#define BITONICSORT_H

void bitonic_helper( int* data, int n, int low, int dir );

/* bitonic sort */
void bitonicsort( int* data, int n, int low, int buf );

#endif // BITONICSORT_H