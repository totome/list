#include <iostream>
#include <vector>
#include "myInAndOut.hpp"
#include "list.hpp"


int main(int argc, char **argv)
{
 // std::vector<double> v;
 // v = myio::read<double>();
 // myio::write<double>(v);
  std::cout<<"!!!!!!!!!!!!!!!!\n";
  lst::List<double> l;
  std::cout<<std::endl<<"!!!!!!!!!!!!!!!!\n"<<std::endl;
  l.push_back(15);

  std::cout<<std::endl<<"!!!!!!!!!!!!!!!!\n"<<std::endl;
  std::cout<<"Elelm : "<<l.pop_back()<<std::endl;
  return 0;
}
