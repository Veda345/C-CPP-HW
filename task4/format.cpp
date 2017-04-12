
#include "format.h"

using namespace std;

string implementation(const string &fmt, unsigned pos)
{
    return get_inter_sym(fmt, pos, false);
}


template<typename In, typename... Out>
string implementation(const string &fmt, unsigned pos, const In &force, const Out &... args)
{
    string begin = "";
    int p = pos;
    begin = get_inter_sym(fmt, pos, true);
    struct format_s _fmt;

    get_flags(fmt, pos, _fmt);

    if (pos < fmt.length() && fmt[pos] == '*')
    {
        string replace = fmt.substr(p, pos - p);
        replace += to_string(parsing<int>(force));
        return implementation(replace + fmt.substr(pos + 1), p, args...);
    }

    string cur = "";
    while (pos < fmt.length() && isdigit(fmt[pos]))
        cur += fmt[pos++];
    if (!cur.empty())
        _fmt.width = stoi(cur);

    cur = "";
    if (pos < fmt.length() - 1 && fmt[pos] == '.')
    {
        pos++;
        if (fmt[pos] == '*')
        {
            string replace = fmt.substr(p, pos - p);
            replace += to_string(parsing<int>(force));
            return implementation(replace + fmt.substr(pos + 1), p, args...);
        } else
        {
            if (fmt[pos] == '-')
                throw invalid_argument("Invalid precision");
            _fmt.precision = 0;
            while (pos < fmt.length() && isdigit(fmt[pos]))
                cur += fmt[pos++];
            if (!cur.empty())
                _fmt.precision = stoi(cur);
        }
    }

    get_len_type(fmt, pos, _fmt);

    if (_fmt.len != ' ')
        pos++;

    if (pos < fmt.length() && _fmt.len_types.find(fmt[pos]) != string::npos)
        throw invalid_argument("Invalid length param!");

    if (pos == fmt.length())
        throw invalid_argument("Specifier missed!");

    stringstream output;
    if (_fmt.is_positive) output << showpos;
    if (_fmt.is_zero)
        output << setfill('0');
    if (_fmt.is_space)
        output << setfill(' ');
    if (_fmt.width > 0)
        output << setw(_fmt.width);
    if (_fmt.precision >= 0)
    {
        output << fixed;
        output.precision(_fmt.precision);
    }
    if (_fmt.is_sharp)
        output << showbase << showpoint;

    string res = get_substitute(fmt, pos, _fmt, force, output);
    string next = implementation(fmt, pos, args...);
    return begin + res + next;
}

template<typename... Args>
string format(const string &fmt, const Args &... args)
{
    return implementation(fmt, 0, args...);
}
