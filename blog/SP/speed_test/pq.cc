#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct data
{
    int v, w;
};
const int MAXN = 1e5 + 10;
int dis[MAXN];
bool inque[MAXN];
vector<data> g[MAXN];
int n, m, s;
inline void spfa()
{
    for (int i = 1; i <= MAXN; i++)
        dis[i] = 0x7fffffff;
    dis[s] = 0;
    priority_queue<int> q;
    q.push(s);
    inque[s] = true;
    while (!q.empty())
    {
        int u = q.top();
        q.pop();
        inque[u] = false;
        for (int i = 0; i < g[u].size(); i++)
        {
            int next = g[u][i].v;
            int w = g[u][i].w;
            if (dis[u] + w < dis[next])
            {
                dis[next] = dis[u] + w;
                if (!inque[next])
                {
                    q.push(next);
                    inque[next] = true;
                }
            }
        }
    }
}
int main()
{
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back((data){v, w});
    }
    spfa();
    for (int i = 1; i <= n; i++)
        printf("%d ", dis[i]);
    return 0;
}