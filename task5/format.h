#ifndef TASK4_FORMAT_H
#define TASK4_FORMAT_H

#include <string>
#include <sstream>
#include <stdexcept>
#include <cstddef>
#include <iomanip>
#include <cstdio>
#include <typeinfo>

using namespace std;

struct format_s
{
    bool is_positive = false,
            is_negative = false,
            is_space = false,
            is_sharp = false,
            is_zero = false;
    int width = -1, precision = -1;
    char len = ' ';
    char spec;
    string specifiers = "diuoxXfFeEgGaAcspn";
    string len_types = "lhjztL";
    string flags = "-+ #0";
};

string parse_at_symbol(nullptr_t force);

template<typename... Args>
string format(const string &cur_str, const Args &... args);

template<typename T, typename... S>
string substitute(const string &cur_str, unsigned pos, const T &force, const S &... args);

template<typename T, typename S>
typename enable_if<is_convertible<S, T>::value, T>::type parsing(S force)
{
    return (T) force;
}

template<typename T, typename S>
typename enable_if<!is_convertible<S, T>::value, T>::type parsing(S force)
{
    throw invalid_argument("Invalid argument type.");
}

string get_inter_sym(const string &cur_str, unsigned &pos, bool hasArg)
{
    string sym = "";
    while (pos < cur_str.length())
    {
        int p = pos;
        while (pos < cur_str.length() && cur_str[pos] != '%')
            pos++;
        sym += cur_str.substr(p, pos - p);

        if (pos == cur_str.length() - 1)
            throw invalid_argument("Invalid format");
        if (pos == cur_str.length())
            return sym;

        if (cur_str[++pos] == '%')
        {
            pos++;
            sym += '%';
            continue;
        } else
        {
            if (!hasArg)
            {
                throw out_of_range("Not enough args");
            } else
            {
                return sym;
            }
        }
    }
    return sym;
}

void get_flags(const string &cur_str, uint &pos, struct format_s &cur_format)
{
    while (pos < cur_str.length() && cur_format.flags.find(cur_str[pos]) != string::npos)
        switch (cur_str[pos++])
        {
            case '-':
                cur_format.is_negative = true;
                break;
            case '+':
                cur_format.is_positive = true;
                break;
            case ' ':
                cur_format.is_space = true;
                break;
            case '#':
                cur_format.is_sharp = true;
                break;
            case '0':
                cur_format.is_zero = true;
                break;
            default:
                throw invalid_argument("Invalid flag");
        }
}

void get_len_type(const string &cur_str, uint &pos, struct format_s &cur_format)
{
    if (cur_format.len_types.find(cur_str[pos]) != string::npos)
    {
        switch (cur_str[pos])
        {
            case 'h':
                if (pos + 1 < cur_str.length() && cur_str[pos + 1] == 'h')
                {
                    cur_format.len = 'H';
                    pos++;
                } else
                {
                    cur_format.len = 'h';
                }
                break;
            case 'l':
                if (pos + 1 < cur_str.length() && cur_str[pos + 1] == 'l')
                {
                    cur_format.len = 'U';
                    pos++;
                } else
                {
                    cur_format.len = 'l';
                }
                break;
            case 'j':
                cur_format.len = 'j';
                break;
            case 'z':
                cur_format.len = 'z';
                break;
            case 't':
                cur_format.len = 't';
                break;
            case 'L':
                cur_format.len = 'L';
                break;
            default:
                throw invalid_argument("Invalid length param");
        }
    }
}

template<typename S>
void parse_int(struct format_s &cur_format, S arg, stringstream &output)
{
    if (!cur_format.is_zero && !cur_format.is_space)
        cur_format.is_zero = true;
    if (cur_format.width <= 0)
        cur_format.width = cur_format.precision;
    if (cur_format.width > 0 && cur_format.precision > 0)
    {
        output << setw(cur_format.width - cur_format.precision) << setfill(' ') << "";
        if (cur_format.is_positive)
        {
            char ch = cur_format.is_zero ? '0' : ' ';
            output << setw(cur_format.precision) << setfill(ch);
        } else
            output << setw(cur_format.precision) << setfill('0');
    }
    int64_t u;
    switch (cur_format.len)
    {
        case 'H':
            u = parsing<unsigned char>(arg);
            break;
        case 'h':
            u = parsing<unsigned short int>(arg);
            break;
        case 'l':
            u = parsing<unsigned long int>(arg);
            break;
        case 'U':
            u = parsing<unsigned long long int>(arg);
            break;
        case 'j':
            u = parsing<uintmax_t>(arg);
            break;
        case 'z':
            u = parsing<size_t>(arg);
            break;
        case 't':
            u = parsing<ptrdiff_t>(arg);
            break;
        case ' ':
            u = parsing<unsigned int>(arg);
            break;
        default:
            throw invalid_argument("Invalid len param for integer specifier");
    }
    output << u;
}

