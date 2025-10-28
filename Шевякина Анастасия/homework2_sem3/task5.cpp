#include <iostream>
#include <vector>
#include <queue>

int bfs_count_paths(const std::vector<std::vector<int>> &g, int start, int end)
{
    std::vector<int> dist(g.size(), -1);
    std::vector<int> count(g.size(), 0);
    
    std::queue<int> q;
    q.push(start);
    dist[start] = 0;
    count[start] = 1;
    
    while(!q.empty())
    {
        int v = q.front();
        q.pop();
        
        for(int u : g[v])
        {
            if(dist[u] == -1)
            {
                dist[u] = dist[v] + 1;
                count[u] = count[v];
                q.push(u);
            }
            else if(dist[u] == dist[v] + 1) 
            {
                count[u] += count[v];
            }
        }
    }
    
    return count[end];
}

int main() 
{
    int V, E;
    std::cin>>V>>E;
    
    std::vector<std::vector<int>> g(V);
    
    for (int i = 0; i < E; i++) 
    {
        int u, v;
        std::cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    int start_v, end_v;
    std::cin>>start_v>>end_v;
    
    int result = bfs_count_paths(g, start_v, end_v);
    std::cout<<result<<std::endl;
    
    return 0;
}