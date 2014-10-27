#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include <exception>

template<typename Value>
class list
{
private:
    struct node
    {
        node * _prev;
        node * _next;
        Value _value;

        node() : _prev(nullptr), _next(nullptr) {}

        explicit node(Value v) : _prev(nullptr), _next(nullptr), _value(v) {}

        node(node * p, node * n, Value v) : _prev(p), _next(n), _value(v) {}

        ~node()
        {
            if(_next)
                delete _next;
        }
    };

    list(Value v) : _head(new node(v)), _tail(_head), _size(1) {}

public:

    static list<Value> unitList(Value v)
    {
        return std::move(list(v));
    }

    class iterator
    {
    public:
        iterator(const iterator & other)
             : _current(other._current)    {}

        iterator(node * now)
             : _current(now)    {}

        Value & operator*()
        {
            return _current->_value;
        }

        const Value & operator*()const
        {
            return _current->_value;
        }

        iterator operator++()
        {
            _current=_current->_next;
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp =*this;
            _current=_current->_next;
            return tmp;
        }

        bool operator==(iterator other)
        {
            return *this==other;
        }

        bool operator!=(iterator other)
        {
            return *this!=other;
        }

        private:
        node * _current;
    };

    const Value & operator[](int n)const;
    Value & operator[](int n);

    list(const list & other) = delete;

    list(node * h, node * t, int s): _head(h), _tail(t), _size(s) {}

    list() : _head(nullptr), _tail(_head), _size(0)
    {

    }

    list(node * n) : _head(n), _tail(n), _size(1)
    {

    }

    list(list && other)
        : _head(nullptr), _tail(nullptr), _size(0)
    {
        using std::swap;
        swap(_head, other._head);

        if(other.size()!=1)
            swap(_tail, other._tail);
        else
            _tail=_head;

        swap(_size, other._size);
    }

    list & operator=(list && other)
    {
        if(this!=&other)
        {
            this->_size=0;
            this->_head=nullptr;
            this->_tail=nullptr;
        }
        using std::swap;
        swap(_head, other._head);
        if(other.size()!=1)
            swap(_tail, other._tail);
        else
            _tail=_head;

        swap(_size, other._size);

        return *this;
    }

    ~list()
    {
        _tail=nullptr;
        _size=0;

        if(_head)
            delete _head;
    }

    const int & size() const;
    auto is_empty() const -> bool;

    auto push_front(Value)-> void;
    auto pop_front(void)  -> Value;

    auto push_back(Value)-> void;
    auto pop_back(void)  -> Value;

    auto begin() -> iterator;
    auto last_elem() -> iterator;

    auto join_front(list && other) -> void;
    auto join_back(list && other) -> void;
    auto detach_front(int n = 0) -> list<Value>;

    auto join_tail(list &&) -> void;
    auto detach_head() -> list<Value>;

    auto detach_half() -> list<Value>;
    auto detach_back(void) -> list<Value>;
    auto end() -> iterator;

private:
    node * _head;
    node * _tail;
    int _size;
};

//----begin and end------------------
template<typename Value>
auto list<Value>::begin() -> list<Value>::iterator
{
    return list<Value>::iterator(_head);
}

template<typename Value>
auto list<Value>::last_elem() -> list<Value>::iterator
{
    return list<Value>::iterator(_tail);
}

template<typename Value>
auto list<Value>::end() -> list<Value>::iterator
{
    return list<Value>::iterator(nullptr);
}

//---info abou list capacity---------

template<typename Value>
auto list<Value>::size() const -> const int &
{
    return _size;
}

template<typename Value>
auto list<Value>::is_empty() const -> bool
{
    return _size == 0;
}
//-------------------------------------


//----push and pop front----------------
template<typename Value>
auto list<Value>::push_front(Value v) -> void
{
    if(this->is_empty())
    {
        _head = new node(v);
        _tail = _head;
    }
    else
    {
        _head = new node(nullptr, _head, v);
    }
    ++_size;
}

template<typename Value>
auto list<Value>::pop_front(void) -> Value
{
    if(this->is_empty())
    {
        throw std::exception();
    }
    else
    {
        Value tmpValue = _head->_value;
        node * tmpPtr = _head;

        if(this->size()==1)
        {
            _head=nullptr;
            _tail=nullptr;
        }
        else
        {
            _head=_head->_next;
        }
        --_size
                ;
        tmpPtr->_next=nullptr;
        delete tmpPtr;
        return tmpValue;
    }
}
//------push and pop back----------------

template<typename Value>
auto list<Value>::push_back(Value v) -> void
{
    if(this->is_empty())
    {
        _head = new node(v);
        _tail = _head;
    }
    else
    {
        _tail->_next = new node(v);
        _tail->_next->_prev=_tail;
        _tail = _tail->_next;
    }
    ++_size;
}

