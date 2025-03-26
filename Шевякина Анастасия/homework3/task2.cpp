#include <iostream>
#include <vector>
#include <algorithm>

int find_amount(const std::vector<std::pair<int, int>>& a)
{
    std::vector<int> outs;
    outs.push_back(a[0].second);
    std::make_heap(outs.begin(), outs.end());
    int am = 0;
    for (int i{0}; i<a.size(); ++i)
    {
        int n = outs.size()-1;
        if (a[i].first <= outs[n])
        {
            am+=1;
        }
        else
        {
            outs.pop_back();
        }

        outs.push_back(a[i].second);
        std::push_heap(outs.begin(), outs.end());
    }
    return am;
}

int main()
{
    int n;
    std::cin>>n;
    std::vector<std::pair<int, int>> buses (n);
    for (int i{0}; i<n; ++i)
    {
        std::cin>>buses[i].first>>buses[i].second;
    }
    std::cout<<find_amount(buses)<<std::endl;
    return 0;
}