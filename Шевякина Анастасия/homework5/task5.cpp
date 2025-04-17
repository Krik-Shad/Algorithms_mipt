#include <iostream>
#include <vector>
#include <algorithm>

std::ostream& operator<< (std::ostream &os, const std::vector<int>& a)
{
    os<<"{";
    for (int i{0}; i<a.size(); ++i)
    {
        os<<" "<<a[i]<<", ";
    }
    os<<"}"<<std::endl;
    return os;
}

std::vector<int> find_mins(int k, int n)
{
    std::vector<int> buffer(k);
    for (int i{0}; i<n; ++i)
    {
        int num;
        std::cin>>num;
        if (i<k)
            buffer[i] = num;
        else
        {
            std::make_heap(buffer.begin(), buffer.end());
            if (num<buffer[0])
            {
                std::pop_heap(buffer.begin(), buffer.end());
                buffer.pop_back();
                buffer.push_back(num);
                std::push_heap(buffer.begin(), buffer.end());
            }
        }
    }
    std::sort_heap(buffer.begin(), buffer.end());
    return buffer;
}

int main()
{
    int n;
    std::cin>>n;
    int k;
    std::cin>>k;
    std::cout<<find_mins(k, n);

    return 0;
}