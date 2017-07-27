//
// Created by Веда Воронина on 25.07.15.
//

#include "deque.h"

using value_type = deque::value_type;
using const_iterator = deque::const_iterator;

deque::const_iterator::const_iterator(deque& p) : ptr(nullptr), parent(&p) {

}

deque::const_iterator::const_iterator(iterator const& other) : ptr(other.ptr), parent(other.parent) {

}

deque::const_iterator::const_iterator(deque& parent, value_type* ptr) : ptr(ptr), parent(&parent) {

}

deque::const_iterator::~const_iterator() {

}
value_type const& deque::const_iterator::operator*() {
    return *ptr;
}

value_type const* deque::const_iterator::operator->() {
    return ptr;
}

bool deque::const_iterator::operator==(const_iterator const& other) const {
    return (ptr == other.ptr);
}

bool deque::const_iterator::operator!=(const_iterator const& other) const {
    return (ptr != other.ptr);
}

bool deque::const_iterator::operator<(const_iterator const& other) const {
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

bool deque::const_iterator::operator>(const_iterator const& other) const {
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

bool deque::const_iterator::operator<=(const_iterator const& other) const {
    return this->operator<(other) || this->operator==(other);
}

bool deque::const_iterator::operator>=(const_iterator const& other) const {
    return this->operator<(other) || this->operator==(other);
}

