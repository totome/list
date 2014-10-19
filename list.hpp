#ifndef LIST_HPP
#define LIST_HPP


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

    list() : _head(nullptr), _tail(_head), _size(0)
    {

    }

    const int & size() const;
    auto is_empty() const -> bool;

    auto push_front(Value)-> void;
    auto pop_front(void)  -> Value;

    auto push_back(Value)-> void;
    auto pop_back(void)  -> Value;

    auto begin() -> iterator;
    auto end() -> iterator;
    auto get_second_half() -> list;

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
        --_size;
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

//---------------------------------------

#endif //LIST_HPP
