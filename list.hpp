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
        iterator() : _previous(nullptr), _now_on(nullptr)
        {

        }

        node & operator*()
        {
            return *_now_on;
        }

        node * operator->()
        {
            return _now_on;
        }

        iterator operator++()
        {
            _previous=_now_on;
            _now_on=_now_on->_next;
            return this;//pre
        }

        iterator operator++(int)
        {
            //post
        }
    private:
        node * _previous;
        node * _now_on;
    };

    list() : _head(nullptr), _size(0) {}
    const int & size() const;
    auto is_empty() const -> bool;

    auto push_front(Value)-> void;
    auto pop_front(void)  -> Value;

    auto push_back(Value)-> void;
    auto pop_back(void)  -> Value;

    auto get_second_half() -> list;

private:
    node * _head;
    int _size;
};

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
    if(!_head)
    {
        _head = new node(v);
    }
    else
    {
        node * tmp = _head;
        _head = new node(tmp, v);
    }
    _size++;
}

template<typename Value>
auto list<Value>::pop_front(void) -> Value
{
    if(!is_empty())
    {
        _size--;
        return _head->_value;
    }
    else
    {
        //throw
    }
}

//---------------------------------------

//------push and pop back----------------

template<typename Value>
auto list<Value>::push_back(Value v) -> void
{
    if(!_head)
    {
        _head = new node(v);
    }
    else
    {
        node * tmp = _head;

        while(tmp->next)
        {
            tmp = tmp->next;
        }

        tmp->next = new node(v);
    }
    _size++;
}

template<typename Value>
auto list<Value>::pop_back(void) -> Value
{
    if(!is_empty())
    {
        _size--;
        node * tmp = _head;

        while(tmp->next)
        {
            tmp = tmp->next;
        }

        Value valToRet = tmp->_value;
        delete tmp;//ROZKMIŃ TO
    }
    else
    {
        //throw
    }
}

//---------------------------------------

#endif //LIST_HPP
