#ifndef __hash_table_h
#define __hash_table_h

#include <iostream>
#include <cassert>
#include <string>

template <class K>
struct hash
{
    static size_t get(const K& key, size_t size)
    {
        return 0;
    }
};  

template <>
struct hash<std::string>
{
    static size_t get(std::string key, size_t size)
    {
        size_t hashValue = 0;
        for (size_t i = 0; i < key.size(); i++)
        {
            hashValue += (unsigned char) key[i];
        }
        return hashValue % size;
    }
};

template <class K, class V, typename hash_generator = hash<K>>
class hash_table
{
private:
    struct node
    {
        K key;
        V value;
        node *next;
    };
    size_t size;
    node **h_table;

    size_t hash_function(const K&) const;
    void insert_begin(size_t, const K&, const V&);
    node* search(const K&, size_t) const;
    void clear(node*);
public:
    hash_table();
    hash_table(const hash_table&) = delete;
    hash_table& operator= (const hash_table&) = delete;
    ~hash_table();

    hash_table& insert(const K&, const V&);
    hash_table& erase(const K&);    

    V& get(const K&);
    V get(const K&) const;

    bool contains(const K&) const;
};

template <class K, class V, typename hash_generator>
hash_table<K, V, hash_generator>::hash_table() : size(211)
{
    h_table = new node*[size];
    for (size_t i = 0; i < size; i++)
    {
        h_table[i] = nullptr;
    }
}

template <class K, class V, typename hash_generator>
hash_table<K, V, hash_generator>::~hash_table()
{
    for (size_t i = 0; i < size; i++)
    {
        clear(h_table[i]);
    }
    delete[] h_table;
}

template <class K, class V, typename hash_generator>
hash_table<K, V, hash_generator>& hash_table<K, V, hash_generator>::insert(const K& key, const V& value)
{
    size_t hashed_position = hash_function(key);
    assert (!search(key, hashed_position));
    insert_begin(hashed_position, key, value);
    return *this;
}

template <class K, class V, typename hash_generator>
hash_table<K, V, hash_generator>& hash_table<K, V, hash_generator>::erase(const K& key)
{
    size_t hashed_position = hash_function(key);
    node *hash_node = search(key, hashed_position);
    if (hash_node)
    {
        node *save;
        if (hash_node->key == key)
        {
            save = h_table[hashed_position];
            h_table[hashed_position] = h_table[hashed_position]->next;
            delete save;
        }
        else 
        {
            node *tmp = hash_node;
            while (tmp->next->key != key)
            {
                tmp = tmp->next;
            }
            save = tmp->next;
            tmp->next = tmp->next->next;
            delete save;
        }
    }
    return *this;
}

template <class K, class V, typename hash_generator>
V& hash_table<K, V, hash_generator>::get(const K& key)
{
    size_t hashed_position = hash_function(key);
    node *hash_node = search(key, hashed_position);
    assert(hash_node != nullptr);
    return hash_node->value;
}

template <class K, class V, typename hash_generator>
V hash_table<K, V, hash_generator>::get(const K& key) const
{
    size_t hashed_position = hash_function(key);
    node *hash_node = search(key, hashed_position);
    assert(hash_node != nullptr);
    return hash_node->value;
}

template <class K, class V, typename hash_generator>
bool hash_table<K, V, hash_generator>::contains(const K& key) const
{
    return search(key, hash_function(key)) != nullptr;
}

template <class K, class V, typename hash_generator>
typename hash_table<K, V, hash_generator>::node* hash_table<K, V, hash_generator>::search(const K& key, size_t position) const
{
    node *tmp = h_table[position];
    while (tmp)
    {
        if (key == tmp->key)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return nullptr;
}

template <class K, class V, typename hash_generator>
void hash_table<K, V, hash_generator>::insert_begin(size_t position, const K& key, const V& value)
{
    h_table[position] = new node {key, value, h_table[position]};
}

template <class K, class V, typename hash_generator>
size_t hash_table<K, V, hash_generator>::hash_function(const K& key) const
{
    return hash_generator::get(key, size);
}

template <class K, class V, typename hash_generator>
void hash_table<K, V, hash_generator>::clear(node* current)
{
    node *save;
    while (current)
    {
        save = current;
        current = current->next;
        delete save;
    }
}

#endif