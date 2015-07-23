#include <string>
#include <cassert>
#include <iostream>
using std::string;

int main(void) {
    // constructor
    {
        assert(string(5, 'a') == "aaaaa");
        assert(string("abc") == "abc");
        assert(string("abcdef", 3) == "abc");
        string str = "abcdef";
        assert(string(str, 3, 3) == "def");
    }
    // operator
    {
        string str = string("a") + string("b") + string("c");
        assert(str == "abc");
        assert(str[1] == 'b');
    }
    // iterator
    {
        string str = "abcdef";
        int i = 0;
        for (string::iterator it = str.begin(); it != str.end(); it++) {
            assert(*it == str[i++]);
        }
    }
    // capacity
    {
        string str = "abc";
        assert(str.length() == 3);
        assert(str.size() == 3);
        str.clear();
        assert(str.empty());
        assert(str.length() == 0);
        assert(str.size() == 0);
    }
    // element access
    {
        string str = "abc";
        assert(str.at(1) == 'b');
    }
    // find
    {
        string str = "abcdef";
        assert(str.find("cd", 0) == 2);
        assert(str.find("gh", 0) == string::npos);
    }
    // replace
    {
        string str = "abc123";
        string oldstr = "123";
        string newstr = "def";
        int pos = str.find(oldstr, 0);
        assert(str.replace(pos, oldstr.size(), newstr) == "abcdef");
    }
    // substr
    {
        string str = "abcdef";
        assert(str.substr(3) == "def");
    }
}
