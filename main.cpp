#include <iostream>
#include <vector>
#include "myInAndOut.hpp"
#include "list.hpp"


int main()
{
    double tmp;
    list<double> l;

    while(std::cin)
    {
        std::cin>>tmp;
        l.push_back(tmp);
    }
    l.pop_back();

    l = merge_sort(std::move(l));

    while(!l.is_empty())
    {
        std::cout<<l.pop_front()<<std::endl;
    }
    return 0;
}
