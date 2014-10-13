#ifndef LIST_HPP
#define LIST_HPP


namespace lst
{
  template <typename T>
  class Elem
  {
  public:
    Elem(T value, Elem<T> * elem = nullptr) : _next_elem(elem)
    {}
    
    ~Elem()
    {
      
    }
    
    void setNextElem(Elem * next_elem)
    {
	_next_elem = next_elem;
    }
    
    T getValue()
    {
      return _value;
    }
    
  private:
    T _value;
    Elem<T> * _next_elem;
  };
  
  template <typename T>
  class List
  {
  public:
    List() : head(nullptr), tail(nullptr) 
    {
      
    }
    
    ~List()
    {
      if(head)
	delete head;
      
      if(tail)
	delete tail;
    }
    
    void push_back(const T &);
    
    T pop_back(void);
    
    void push_front(const T &);
    
    void insert(const T &);
    
  private:
    Elem<T> * head;
    Elem<T> * tail;
  };
  
  template <typename T>
  void List<T>::push_back(const T & value)
  {
    auto newtail = new Elem<T>(value);
    tail -> setNextElem(newtail);
    tail = newtail;
  }
  
  template <typename T>
  void List<T>::push_front(const T & value)
  {
    T * tmp = head;
    head = new Elem<T>(value, head);
  }
  
  template <typename T>
  T List<T>::pop_back()
  {
    T value = tail->getValue();
    delete tail;
    return value;
  }
  
  template <typename T>
  void List<T>::insert(const T & value)
  {
    
  }
  
}

#endif //LIST_HPP