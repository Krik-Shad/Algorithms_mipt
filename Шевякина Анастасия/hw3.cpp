#include <iostream>
#include <vector>
#include <map>

std::ostream& operator << (std::ostream & os, std::map<int, int> w)
{
    for ( const auto& element : w){
        os << "{ " << element.first << " : " << element.second << " }\n";
    }
    return os;
}

int search(const std::vector<int> &a)
{
    std::map<int, int> stack;
    for (size_t i(0); i < a.size(); ++i)
    {
        // std::cout<<a[i] << std::endl;
        // std::cout<<stack<<std::endl;
        if (stack.count(a[i]) == 1 && stack[a[i]] == 2)
            return a[i]; 
        stack[a[i]] = 2;
    }
    return -1;
}

int main()
{
    int n;
    std::cin>>n;
    std::vector<int> a(n);
    for (int i{0}; i<n; ++i)
    {
        std::cin>>a[i];
        // a.push_back(number);
    }
    std::cout<<search(a)<<std::endl;
    return 0;
}