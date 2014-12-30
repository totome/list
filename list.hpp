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
        std::unique_ptr<Value> _value;

        node() : _prev(nullptr), _next(nullptr) {}

        explicit node(Value v) : _prev(nullptr), _next(nullptr), _value(new Value(v)) {}

        node(node * p, node * n, Value v) : _prev(p), _next(n), _value(new Value(v)) {}

        node(node * p, node * n) : _prev(p), _next(n) {}

        bool hasValue(){return _value;}

        operator bool(){return _value;}

        ~node()
        {
            if(_next)
                delete _next;
        }
    };

    list(Value v) : _head(new node()), _tail(new node()), _size(1)
    {
        _head->_next = _tail->_prev = new node(v);
        _head->_next->_prev = _head;
        _tail->_prev->_next = _tail;
    }

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
            return *(_current->_value.get());
        }

        const Value & operator*()const
        {
            return *(_current->_value.get());
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

    list(const list & other) = delete;

//    list(node * h, node * t, int s): _head(h), _tail(t), _size(s) {}

    list() : _head(new node()), _tail(new node()), _size(0)
    {
        _head->_next = _tail;
        _tail->_prev = _head;
    }

    list(node * n) : _head(new node()), _tail(new node()), _size(1)
    {
        _head->_next = n;
        n->_prev = _head;
        _tail->_prev = n;
        n->_next = _tail;

    }

    list(list && other)
        : _head(new node()), _tail(new node()), _size(0)
    {
        _head->_next = _tail;
        _tail->_prev = _head;

        using std::swap;
        swap(_head, other._head);
        swap(_tail, other->_tail);
        swap(_size, other._size);
    }

    list & operator=(list && other)
    {
        if(this != &other)
        {
            using std::swap;
            swap(_head, other._head);
            swap(_tail, other._tail);
            swap(_size, other._size);
        }
        return *this;
    }

    ~list()
    {
        delete _head;
    }

private:
    auto push_front()-> void;
    auto push_back()-> void;

    auto partition(node *, node *)->void;
    auto selectPartition(node * left, node * right, int pos)->Value;

public:
    const int & size() const;
    auto is_empty() const -> bool;

    auto remove(node *) -> void;//probably should be private

    auto push_front(Value)-> void;
    auto pop_front(void)  -> Value;

    auto push_back(Value)-> void;
    auto pop_back(void)  -> Value;

    auto begin() -> iterator;
    auto last_elem() -> iterator;

    auto join_front(list && other) -> void;
    auto join_back(list && other) -> void;
    auto detach_front() -> list<Value>;

    auto join_tail(list &&) -> void;
    auto detach_head() -> list<Value>;

    auto detach_elem()->list<Value>;

    auto detach_half() -> list<Value>;
    auto detach_back(void) -> list<Value>;
    auto end() -> iterator;

    auto quick_sort()->void;

    auto select(int givenPosition)->Value;


private:
    node * _head;
    node * _tail;
    int _size;
};

template<Value>
auto list<Value>::detach_elem(list<Value>::iterator it)->list<value>
{
    std::unique_ptr<Value> tmp;
    tmp.swap(*it);
    return std::move(list<Value>::unitList(tmp));
}

//----begin and end------------------
template<typename Value>
auto list<Value>::begin() -> list<Value>::iterator
{
    return list<Value>::iterator(_head->_next);
}

template<typename Value>
auto list<Value>::last_elem() -> list<Value>::iterator
{
    return list<Value>::iterator(_tail->_prev);
}

template<typename Value>
auto list<Value>::end() -> list<Value>::iterator
{
    return list<Value>::iterator(_tail);
}

//---info abou list capacity---------

template<typename Value>
auto list<Value>::size() const -> const int &
{
    int count = 0;
    list<Value>::iterator it = begin();
    while(it!=end()){++it; ++count;}
    return count;//_size;
}

template<typename Value>
auto list<Value>::is_empty() const -> bool
{
    return size() == 0;
}
//-------------------------------------


//----push and pop front----------------
template<typename Value>
auto list<Value>::push_front(Value v) -> void
{
    node * nPtr = new node(_head, _head->_next, v);

    _head->_next = nPtr;
    nPtr->_next->_prev = nPtr;

    ++_size;
}

template<typename Value>
auto list<Value>::push_front(void) -> void
{
    node * nPtr = new node(_head, _head->_next);

    _head->_next = nPtr;
    nPtr->_next->_prev = nPtr;

    ++_size;
}

template<typename Value>
auto list<Value>::remove(node * toRe) -> void
{
    if(!toRe->hasValue())
    {
        throw std::out_of_range("trying to remowe guard-node");
    }
    else
    {
        _size--;

        toRe->_prev->_next = toRe->_next;
        toRe->_next->_prev = toRe->_prev;

        toRe->_next = nullptr;
        delete toRe;
    }
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
        node * tmpNode = _head->_next;
        std::unique_ptr<Value> tmpPtr;

        tmpPtr.swap(_value);

        remove(tmpNode);

        return *tmpPtr
    }
}

/*------------the old one:-----------
        Value tmpValue = *_head->_value;
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
}*/
//------push and pop back----------------

template<typename Value>
auto list<Value>::push_back(Value v) -> void
{
    node * nPtr = new node(_tail->_prev, _tail, v);

    _tail->_prev = nPtr;
    nPtr->_prev->_next = nPtr;

    ++_size;
}

template<typename Value>
auto list<Value>::push_back(void) -> void
{
    node * nPtr = new node(_tail->_prev, _tail);

    _tail->_prev = nPtr;
    nPtr->_prev->_next = nPtr;

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
        node * tmpNode = _tail->_prev;
        std::unique_ptr<Value> tmpPtr;

        tmpPtr.swap(_value);

        remove(tmpNode);

        return *tmpPtr
    }
}
/*
    if(this->is_empty())
    {
        throw std::exception();
    }
    else
    {
        Value tmpValue = *_tail->_value;
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
}*/
//-----join and detach-------------------

template<typename Value>
auto list<Value>::join_tail(list<Value> && other) -> void
{
    if(this != &other && !other.is_empty())
    {
        other._head->_next->_prev = _tail->_prev;
        other._tail->_prev->_next = _tail;

        _tail->_prev->_next = other._head->_next;
        _tail->_prev = other._tail->_prev;

        other._head->_next = other._tail;
        _size += other._size;
    }
}


template<typename Value>
auto list<Value>::detach_front() -> list<Value>
{
    _size--;


    delete toRe;

    if(this->is_empty())
    {
        throw std::exception();
    }
    else
    {
        node * toRe = _head->_next;

        _head->_next = toRe->_next;
        toRe->_next->_prev = toRe->_prev;

        toRe->_next = nullptr;
        std::unique_ptr<Value> tmpPtr;

        tmpPtr.swap(_value);

        remove(tmpNode);

        return *tmpPtr
    }
    node * tmp;
}


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




#endif //LIST_HPP
