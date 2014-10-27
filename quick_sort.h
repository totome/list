#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "list.hpp"

template<typename V>
auto quick_sort(list<V> & T, int left, int right) -> void
{
    V pivot;
    int i = left,  j = left;

    pivot = T[(right+left)/2];
    T[(right+left)/2] = T[right];
    T[right]=pivot;

    using std::swap;

    while(i < right)
    {
        if(T[i] < pivot)swap(T[i],T[j++]);
        ++i;
    }

    T[right]=T[j];
    T[j]=pivot;

    if(left < j-1)quick_sort(T, left, j-1);
    if(j+1 < right)quick_sort(T, j + 1, right);
}

#endif // QUICK_SORT_H
