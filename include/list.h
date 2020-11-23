#ifndef __list_h
#define __list_h

#include <iostream>

template <class T>
class list
{
private:
    struct list_node
    {
        T *val;
        list_node *next;
    };
    list_node *first, *last;
    size_t _size;

    void clear();
    void copy(const list&);
public:
    list();
    list(const list&);
    ~list();
    list& operator= (const list&);

    list& append(const T&);
    size_t size() const;

    template <class E>
    friend std::ostream& operator<< (std::ostream&, const list<E>&);
};

template <class T>
list<T>::list() : head(nullptr), last(nullptr), size(0)
{}

template <class T>
list<T>::list(const list<T>& lst)
{
    copy(lst);
}

template <class T>
list<T>::~list()
{
    clear();
}

template <class T>
list<T> &list<T>::operator= (const list<T>& lst)
{
    if (this != &lst)
    {
        clear();
        copy(lst);
    }
    return *this;
}

template <class T>
list<T> &list<T>::append(const T& val)
{
    if (last == nullptr)
    {
        first = last = new list_node {val, nullptr};
    }
    else
    {
        list_node *node = new list_node {val, nullptr};
        last->next = node;
        last = node;
    }
    _size++;
    return *this;
}

template <class T>
size_t list<T>::size() const
{
    return _size;
}

template <class T>
void list<T>::clear()
{
    list_node *node;
    while (first != nullptr)
    {
        node = first;
        first = first->next;
        delete node;
    }
    first = nullptr;
    last = nullptr;
    _size = 0;
}

template <class T>
void list<T>::copy(const list<T>& lst)
{
    if (lst.first == nullptr)
    {
        first = nullptr;
        last = nullptr;
        _size = 0;
        return;
    }
    first = last = new list_node {lst.first->val, nullptr};
    list_node *lst_temp = lst.first->next;
    while (lst_temp != nullptr)
    {
        last->next = new list_node {lst_temp->val, nullptr};
        last = last->next;
        lst_temp = lst_temp->next;
    }
}

template <class T>
std::ostream& operator<< (std::ostream& out, const list<T>& lst)
{
    typename list<T>::list_node *node = lst.first;
    while (node->next != nullptr)
    {
        out << node->val << " ";
    }
    out << node->val << std::endl;
    return out;
}

#endif