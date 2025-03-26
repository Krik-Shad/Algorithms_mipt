#include <iostream>
#include <vector>
#include <algorithm>

std::ostream& operator<< (std::ostream &os, const std::vector<int>& a)
{
    // os<<"{";
    for (int i{0}; i<a.size(); ++i)
    {
        os<<a[i]<<" ";
    }
    os<<std::endl;
    return os;
}

std::vector<int> find_max(const std::vector<int>& a, int k)
{
    std::vector<int> result;
    std::vector<int> heap;
    for (int i{0}; i<k; ++i)
    {
        heap.push_back(a[i]);
    }
    std::make_heap(heap.begin(), heap.end());
    for (int i(k-1); i<a.size(); ++i)
    {
        result.push_back(heap[0]);
        std::remove(heap.begin(), heap.end(), a[i-k]);
        heap.push_back(a[i+1]);
        std::push_heap(heap.begin(), heap.end());
    }
    return result;
}

int main()
{
    int n, k;
    std::cin>>n;
    std::vector<int> screen(n);
    for (int i{0}; i<n; ++i)
    {
        std::cin>>screen[i];
    }
    std::cin>>k;
    std::cout<<find_max(screen, k)<<std::endl;
    return 0;
}