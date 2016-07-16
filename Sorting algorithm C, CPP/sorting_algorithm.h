#pragma once

namespace sorting
{
    int max( int x, int y );
    void merge_helper( int* input, int left, int right, int* scratch );

    void max_heapify( int* a, int i, int n );
    void build_maxheap( int* a, int n );

    void countSort( int* arr, int n, int exp );

    void bitonic_helper( int* data, int n, int low, int dir );

    /* quick sort */
    void quick( int *tab, int left, int right );

    /* merge sort */
    void merge( int* input, int size );

    /* heap sort */
    void heap( int* a, int n );

    /* shell sort */
    void shell( int* tab, int n );

    /* counting sort */
    void counting( int* tab, int n );

    /* radix sort */
    void radix( int* arr, int n );

    /* bitonic sort */
    void bitonic( int* data, int n, int low, int buf );

    /* cocktail sort */
    void cocktail( int* arr, int len );

    /* bubble sort */
    void bubble( int* tab, int n );

    /* selection sort */
    void selection( int* tab, int n );

    /* insertion sort */
    void insertion( int* tab, int n );
};
