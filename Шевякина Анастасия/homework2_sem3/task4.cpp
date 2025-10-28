#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

int min_for_strong(const std::vector<std::vector<int>>& g, int V) 
{
    std::vector<std::vector<int>> g_reversed(V);
    for (int i = 0; i < V; i++) 
    {
        for (int u : g[i]) 
        {
            g_reversed[u].push_back(i);
        }
    }

    std::vector<int> visited(V);
    std::vector<int> order;
    
    std::function<void(int)> dfs1=[&](int v) 
    {
        visited[v] = 1;
        for (int u : g[v]) 
        {
            if (!visited[u]) 
            {
                dfs1(u);
            }
        }
        order.push_back(v);
    };
    
    for (int i=0; i<V; i++) 
    {
        if (!visited[i]) 
        {
            dfs1(i);
        }
    }
    
    std::fill(visited.begin(), visited.end(), 0);
    std::reverse(order.begin(), order.end());
    
    std::vector<int> comp_id(V, -1);
    int comp_count = 0;
    
    std::function<void(int)> dfs2=[&](int v) 
    {
        visited[v] = 1;
        comp_id[v] = comp_count;
        for (int u : g_reversed[v]) 
        {
            if (!visited[u])
            {
                dfs2(u);
            }
        }
    };
    
    for (int v : order) 
    {
        if (!visited[v]) 
        {
            dfs2(v);
            comp_count++;
        }
    }
    
    if (comp_count == 1) return 0;
    
    std::vector<int> in_edge(comp_count), out_edge(comp_count);
    for (int i = 0; i < V; i++) 
    {
        for (int u : g[i]) 
        {
            if (comp_id[i]!=comp_id[u]) 
            {
                out_edge[comp_id[i]]++;
                in_edge[comp_id[u]]++;
            }
        }
    }
    
    int sources = 0, sinks = 0;
    for (int i = 0; i < comp_count; i++) 
    {
        if (in_edge[i] == 0) sources++;
        if (out_edge[i] == 0) sinks++;
    }
    
    return std::max(sources, sinks);
}

int main()
{
    int V, E;
    std::cin>>V>>E;
    std::vector<std::vector<int>> g(V);
    
    for (int i = 0; i < E; i++) 
    {
        int v, u;
        std::cin>>v>>u;
        g[v].push_back(u);
    }
    
    int result = min_for_strong(g, V);
    std::cout<<result<<std::endl;
    
    return 0;
}