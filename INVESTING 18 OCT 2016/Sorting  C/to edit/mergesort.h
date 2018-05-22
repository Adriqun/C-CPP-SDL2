#ifndef MERGESORT_H
#define MERGESORT_H

int max( int x, int y );
void merge_helper( int* tab, int s, int mid, int e );

/* merge sort */
void mergesort( int* tab, int s, int e );

#endif // MERGESORT_H