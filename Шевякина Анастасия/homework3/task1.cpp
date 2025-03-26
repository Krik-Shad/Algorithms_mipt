#include <iostream>
#include <vector>
#include <algorithm>

int find_min(std::vector<int>& a)
{
    int summary{0};
    while (a.size() > 1)
    {
        int m = a.size()-1;
        int s = a[m] + a[m-1];
        summary += s;
        a.pop_back();
        a.pop_back();
        a.push_back(s);
        std::push_heap(a.begin(), a.end());
    }
    return summary;
}

int main()
{
    int n;
    std::cin>>n;
    std::vector<int> heap(n);
    for (int i{0}; i<n; ++i)
    {
        std::cin>>heap[i];
    }
    std::sort(heap.begin(), heap.end());
    std::make_heap(heap.begin(), heap.end());
    std::cout<<find_min(heap)<<std::endl;
    return 0;
}