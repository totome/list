#ifndef MYINANDOUT_HPP 
#define MYINANDOUT_HPP
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

namespace myio
{
  template <typename T>
  auto read()-> std::vector<T> 
  {
    std::vector<T> v;    
    std::copy
      (
	std::istream_iterator<T>(std::cin),
	std::istream_iterator<T>(),
	std::back_inserter(v)
      ); 
    return v;
  }
  
  template <typename T>
  auto write(const std::vector<T> & v)-> void
  {
    for(auto x : v)std::cout<<x;
  }
}

#endif