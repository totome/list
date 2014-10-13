#ifndef LIST_HPP
#define LIST_HPP

namespace lst
{
  template <typename T>
  class List
  {
  public:
    List();
    ~List();
    void push_back(const T &);
    void push_back(T &&);
    
    void push_front(const T &);
    void push_front(T &&);
    
    void insert(const T &);
    void insert(T &&);
    
  private:
    
  };
  
  template <typename T>
  void List<T>::push_back(const T & value)
  {
    
  }
  
  template <typename T>
  void List<T>::push_back(T && rvalue)
  {
    
  }
  
  template <typename T>
  void List<T>::push_front(const T & value)
  {
    
  }
  
  template <typename T>
  void List<T>::push_front(T && rvalue)
  {
    
  }
  
  template <typename T>
  void List<T>::insert(const T & value)
  {
    
  }
  
  template <typename T>
  void List<T>::insert(T && rvalue)
  {
    
  }
  
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