template<typename S>
void parse_double(struct format_s &cur_format, S arg, stringstream &output)
{
    if (!cur_format.is_zero && !cur_format.is_space)
        cur_format.is_zero = true;
    double f;
    switch (cur_format.len)
    {
        case 'l':
        case ' ':
            f = parsing<double>(arg);
            break;
        case 'L':
            f = parsing<long double>(arg);
            break;
        default:
            throw invalid_argument("Invalid len param for given specifier");
    }
    output << f;
}

template<typename S>
void parse_a(struct format_s &cur_format, S arg, stringstream &output)
{
    double f;
    switch (cur_format.len)
    {
        case 'l':
        case ' ':
            f = parsing<double>(arg);
            break;
        case 'L':
            f = parsing<long double>(arg);
            break;
        default:
            throw invalid_argument("Invalid len param for given specifier");
    }
    char *buf = new char[1024];
    string s = "%";
    if (cur_format.is_zero) s += '0';
    if (cur_format.is_positive) s += '+';
    if (cur_format.is_negative) s += '-';
    if (cur_format.is_space) s += ' ';
    if (cur_format.width > 0) s += to_string(cur_format.width);
    if (cur_format.precision > 0) s += '.', s += to_string(cur_format.precision);
    s += cur_format.spec;
    snprintf(buf, 1024, s.c_str(), f);
    output << buf;
}

template<typename S>
void parse_g(struct format_s &cur_format, S arg, stringstream &output)
{
    int32_t f;
    output << setfill(cur_format.is_zero ? '0' : ' ');
    switch (cur_format.len)
    {
        case 'l':
        case ' ':
            f = parsing<int>(arg);
            break;
        case 'L':
            f = parsing<long int>(arg);
            break;
        default:
            throw invalid_argument("Invalid len param for given specifier");
    }
    output << f;
}

template<typename T>
typename enable_if<!is_integral<T>::value && !is_convertible<T, string>::value &&
                   !is_pointer<T>::value, string>::type parse_at_symbol(const T &force)
{
    throw invalid_argument("Invalid argument");
}

template<typename T>
typename enable_if<is_integral<T>::value, string>::type parse_at_symbol(T force)
{
    return to_string(force);
}

template<typename T, int pos>
typename enable_if<!is_convertible<T *, string>::value, string>::type parse_at_symbol(const T (&arg)[pos])
{
    string outcome = "[";
    for (int i = 0; i < pos - 1; i++)
        outcome += to_string(arg[i]) + ", ";
    outcome += to_string(arg[pos - 1]) + ']';
    return outcome;
}

template<typename T>
typename enable_if<is_convertible<T, string>::value, string>::type parse_at_symbol(const T &force)
{
    return force;
}

template<typename T>
typename enable_if<!is_array<T>::value && !is_convertible<T, string>::value &&
                   is_pointer<T>::value, string>::type parse_at_symbol(T &force)
{
    string outcome = "";
    if (!force)
        outcome += "nullptr<" + (string) typeid(*force).name() + ">";
    else
        outcome += "ptr<" + (string) typeid(*force).name() + ">(" + format("%@", *force) + ")";
    return outcome;
}

