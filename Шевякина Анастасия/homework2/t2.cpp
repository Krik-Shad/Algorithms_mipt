#include <stack>
#include <string>
string simplifyPath(std::string path) {
    std::stack<std::string> words;
    for (int i{0}; i<path.size(); ++i)
    {
        if (path[i] == '/')
            continue;
        std::string current;
        while (i<path.size() && path[i]!='/')
        {
            current += path[i];
            ++i;
        }
        if (current == ".")
            continue;
        else if (current == "..")
        {
            if (!words.empty())
                words.pop();
        }
        else {
            words.push(current);
        }
    }
    std::string result;
    // int n = words.size();
    while (!words.empty()) {
        result = "/" + words.top() + result;
        words.pop();
    }
    if (result=="") result = "/";
    return result;
}