#include <iostream>
#include <stack>
class Solution {
public:
    string simplifyPath(string path) {
        std::stack<string> slash;
        std::stack<string> dots;
        std::stack<string> names;
        char last = '|';
        for (char i : path)
        {
            switch (i) 
            {
                case '/':
                {
                    if (dots.top() == "..")
                    {
                        if (!slash.empty()) slash.pop();
                        if (!names.empty()) names.pop();
                        dots.pop();
                    }
                    if (last != '/')
                    {
                        slash.push("/");
                        last = '/';
                    }
                    //else do nothing
                    break;
                }
                case '.':
                {
                    if (last == '.')
                    {
                        dots.pop();
                        dots.push("..");
                        break;
                    }
                    else if (last == '/')
                    {
                        dots.push(".");
                        last = '.';
                    }
                    else 
                    if (dots.top() != "..")
                        break;
                    else
                        continue;
                }
                default:
                {

                    string new_str = i;
                    if (last=='/' || (last == '.' && dots.top()!=".."))
                    {   
                        new_str = names.top() + new_str;
                        names.pop();
                    }
                    if (dots.top()==".." && i == '.')
                    {
                        if (names.top().contains(".")) new_str += "."
                        else
                    }

                    names.push(new_str);
                    last = i;
                    break;
                }
            }
        }
        if (names.size()<slash.size())
        {
            slash.pop();
        }
        string result("");
        int y = names.size()
        for (int i{0}; i < y; i++)
        {
            result = names.top() + result;
            result = slash.top() + result;
            names.pop();
            slash.pop();
        }
        return result;
    }
};