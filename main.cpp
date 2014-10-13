#include <iostream>
#include <vector>
#include "myInAndOut.hpp"


int main(int argc, char **argv)
{
  std::vector<int> v;
  v = myio::read<int>();
  myio::write<int>(v);
  return 0;
}
