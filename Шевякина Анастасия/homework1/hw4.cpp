#include <vector>
#include <iostream>

void find_bin(const std::vector<int>& a, const std::vector<int>& b)
{
    std::vector<int> result;
    for (size_t i{0}; i<b.size(); ++i)
    {
        int l{0}, r{1};
        while (r<a.size() && a[r]<=b[i])
        {
            r*=2;
        }
        // std::cout<<l << " : " << r<<std::endl;
        int mid{0};
        while (r-l>1)
        {
            mid = (l+r)/2;
            // std::cout<<"mid = "<<mid<<std::endl;
            if (a[mid]<b[i])
                l = mid;
            else 
                --r;
        }
        if (a[mid] != b[i]) std::cout<< "0"<<std::endl;
        else std::cout<<mid<<std::endl;
        result.push_back(mid);
    }
}

int main()
{
    int n, m;
    std::cin>>n>>m;
    std::vector<int> a(n);
    std::vector<int> b(m);
    for (int i{0}; i<n; ++i)
    {
        std::cin>>a[i];
    }
    for (int i{0}; i<m; ++i)
    {
        std::cin>>b[i];
    }
    find_bin(a, b);
    return 0;
}