template<typename Value>
auto list<Value>::pop_back(void) -> Value
{
    if(this->is_empty())
    {
        throw std::exception();
    }
    else
    {
        Value tmpValue = _tail->_value;
        node * tmpPtr = _tail;

        if(this->size()==1)
        {
            _head=nullptr;
            _tail=nullptr;
        }
        else if(this->size()==2)
        {
            _head->_next = nullptr;
            _tail=_head;
        }
        else
        {
            node * it = _head;
            while(it->_next->_next)
            {
                it = it->_next;
            }

            it->_next = nullptr;
            _tail = it;
        }
        --_size;
        delete tmpPtr;
        return tmpValue;
    }
}
//-----join and detach-------------------

template<typename Value>
auto list<Value>::join_tail(list<Value> && other) -> void
{
    if(is_empty())
    {
        _head=other._head;
    }
    else
    {
        _tail->_next = other._head;
        other._head->_prev = _tail;
    }

    _tail = other._tail;
    _size += other.size();

    other._tail=nullptr;
    other._size=0;
    other._head=nullptr;
}


template<typename Value>
auto list<Value>::detach_front(int n) -> list<Value>
{
    node * tmp;

    if(this->is_empty())
    {
        return list();
    }
    else
    {
        tmp=_head;

        if(this->size()==1)
        {
            _head=nullptr;
            _tail=nullptr;
        }
        else
        {
            _head->_next->_prev = nullptr;
            _head=_head->_next;
        }
        _size = _size-1;
        tmp->_next=nullptr;
    }
    return std::move(list(tmp));
}

template<typename Value>
auto list<Value>::detach_back(void) -> list<Value>
{
    node * tmp;

    if(this->is_empty())
    {
        return list();
    }
    else
    {
        tmp=_tail;

        if(this->size()==1)
        {
            _head=nullptr;
            _tail=nullptr;
        }
        else
        {
            _tail=_tail->_prev;
            _tail->_next=nullptr;
        }
        _size = _size-1;
        tmp->_prev=nullptr;
        tmp->_next=nullptr;
    }
    return std::move(list(tmp));
}

template<typename Value>
auto list<Value>::join_front(list<Value> && other) -> void
{
    if(is_empty())
    {
        _head= other._head;
        _tail= other._tail;
        _size= other._size;
    }
    else
    {
        other._tail->_next = _head;
        _head->_prev = other.tail;
        _head = other._head;
        _size += other.size();
    }

    other._tail=nullptr;
    other._size=0;
    other._head=nullptr;
}

template<typename Value>
auto list<Value>::join_back(list<Value> && other) -> void
{
    if(is_empty())
    {
        _head=other._head;
        _tail = other._tail;
        _size = other.size();
    }
    else
    {
        _tail->_next = other._head;
        other._head->_prev = _tail;
        _tail = other._tail;

        _size += other.size();
    }

    other._tail=nullptr;
    other._size=0;
    other._head=nullptr;
}


template<typename Value>
auto list<Value>::detach_head() -> list<Value>
{
    node * tmp;

    if(this->is_empty())
    {
        return list();
    }
    else
    {
        tmp=_head;

        if(this->size()==1)
        {
            _head=nullptr;
            _tail=nullptr;
        }
        else
        {
            _head->_next->_prev = nullptr;
            _head=_head->_next;
        }
        _size = _size - 1;
        tmp->_next=nullptr;
    }
    return std::move(list(tmp));
}


template<typename Value>
auto list<Value>::detach_half() -> list<Value>
{
    node * tmp;
    node * prevtmp;
    node * tmptail;

    int tmpsize= _size;

    if(this->is_empty() || this->size()==1)
    {
        return list();
    }
    else if(size()==2)
    {
        _head->_next=nullptr;
        tmp=_tail;
        _tail=nullptr;

        return list(tmp);
    }
    else
    {
        prevtmp=_head;
        tmp=_head->_next;

        int half = size()%2 + size()/2;

        for(int i=1; i<half; ++i)
        {
            tmp=tmp->_next;
            prevtmp=prevtmp->_next;
        }


        tmptail=_tail;

        _tail=prevtmp;
        _tail->_next=nullptr;
        _size=half;

        return list(tmp, tmptail, tmpsize-half);
     }
}

template <typename Value>
auto list<Value>::operator[](int n)const ->const Value &
{
    if(n>_size)
    {
        throw std::exception();
    }

    list<Value>::iterator it = begin();
    while(n>0)
    {
        ++it; --n;
    }
    return *it;
}

template <typename Value>
auto list<Value>::operator[](int n)->Value &
{
    if(n>_size or n<0)
    {
        throw std::exception();
    }

    list<Value>::iterator it = begin();
    while(n>0)
    {
        ++it; --n;
    }
    return *it;
}


#endif //LIST_HPP
