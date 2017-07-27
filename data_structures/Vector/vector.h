#ifndef VECTOR_H
#define VECTOR_H

#include <string>

class vector
{
public:
    typedef std::string value_type;
    typedef value_type* iterator;
    typedef value_type const* const_iterator;
    typedef std::size_t size_type;

    vector();
    vector(vector const& other);

    ~vector();

    vector& operator=(vector const& other);

    void clear();

    void push_back(value_type const& value);
    void pop_back();

    value_type& back();
    value_type const& back() const;

    size_type size() const;
    value_type& operator[](size_type index);
    value_type const& operator[](size_type index) const;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    iterator erase(iterator pos);
    iterator erase(iterator first, iterator second);

    iterator insert(iterator pos, value_type const& value);
private:
    vector(size_type cap);
    void swap(vector& other);

    iterator first;
    size_type s, capacity;
};

#endif // VECTOR_H
