#ifndef LIST_HPP
#define LIST_HPP

namespace lst
{
  template <typename T>
  class List
  {
  public:
    List(T t);
    ~List();
  };
  
  template <typename T>
  class Elem
  {
  public:
    Elem(T * elem = nullptr) : _next_elem(elem)
    {}
    
    ~Elem();
  private:
    T * _next_elem;
  };
}

#endif //LIST_HPP