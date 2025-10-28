#include <vector>
#include <functional>

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        size_t V = isConnected.size();
        std::vector<std::vector<int>> g(V);
        for (int i = 0; i< V; i++) 
        {
            for (int j = 0; j < V; j++) 
            {
                if (isConnected[i][j] == 1 && i != j) 
                {
                    g[i].push_back(j);
                }
            }
        }
        std::vector<std::vector<int>> g_reversed(V);
            for (int i=0; i <V; i++) 
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

        std::function<void(int)>dfs2=[&](int v) 
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
        return comp_count;
    }
};