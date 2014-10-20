#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include <exception>
#include <iterator>

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
             : _current(other._current)    {}

        iterator(node * now)
             : _current(now)    {}

        Value & operator*()
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
            auto tmp =*this;
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
        _head = new node(_head, v);
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
    }

    _tail = other._tail;
    _size += other.size();

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

//---------------------------------------------------------------
//---------------------MERGE SORT--------------------------------

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
        list<T> l0 = l1.detach_head();
        list<T> l2 = l1.detach_head();


        if(*(l0.begin()) > *(l1.begin()))
        {
                if(*(l0.begin())>*(l2.begin()))
                {
                    if(*(l1.begin())>*(l2.begin()))
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
            if(*(l0.begin()) > *(l2.begin()))
            {
                l2.join_tail(std::move(l0));
                l2.join_tail(std::move(l1));
                return std::move(l2);
            }
            else
            {
                if(*(l1.begin())>*(l2.begin()))
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
            if(*(l1.begin()) < *(l2.begin()))
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



#endif //LIST_HPP
