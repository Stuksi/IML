#ifndef __dllist_h
#define __dllist_h

#include <iostream>
#include <cassert>
#include <functional>

template <class T>
class dllist
{
private:
    struct node
    {
        T data;
        node *next, *previous;
    };
    node first;
    size_t len;

    void clear();
    void copy(const dllist&);
public:
    dllist();
    dllist(const dllist&);
    dllist& operator= (const dllist&);
    ~dllist();

    dllist& append(const T&);
    dllist& sort(std::function<bool(const T&, const T&)>);

    size_t size() const;

    template <class E> 
    friend std::ostream& operator<< (std::ostream&, const dllist<E>&);

    class iterator
    {
    private:
        node *current, *first;
    public:
        iterator(node*, node*);

        T& operator*();
        iterator& operator++();
        iterator& operator--();
        bool operator!=(const iterator&);
    };

    iterator begin();
    iterator last();
    iterator end();
};

// ----------------------------------------- // STRUCTURE // ----------------------------------------- //

template <class T>
dllist<T>::dllist() : len(0)
{
    first.next = &first;
    first.previous = &first;
}

template <class T>
dllist<T>::dllist(const dllist& dllist) : len(0)
{
    first.next = &first;
    first.previous = &first;
    copy(dllist);
}

template <class T>
dllist<T>& dllist<T>::operator=(const dllist& dllist)
{
    if (this != &dllist)
    {
        clear();
        copy(dllist);
    }
    return *this;
}

template <class T>
dllist<T>::~dllist()
{
    clear();
}

// ----------------------------------------- // FUNCTIONALITY // ----------------------------------------- //

template <class T>
dllist<T>& dllist<T>::append(const T& data)
{
    if (first.next == &first)
    {
        first.next = first.previous = new node {data, &first, &first};
    }
    else
    {
        first.previous = new node {data, &first, first.previous};
        first.previous->previous->next = first.previous;
    }
    len++;
    return *this;
}

template <class T>
dllist<T>& dllist<T>::sort(std::function<bool(const T&, const T&)> predicate)
{
    return *this;
}

template <class T>
size_t dllist<T>::size() const
{
    return len;
}

template <class T>
typename dllist<T>::iterator dllist<T>::begin()
{
    return iterator(first.next, &first);
}

template <class T>
typename dllist<T>::iterator dllist<T>::end()
{
    return iterator(&first, &first);
}

template <class T>
typename dllist<T>::iterator dllist<T>::last()
{
    return iterator(first.previous, &first);
}

// ----------------------------------------- // CLASS iterator // ----------------------------------------- //

template <class T>
dllist<T>::iterator::iterator(node *_current, node *_first) : current(_current), first(_first)
{}

template <class T>
T& dllist<T>::iterator::operator*()
{
    assert(current != first);
    return current->data;
}

template <class T>
typename dllist<T>::iterator& dllist<T>::iterator::operator++()
{
    assert(current != first);
    current = current->next;
    return *this;
}

template <class T>
typename dllist<T>::iterator& dllist<T>::iterator::operator--()
{
    assert(current != first);
    current = current->previous;
    return *this;
}

template <class T>
bool dllist<T>::iterator::operator!=(const iterator& iterator)
{
    return current != iterator.current;
}

// ----------------------------------------- // HELPER // ----------------------------------------- //

template <class T>
std::ostream& operator<< (std::ostream& out, const dllist<T>& dllist)
{
    typename dllist<T>::node *tmp = dllist.first.next;
    if (tmp != &dllist.first)
    {
        while (tmp->next != &dllist.first)
        {
            out << tmp->data << " ";
            tmp = tmp->next;
        }
        out << tmp->data;
    }
    return out;
}

template <class T>
void dllist<T>::copy(const dllist& dllist)
{
    if (dllist.first.next == &dllist.first)
    {
        return;
    }
    node *tmp = dllist.first.next;
    while (tmp != &dllist.first)
    {
        append(tmp->data);
        tmp = tmp->next;
    }
}

template <class T>
void dllist<T>::clear()
{
    node *tmp = first.next, *save;
    while (tmp != &first)
    {
        save = tmp;
        tmp = tmp->next;
        delete save;
    }
    first.previous = &first;
    first.next = &first;
    len = 0;
}

#endif