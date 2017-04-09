//
// Created by Vedana Voronina on 08.04.17.
//

#include "lazy_string.h"
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

lazy_string::lazy_char::operator char() const
{
    return (*(str->str_ptr))[str->start + pos];
}

lazy_string::lazy_char &lazy_string::lazy_char::operator=(char ch)
{
    if (str->str_ptr.use_count() > 1)
    {
        str->start = 0;
        str->str_ptr = make_shared<string>(str->str_ptr->substr(str->start, str->len));
    }
    (*(str->str_ptr))[str->start + pos] = ch;
}

lazy_string::lazy_char::lazy_char(lazy_string *new_str, size_t new_pos)
{
    str = new_str;
    pos = new_pos;
}

lazy_string::lazy_string()
{
    str_ptr = make_shared<string>("");
}

lazy_string::lazy_string(const string &str)
{
    str_ptr = make_shared<string>(str);
    len = str.size();
}

lazy_string::lazy_string(const shared_ptr<string> new_str, size_t new_start, size_t new_len)
{
    str_ptr = new_str;
    start = new_start;
    len = new_len;
}

size_t lazy_string::size() const
{
    return len;
}

size_t lazy_string::length() const
{
    return len;
}

lazy_string::lazy_char lazy_string::operator[](size_t pos)
{
    return at(pos);
}

const char &lazy_string::operator[](size_t pos) const
{
    return at(pos);
}

lazy_string::lazy_char lazy_string::at(size_t pos)
{
    if (pos < 0 || pos >= len)
        throw out_of_range("Invalid index!");
    return lazy_char(this, pos);
}

const char &lazy_string::at(size_t pos) const
{
    if (pos < 0 || pos >= len)
        throw out_of_range("Invalid index!");
    return (*str_ptr)[start + pos];
}

lazy_string::operator string()
{
    return str_ptr->substr(start, len);
}

lazy_string lazy_string::substr(size_t pos, size_t count)
{
    if (pos < 0 || pos > len)
        throw out_of_range("Invalid index!");
    else
        return lazy_string(str_ptr, start + pos, min(count, len - pos));
}

istream &operator>>(istream &in, lazy_string &str)
{
    shared_ptr<string> new_str = make_shared<string>();
    in >> *new_str;
    str.str_ptr = new_str;
    str.len = new_str->size();
    return in;
}

ostream &operator<<(ostream &out, lazy_string &str)
{
    return out << string(str);
}
