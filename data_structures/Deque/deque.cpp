#include <iostream>
#include "deque.h"

deque::deque() : start(nullptr), first(*this, nullptr), sz(0), capacity(0) {

}
deque::deque(size_t cap) :
        sz(0), capacity(cap), first(*this, nullptr),start(nullptr)
{
    start = (deque::value_type *)operator new(cap * sizeof(value_type));
    first = iterator(*this, start);
}

deque::deque(deque const& other) :
        deque(other.capacity)
{
    size_t s = other.sz;
    sz = 0;
    for(size_t i = 0; i <= s && s > 0; i++) {
        new(first.ptr + i) value_type(other.first.ptr[i]);
        sz = i;
    }
}

deque::~deque() {
    clear_buffer(start, sz);
    operator delete (start);
}

deque::iterator deque::begin() {
    return first;
}

deque::const_iterator deque::begin() const {
    return first;
}

deque::iterator deque::end() {
    return first+sz;
}

deque::const_iterator deque::end() const {
    return first+sz;
}

deque& deque::operator=(deque const& other) {
    deque tmp(other);
    swap(tmp);
    return *this;
}

void deque::push_back(value_type const& element) {
    if (sz == capacity) {
        size_t new_capacity = std::max(DEFAULT_SIZE, 2 * capacity);
        deque tmp (new_capacity);
        size_t  t = sz;
        for(size_t i = 0; i < t; i++) {
            tmp.push_back(*(first+i));
        }
        swap(tmp);

    }
    new ((first + sz).ptr) value_type(element);
    sz++;
}

void deque::push_front(value_type const& element) {
    if (sz == capacity) {
        size_t new_capacity = std::max(DEFAULT_SIZE, 2 * capacity);
        deque tmp(new_capacity);
        size_t  t = sz;
        for(size_t i = 0; i < t; i++) {
            tmp.push_back(*(first+i));
        }
        swap(tmp);

    }
        new ((first - 1).ptr) value_type(element);
        first = iterator(*this, (first - 1).ptr);
        sz++;
}

deque::value_type& deque::front() {
    return *first;
}

deque::value_type& deque::back() {
    return *(first + sz - 1);
}

deque::value_type const& deque::back() const {
    return *(first + sz - 1);
}

deque::value_type const& deque::front() const {
    return *first;
}

void deque::pop_front() {
    value_type* b = first.ptr;
    ++first;
    b->~value_type();
    --sz;
}

void deque::pop_back() {
    (&*first + --sz)->~value_type();

}

bool deque::empty() const {
    return (sz == 0);
}

size_t deque::size() const {
    return sz;
}

deque::value_type& deque::operator[](size_t index) {
    return *(first + index);
}

deque::value_type const& deque::operator[](size_t index) const {
    return *(first + index);
}

deque::iterator deque::erase(iterator pos) {
    iterator it = pos;
    for(; it != first; --it) {
        value_type tmp = *(it - 1);
        *(it - 1) = *it;
        *it = tmp;
    }
    pop_front();
    return pos;
}

deque::iterator deque::insert(iterator pos, value_type const& element) {
    push_back(element);
    iterator it = first + (sz - 1);
    for (int i = 0; i < sz; i++)
        std:: cout << *(first+i) << std:: endl;
    for(; it != pos ; it-=1) {
        value_type tmp = *(it - 1);
        *(it - 1) = *it;
        *it = tmp;
    }
    return pos;
}

void deque::clear_buffer(value_type *buffer, size_t size) {
    value_type* begin = buffer;
    for (size_t i = 0; i < size; i++) {
        (begin + i)->~value_type();
    }
}
void deque::swap(deque& other){
    iterator tmp = first;
    first = other.first;
    other.first = tmp;
    std::swap(sz, other.sz);
    std::swap(capacity, other.capacity);
    std::swap(start, other.start);
}


