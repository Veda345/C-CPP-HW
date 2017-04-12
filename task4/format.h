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
    int width = 0, precision = -1;
    char len = ' ';
    char spec;
    string specifiers = "diuoxXfFeEgGaAcspn";
    string len_types = "lhjztL";
    string flags = "-+ #0";
};

template<typename... Args>
string format(const string &fmt, const Args &... args);

template<typename In, typename... Out>
string substitute(const string &fmt, unsigned pos, const In &force, const Out &... args);

string substitute(const string &fmt, unsigned pos);

template<typename In, typename Out>
typename enable_if<is_convertible<Out, In>::value, In>::type parsing(Out force)
{
    return (In) force;
}

template<typename In, typename Out>
typename enable_if<!is_convertible<Out, In>::value, In>::type parsing(Out force)
{
    throw invalid_argument("Invalid argument type.");
}

string get_inter_sym(const string &fmt, unsigned &pos, bool hasArg)
{
    string sym = "";
    int p = pos;
    while (pos < fmt.length())
    {
        while (pos < fmt.length() && fmt[pos] != '%')
            pos++;
        sym += fmt.substr(p, pos - p);

        if (pos == fmt.length() - 1)
            throw invalid_argument("Invalid format");
        if (pos == fmt.length())
            return sym;

        if (fmt[++pos] == '%')
        {
            pos++;
            sym += '%';
            continue;
        } else
        {
            if (!hasArg)
                throw invalid_argument("Not enough args");
            return sym;
        }
    }
    return sym;
}

void get_flags(const string &fmt, uint &pos, struct format_s &_fmt)
{
    while (pos < fmt.length() && _fmt.flags.find(fmt[pos]) != string::npos)
        switch (fmt[pos++])
        {
            case '-':
                _fmt.is_negative = true;
                break;
            case '+':
                _fmt.is_positive = true;
                break;
            case ' ':
                _fmt.is_space = true;
                break;
            case '#':
                _fmt.is_sharp = true;
                break;
            case '0':
                _fmt.is_zero = true;
                break;
            default:
                throw invalid_argument("Invalid flag");
        }
}

void get_len_type(const string &fmt, uint &pos, struct format_s &_fmt)
{
    if (_fmt.len_types.find(fmt[pos]) != string::npos)
    {
        switch (fmt[pos])
        {
            case 'h':
                if (pos + 1 < fmt.length() && fmt[pos + 1] == 'h')
                {
                    _fmt.len = 'H';
                    pos++;
                } else
                {
                    _fmt.len = 'h';
                }
                break;
            case 'l':
                if (pos + 1 < fmt.length() && fmt[pos + 1] == 'l')
                {
                    _fmt.len = 'U';
                    pos++;
                } else
                {
                    _fmt.len = 'l';
                }
                break;
            case 'j':
                _fmt.len = 'j';
                break;
            case 'z':
                _fmt.len = 'z';
                break;
            case 't':
                _fmt.len = 't';
                break;
            case 'L':
                _fmt.len = 'L';
                break;
            default:
                throw invalid_argument("Invalid length param");
        }
    }
}

template<typename Out>
void parse_int(struct format_s &_fmt, Out arg, stringstream &output) {
    uintmax_t u;
    switch (_fmt.len)
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

template<typename Out>
string get_substitute(const string &fmt, uint &pos, struct format_s &_fmt, Out arg, stringstream &output)
{
    _fmt.spec = fmt[pos++];
    switch (_fmt.spec)
    {
        case 'i':
        case 'd':
            intmax_t res;
            switch (_fmt.len)
            {
                case 'H':
                    res = parsing<signed char>(arg);
                    break;
                case 'h':
                    res = parsing<short int>(arg);
                    break;
                case 'U':
                    res = parsing<long long int>(arg);
                    break;
                case 'l':
                    res = parsing<long int>(arg);
                    break;
                case 'j':
                    res = parsing<intmax_t>(arg);
                    break;
                case 'z':
                    res = parsing<size_t>(arg);
                    break;
                case 't':
                    res = parsing<ptrdiff_t>(arg);
                    break;
                case ' ':
                    res = parsing<int>(arg);
                    break;
                default:
                    throw invalid_argument("Invalid len param for integer specifier");
            }
            output << res;
            break;
        case 'X':
            output << std::uppercase;
        case 'x':
            output << std::hex;
            parse_int(_fmt, arg, output);
            break;
        case 'o':
            output << std::oct;
            parse_int(_fmt, arg, output);
            break;
        case 'u':
            parse_int(_fmt, arg, output);
            break;
        case 'E':
        case 'G':
        case 'A':
            output << std::uppercase;
        case 'e':
        case 'g':
        case 'a':
        case 'F':
        case 'f':
            double f;
            switch (_fmt.len)
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
            break;
        case 'c':
            switch (_fmt.len)
            {
                case 'l':
                    //
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
            switch (_fmt.len)
            {
                case 'l':
//                    wstr = parsing<wstring>(arg);
//                    output << wstr;
                    break;
                case ' ':
                    str = parsing<string>(arg);
                    if (str.length() > (unsigned) _fmt.precision && _fmt.precision >= 0)
                        str = str.substr(0, _fmt.precision);
                    output << str;
                    break;
                default:
                    throw invalid_argument("Invalid len param for given specifier");
            }
        }
            break;
        case 'p':
            char null_p[8];
            if (_fmt.len != ' ')
                throw invalid_argument("Invalid len param for given specifier");
            snprintf(null_p, 2, "%p", parsing<void *>(arg));
            if (null_p[0] != '(' && parsing<void *>(arg) != NULL && parsing<void *>(arg) != nullptr)
                output << parsing<void *>(arg);
            else
                output << "(nil)";
            break;

    }

    return output.str();
}

#endif //TASK4_FORMAT_H