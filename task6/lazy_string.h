//
// Created by Vedana Voronina on 08.04.17.
//

#ifndef TASK6_LAZY_STRING_H
#define TASK6_LAZY_STRING_H

#include <string>
#include <istream>
#include <ostream>
#include <memory>

using namespace std;

class lazy_string
{
    class lazy_char
    {
        lazy_char(lazy_string *str, size_t pos);

        size_t pos;
        lazy_string *str;

    public:
        friend class lazy_string;

        lazy_char &operator=(char c);

        operator char() const;
    };

    size_t start = 0, len = 0;
    shared_ptr<string> str_ptr;

    lazy_string(const shared_ptr<string> str, size_t, size_t);

public:

    lazy_string();

    lazy_string(const string &str);

    size_t size() const;

    size_t length() const;

    lazy_char operator[](size_t pos);

    const char &operator[](size_t pos) const;

    lazy_char at(size_t pos);

    const char &at(size_t pos) const;

    operator string();

    lazy_string substr(size_t pos = 0, size_t count = string::npos);

    friend istream &operator>>(istream &in, lazy_string &str);

    friend ostream &operator<<(ostream &out, lazy_string &str);

};

#endif //TASK6_LAZY_STRING_H