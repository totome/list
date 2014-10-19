#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>

template<typename Value>
class list
{
private:
    struct node
    {
        node * _next;
        Value _value;
        node() : _next(nullptr) {}
        explicit node(Value v) : _next(nullptr), _value(v) {}
        node(node * ptr, Value v) : _next(ptr), _value(v) {}
        ~node()
        {
            if(_next)
                delete _next;
        }
    };

public:

    class iterator
    {
    public:
        iterator(const iterator & other)
            : _previous(other._previous),
              _current(other._current)
        {

        }

        iterator(node * prev, node * now)
            : _previous(prev),
              _current(now)
        {

        }
        node & operator*()
        {
            return *_current;
        }

        node * operator->()
        {
            return _current;
        }

        iterator operator++()
        {
            _previous=_current;
            _current=_current->_next;
            return this;//pre
        }

        iterator operator++(int)
        {
            //post
        }

    private:
        node * _previous;
        node * _current;
    };

    list(const list & other) = delete;

    list(node * h, node * t, int s): _head(h), _tail(t), _size(s) {}

    list() : _head(nullptr), _tail(_head), _size(0)
    {

    }

    list(node * n) : _head(n), _tail(n), _size(1)
    {

    }

    list(list && other)
        : _size(0), _head(nullptr), _tail(nullptr)
    {
        using std::swap;
        swap(_size, other._size);
        swap(_head, other._head);
        swap(_tail, other._tail);
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
        swap(_size, other._size);
        swap(_head, other._head);
        swap(_tail, other._tail);

        return *this;
    }

    ~list()
    {
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
    auto end() -> iterator;
    auto join_tail(list<Value> &&) -> void;
    auto detach_head() -> list<Value>;
    auto detach_half() -> list<Value>;
private:
    node * _head;
    node * _tail;
    int _size;
};

//----begin and end------------------
template<typename Value>
auto list<Value>::begin() -> list<Value>::iterator
{
    return list<Value>::iterator(nullptr, _head);
}

template<typename Value>
auto list<Value>::end() -> list<Value>::iterator
{
    return list<Value>::iterator(_tail, nullptr);
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
        _head = new node(_head, v);
    }
    ++_size;
}

template<typename Value>
auto list<Value>::pop_front(void) -> Value
{
    if(this->is_empty())
    {
        //throw
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
        _tail = _tail->_next;
    }
    ++_size;
}

template<typename Value>
auto list<Value>::pop_back(void) -> Value
{
    if(this->is_empty())
    {
        //throw
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
    this->_tail->_next = other._head;
    this->_tail = other._tail;
    this->_size += other.size();

    other._size=0;
    other._tail=nullptr;
    other._head=nullptr;
}

template<typename Value>
auto list<Value>::detach_head() -> list<Value>
{
    node * tmp;

    if(this->is_empty())
    {
        //throw
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
            _head=_head->_next;
        }
        --_size;
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

    if(this->is_empty())
    {
        //throw
    }
    else
    {
        if(this->size()==1)
        {
             tmp=_head;
            _head=nullptr;
            _tail=nullptr;
            return std::move(list(tmp));
        }
        else
        {
            prevtmp=_head;
            tmp=_head->_next;

            int half = size()/2;

            for(int i=1; i<half; ++i)
            {
                tmp=tmp->_next;
                prevtmp=prevtmp->_next;
            }

            prevtmp->_next=nullptr;

            tmptail=_tail;
            _tail=prevtmp;
            _size=half;

            return list(tmp, tmptail, tmpsize-half);
        }
    }
}


//---------------------------------------

#endif //LIST_HPP
