#ifndef HEAPSORT_H
#define HEAPSORT_H

void max_heapify( int* a, int i, int n );
void build_maxheap( int* a, int n );

/* heap sort */
void heapsort( int* a, int n );

#endif // HEAPSORT_H