#include "vector.h"

const vector::size_type STD_SIZE = 10;
const vector::size_type TYPE_SIZE = sizeof(vector::value_type);

vector::vector() :
    vector(STD_SIZE)
{
}

vector::vector(size_type cap) :
    s(0), capacity(cap)
{
    first = (vector::iterator)::operator new(cap * TYPE_SIZE);
}

vector::vector(vector const& other) :
    vector(other.capacity)
{
    s = other.s;
    for(vector::size_type i = 0; i < s; i++)
        new(first + i) value_type(other.first[i]);
}

vector::~vector(){
    clear();
    ::operator delete(first);
}

void vector::push_back(vector::value_type const& value) {
    if (s == capacity) {
        vector tmp(2 * capacity);

        for(size_type i = 0; i < s; i++)
            tmp.push_back(*(first + i));

        swap(tmp);
    }
    new(first + s++) value_type(value);
}

void vector::pop_back(){
    typedef value_type value_type_2;
    first[s - 1].~value_type_2();
    s--;
}

void vector::clear(){
    typedef value_type value_type_2;
    for(size_type i = 0; i < s; i++)
        first[i].~value_type_2();
    s = 0;
}

vector& vector::operator =(vector const& other) {
    vector tmp(other);
    swap(tmp);
    return *this;
}

vector::iterator vector::erase(iterator pos){
    iterator ret  = pos++;
    iterator last = end();
    for (;pos != last; pos++)
        std::swap(*(pos - 1), *pos);
    pop_back();
    return ret;
}

vector::iterator vector::erase(iterator first, iterator second){
    iterator ret  = first;
    iterator last = end();
    for(;second != last; first++, second++) {
        std::swap(*first, *second);
    }
    size_type n = second - first;
    for(size_type i = 0; i < n; i++)
        pop_back();
    return ret;
}

vector::iterator vector::insert(iterator pos, value_type const& value) {
    push_back(value);
    iterator it = end() - 1;
    for(; it != pos; it--)
        std::swap(*(it - 1), *it);
    return pos;
}

void vector::swap(vector& other){
    iterator tmp = other.first;
    other.first = first;
    first = tmp;

    std::swap(s, other.s);
    std::swap(capacity, other.capacity);
}


vector::iterator vector::begin(){
    return first;
}

vector::const_iterator vector::begin() const{
    return first;
}

vector::iterator vector::end(){
    return first + s;
}

vector::const_iterator vector::end() const{
    return first + s;
}

vector::value_type& vector::back(){
    return first[s - 1];
}

vector::value_type const& vector::back() const{
    return first[s - 1];
}

vector::size_type vector::size() const{
    return s;
}

vector::value_type& vector::operator [](vector::size_type index){
    return first[index];
}

vector::value_type const& vector::operator [](vector::size_type index) const{
    return first[index];
}