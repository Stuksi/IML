#ifndef __stack_h
#define __stack_h

#include <cstdio>
#include <cassert>

template <class T>
class stack
{
private:
    struct node
    {
        T data;
        node *next;
    };
    node *_top;
    size_t len;

    void clear();
    void copy(const stack&);
public:
    stack();
    stack(const stack&);
    ~stack();

    stack& operator= (const stack&);

    stack& push(const T&);
    stack& pop();
    
    bool empty();

    T& top();
    T top() const;

    size_t size() const;
};

template <class T>
stack<T>::stack() : _top(nullptr), len(0)
{}

template <class T>
stack<T>::stack(const stack& s)
{
    copy(s);
}

template <class T>
stack<T>::~stack()
{
    clear();
}

template <class T>
stack<T>& stack<T>::operator= (const stack& s)
{
    if (this != &s)
    {
        clear();
        copy(s);
    }
    return *this;
}


template <class T>
stack<T>& stack<T>::push(const T& data)
{
    _top = new node {data, _top};
    len++;
    return *this;
}

template <class T>
stack<T>& stack<T>::pop()
{
    assert(_top != nullptr);
    node *save = _top;
    _top = _top->next;
    len--;
    delete save;
    return *this;
}

template <class T>
bool stack<T>::empty()
{
    return len == 0;
}

template <class T>
T& stack<T>::top()
{
    assert(_top != nullptr);
    return _top->data;
}

template <class T>
T stack<T>::top() const
{
    assert(_top != nullptr);
    return _top->data;
}

template <class T>
size_t stack<T>::size() const
{
    return len;
}

template <class T>
void stack<T>::clear()
{
    node *save;
    while (_top != nullptr)
    {
        save = _top;
        _top = _top->next;
        delete save;
    }
    len = 0;
}

template <class T>
void stack<T>::copy(const stack& s)
{
    _top = new node {s._top->data, nullptr};
    node *s_it = s._top->next, *it = _top;
    while (s_it != nullptr)
    {
        it->next = new node {s_it->data, nullptr};
        s_it = s_it->next;
        it = it->next;
    }
    len = s.len;
}

#endif