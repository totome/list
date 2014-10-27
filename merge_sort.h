#ifndef MERGE_SORT_H
#define MERGE_SORT_H
#include "list.hpp"

template<typename T>
auto merge_sort(list<T> && l1)-> list<T>
{
    if(l1.size()==1)
    {
        return std::move(l1);
    }
    else if(l1.size()==2)
    {
        if( *(l1.begin()) > *(l1.last_elem()))
        {
            list<T> l(l1.detach_head());
            l1.join_tail(std::move(l));
        }

       return std::move(l1);
    }
    else if(l1.size()==3)
    {
        list<T> l0 = l1.detach_front();
        list<T> l2 = l1.detach_back();


        if(l0[0] > l1[0])
        {
                if(l0[0] > l2[0])
                {
                    if(l1[0]>l2[0])
                    {
                        l2.join_tail(std::move(l1));
                        l2.join_tail(std::move(l0));
                        return std::move(l2);
                    }
                    else
                    {
                        l1.join_tail(std::move(l2));
                        l1.join_tail(std::move(l0));
                        return std::move(l1);
                    }
                }
                else
                {
                    l1.join_tail(std::move(l0));
                    l1.join_tail(std::move(l2));
                    return std::move(l1);
                }
        }
        else
        {
            if(l0[0] > l2[0])
            {
                l2.join_tail(std::move(l0));
                l2.join_tail(std::move(l1));
                return std::move(l2);
            }
            else
            {
                if(l1[0]>l2[0])
                {
                    l0.join_tail(std::move(l2));
                    l0.join_tail(std::move(l1));
                    return std::move(l0);
                }
                else
                {
                    l0.join_tail(std::move(l1));
                    l0.join_tail(std::move(l2));
                    return std::move(l0);
                }
            }
        }
     }
     else
     {
        list<T> l2(l1.detach_half());
        list<T> result;

        l1 = merge_sort(std::move(l1));
        l2 = merge_sort(std::move(l2));

        while(!l1.is_empty() && !l2.is_empty())
        {
            if(l1[0] < l2[0])
            {
                result.join_tail(std::move(l1.detach_head()));
            }
            else
            {
                result.join_tail(std::move(l2.detach_head()));
            }
        }

        if(not l1.is_empty())
        {
            result.join_tail(std::move(l1));
        }

        if(not l2.is_empty())
        {
            result.join_tail(std::move(l2));
        }
        return std::move(result);
    }
}

#endif // MERGE_SORT_H
