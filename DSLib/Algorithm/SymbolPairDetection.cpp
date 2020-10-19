#include "SymbolPairDetection.h"
#include "Stack/LinkStack.h"

namespace DSLib {

bool is_left(char c)
{
    return (c == '(') || (c == '[') || (c == '{') || (c == '<');
}

bool is_right(char c)
{
    return (c == ')') || (c == ']') || (c == '}') || (c == '>');
}

bool is_quot(char c)
{
    return (c == '\'') || (c == '\"');
}

bool is_match(char l, char r)
{
    return ((l == '(') && (r == ')'))   ||
           ((l == '[') && (r == ']'))   ||
           ((l == '{') && (r == '}'))   ||
           ((l == '<') && (r == '>'))   ||
           ((l == '\'') && (r == '\'')) ||
           ((l == '\"') && (r == '\"'));
}

bool scan(const char * code)
{
    LinkStack<char> ls;
    bool ret = true;
    int i = 0;

    code = (code == nullptr) ? "" : code;

    while (code[i] != '\0' && ret)
    {
        if (is_left(code[i]))
        {
            ls.push(code[i]);
        }
        else if (is_right(code[i]))
        {
            if (ls.size() > 0 && is_match(ls.top(), code[i]))
            {
                ls.pop();
            }
            else
            {
                ret = false;
            }
        }
        else if (is_quot(code[i]))
        {
            if (ls.size() == 0 || !is_match(ls.top(), code[i]))
            {
                ls.push(code[i]);
            }
            else if (is_match(ls.top(), code[i]))
            {
                ls.pop();
            }
        }
        else
        {

        }
        i++;
    }

    return ret && (ls.size() == 0);
}

}