template<typename S>
string get_substitute(const string &cur_str, uint &pos, struct format_s &cur_format, S arg, stringstream &output)
{
    cur_format.spec = cur_str[pos++];
    switch (cur_format.spec)
    {
        case 'i':
        case 'd':
            parse_int(cur_format, arg, output);
            break;
        case 'X':
            output << std::uppercase;
        case 'x':
            output << std::hex;
            parse_int(cur_format, arg, output);
            break;
        case 'o':
            output << std::oct;
            parse_int(cur_format, arg, output);
            break;
        case 'u':
            output << noshowpos;
            parse_int(cur_format, arg, output);
            break;
        case 'A':
        case 'a':
            parse_a(cur_format, arg, output);
            break;
        case 'G':
            output << std::uppercase;
        case 'g':
            output << std::setprecision(0);
            parse_g(cur_format, arg, output);
            break;
        case 'E':
            output << std::uppercase;
        case 'e':
            if (cur_format.is_space)
            {
                output << setw(1);
                output << " ";
                output << setw(cur_format.width);
            }
            output << fixed << std::scientific << setprecision(cur_format.precision);
            parse_double(cur_format, arg, output);
            break;
        case 'F':
            output << std::uppercase;
        case 'f':
            if (cur_format.is_space)
            {
                output << setw(1);
                output << " ";
                output << setw(cur_format.width);
            }
            if (cur_format.precision > 0 && cur_format.width > 0)
            {
                output << fixed;
                output << setprecision(cur_format.precision);
            } else if (cur_format.precision <= 0)
            {
                output << fixed;
                output << setprecision(6);
            }
            parse_double(cur_format, arg, output);
            break;

        case 'c':
            cur_format.is_zero = false;
            output << setfill(' ');
            switch (cur_format.len)
            {
                case 'l':
                    break;
                case ' ':
                    output << parsing<unsigned char>(arg);
                    break;
                default:
                    throw invalid_argument("Invalid len param for given specifier");
            }
            break;
        case 's':
        {
            string str;
            wstring wstr;
            cur_format.is_zero = false;
            output << setfill(' ');
            switch (cur_format.len)
            {
                case 'l':
                    break;
                case ' ':
                    str = parsing<string>(arg);
                    if (str.length() > (unsigned) cur_format.precision && cur_format.precision >= 0)
                        str = str.substr(0, cur_format.precision);
                    output << str;
                    break;
                default:
                    throw invalid_argument("Invalid len param for given specifier");
            }
        }
            break;
        case 'p':
            char null_p[8];
            if (cur_format.len != ' ')
                throw invalid_argument("Invalid len param for given specifier");
            snprintf(null_p, 2, "%p", parsing<void *>(arg));
            if (null_p[0] != '(' && parsing<void *>(arg) != NULL && parsing<void *>(arg) != nullptr)
                output << parsing<void *>(arg);
            else
                output << "(nil)";
            break;
        case '@':
            output << parse_at_symbol(arg);
            break;
    }

    return output.str();
}

string substitute(const string &cur_str, unsigned pos)
{
    return get_inter_sym(cur_str, pos, false);
}


template<typename T, typename... S>
string substitute(const string &cur_str, unsigned pos, const T &force, const S &... args)
{
    string begin = "";
    int p = pos;
    begin = get_inter_sym(cur_str, pos, true);
    struct format_s cur_format;

    get_flags(cur_str, pos, cur_format);

    if (pos < cur_str.length() && cur_str[pos] == '*')
    {
        string replace = cur_str.substr(p, pos - p);
        replace += to_string(parsing<int>(force));
        return substitute(replace + cur_str.substr(pos + 1), p, args...);
    }

    string cur = "";
    while (pos < cur_str.length() && isdigit(cur_str[pos]))
        cur += cur_str[pos++];
    if (!cur.empty())
        cur_format.width = stoi(cur);

    cur = "";
    if (pos < cur_str.length() - 1 && cur_str[pos] == '.')
    {
        pos++;
        if (cur_str[pos] == '*')
        {
            string replace = cur_str.substr(p, pos - p);
            replace += to_string(parsing<int>(force));
            return substitute(replace + cur_str.substr(pos + 1), p, args...);
        } else
        {
            if (cur_str[pos] == '-')
                throw invalid_argument("Invalid precision");
            cur_format.precision = 0;
            while (pos < cur_str.length() && isdigit(cur_str[pos]))
                cur += cur_str[pos++];
            if (!cur.empty())
            {
                cur_format.precision = stoi(cur);
            }
        }
    }

    get_len_type(cur_str, pos, cur_format);

    if (cur_format.len != ' ')
        pos++;

    if (pos < cur_str.length() && cur_format.len_types.find(cur_str[pos]) != string::npos)
        throw invalid_argument("Invalid length param!");

    if (pos == cur_str.length())
        throw invalid_argument("Specifier missed!");

    stringstream output;
    if (cur_format.is_positive)
        output << showpos;
    if (cur_format.is_zero)
        output << setfill('0');
    if (cur_format.is_space)
        output << setfill(' ');
    if (cur_format.width > 0)
        output << setw(cur_format.width);
    if (cur_format.is_negative)
        output << left;
    if (cur_format.is_sharp)
        output << showbase;
    output << showpoint;
    string res = get_substitute(cur_str, pos, cur_format, force, output);
    string next = substitute(cur_str, pos, args...);
    return begin + res + next;
}

template<typename... Args>
string format(const string &cur_str, const Args &... args)
{
    return substitute(cur_str, 0, args...);
}

#endif //TASK4_FORMAT_H 