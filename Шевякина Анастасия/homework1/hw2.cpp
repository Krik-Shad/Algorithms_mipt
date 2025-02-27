#include <iostream>
#include <vector>
#include <stdexcept>

int binary_jump(int n, int k, const std::vector<char> & way)//std::string &way)
{

    if (n<=0) 
        throw std::runtime_error("n can't be less than 0");
    std::vector<int> results;
    int res;
    for (int i{0}; i<n; ++i)
    {
        if (way[i] == '1')
            results.push_back(i+1);
    }
    if (results.size() == 0) return n;
    int l{0}, r{results.size()};
    int mid((r+l)/2);
    while(l<r-1)
    {
        if (results[mid]*k < n)
            l = mid;
        else {
            for (int i{1}; i<=k; ++i)
            {
                if (way[i*results[mid]-1] == '0') {
                    res = -1;
                    break;
                }
                else if (i>r) res = results[mid];
            }
            if (res != -1) return results[mid];
        }
        
    }
    return -1;

}


int main()
try
{
    int n, k;
    std::vector<char> plan;
    std::cin>>n>>k;
    for (int i{0}; i < n-1; ++i)
    {
        char in;
        std::cin>>in;
        plan.push_back(in);
    };
    std::cout<<binary_jump(n, k, plan);
    return 0;
}
catch (std::exception& e)
{
    std::cerr<<e.what()<<std::endl;
    return 1;
}
catch (...)
{
    std::cerr<<"Unexpected error"<<std::endl;
    return 2;
}