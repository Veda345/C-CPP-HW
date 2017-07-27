//
// Created by Веда Воронина on 25.07.15.
//

#include "deque.h"
using value_type = deque::value_type;
using iterator = deque::iterator;

deque::iterator::iterator(deque& p) : ptr(nullptr), parent(&p) {

}

deque::iterator::iterator(iterator const& other) : ptr(other.ptr), parent(other.parent) {

}

deque::iterator::iterator(deque& parent, value_type* ptr) : ptr(ptr), parent(&parent) {

}

deque::iterator::~iterator() {

}

iterator& deque::iterator::operator=(iterator const& other) {
    parent = other.parent;
    ptr = other.ptr;
    return *this;
}

value_type& deque::iterator::operator*() {
    return *ptr;
}

value_type const& deque::iterator::operator*() const {
    return *ptr;
}

value_type* deque::iterator::operator->() {
    return ptr;
}

bool deque::iterator::operator==(iterator const& other) const {
    return (ptr == other.ptr);
}

bool deque::iterator::operator!=(iterator const& other) const {
    return (ptr != other.ptr);
}

bool deque::iterator::operator<(iterator const& other) const {
    if (this->operator==(other))
        return false;
    if (parent->first < parent->first + parent->sz) {
        return ptr < other.ptr;
    } else {
        if (ptr > parent->first.ptr && other.ptr > parent->first.ptr)
            return ptr < other.ptr;
        if (ptr < (parent->first + parent->sz).ptr && other.ptr < (parent->first + parent->sz).ptr)
            return ptr < other.ptr;
        if (ptr < (parent->first + parent->sz).ptr && other.ptr > parent->first.ptr)
            return false;
        if (ptr > parent->first.ptr && other.ptr < (parent->first + parent->sz).ptr)
            return true;
    }
    return true;
}

bool deque::iterator::operator>(iterator const& other) const {
    if (this->operator==(other))
        return false;
    if (parent->first < parent->first + parent->sz) {
        return ptr > other.ptr;
    } else {
        if (ptr > parent->first.ptr && other.ptr > parent->first.ptr)
            return ptr > other.ptr;
        if (ptr < (parent->first + parent->sz).ptr && other.ptr < (parent->first + parent->sz).ptr)
            return ptr > other.ptr;
        if (ptr < (parent->first + parent->sz).ptr && other.ptr > parent->first.ptr)
            return true;
        if (ptr > parent->first.ptr && other.ptr < (parent->first + parent->sz).ptr)
            return false;
    }
    return false;
}

bool deque::iterator::operator<=(iterator const& other) const {
    return this->operator<(other) || this->operator==(other);
}

bool deque::iterator::operator>=(iterator const& other) const {
    return this->operator>(other) || this->operator==(other);
}


iterator& deque::iterator::operator++() {
    ptr++;
    if (ptr == (parent->start + parent->capacity)) {
        ptr = parent->start;
    }
    return *this;
}

iterator& deque::iterator::operator--() {
    if (ptr == parent->start) {
        ptr = parent->start + parent->capacity;
    }
    ptr--;
    return *this;
}

iterator& deque::iterator::operator+=(int const& other) {
    if (other == 0)
        return *this;
    if (other < 0) {
        return this->operator-=(-other);
    }
    int len = other;
    if (parent->first.ptr < ptr) {
        if (ptr < parent->start + parent->sz - len) ptr += len;
        else ptr = parent->start, len -= parent->start + parent->sz - ptr, ptr += len;
        return *this;
    }
    ptr += len;
    return *this;
}

iterator& deque::iterator::operator-=(int const& other) {
    if (other == 0)
        return *this;
    if (other < 0) {
        return this->operator+=(-other);
    }
    size_t len = other;
    if (parent->first.ptr > ptr) {
        if (ptr - parent->start >= len) ptr -= len;
        else ptr = parent->start + parent->sz, len -= ptr - parent->start, ptr -= len;
        return *this;
    }
    ptr -= len;
    return *this;
}

deque::iterator operator+(deque::iterator a, int const& b) {
    return a += b;
}

deque::iterator operator-(deque::iterator a, int const& b) {
    return a -= b;
}

deque::iterator operator+(int const& a, deque::iterator b) {
    return b += a;
}


