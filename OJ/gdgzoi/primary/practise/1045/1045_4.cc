#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct data
{
    int v, w;
};
const int INF = 0x7fffffff;
vector<data> g[2010];
int love[1010][30];
int minn[2010];
int pre[2010];
int vol[30];
int n, b, s, t;
inline int EK_bfs()
{
    memset(minn, 127, sizeof(minn));
    for (int i = 0; i < 2010; i++)
        pre[i] = -1;
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i].v;
            int w = g[u][i].w;
            if (pre[v] == -1 && w > 0)
            {
                pre[v] = u;
                minn[v] = min(minn[u], w);
                q.push(v);
            }
        }
    }
    if (pre[t] == -1)
        return -1;
    return minn[t];
}
inline int EK()
{
    int ans = 0;
    while (1)
    {
        int tmp = EK_bfs();
        if (tmp == -1)
            break;
        ans += tmp;
        int u = t;
        while (u != s)
        {
            for (int i = 0; i < g[pre[u]].size(); i++)
            {
                if (g[pre[u]][i].v == u)
                {
                    g[pre[u]][i].w -= tmp;
                    break;
                }
            }
            bool flag = true;
            for (int i = 0; i < g[u].size(); i++)
            {
                if (g[u][i].v == pre[u])
                {
                    g[u][i].w += tmp;
                    flag = false;
                    break;
                }
            }
            if (flag)
                g[u].push_back((data){pre[u], tmp});
            u = pre[u];
        }
    }
    return ans;
}
inline void init()
{
    for (int i = 0; i < 2010; i++)
        g[i].clear();
}
int main()
{
    scanf("%d %d", &n, &b);
    s = 0;
    t = n + b + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= b; j++)
            scanf("%d", &love[i][j]);
    for (int i = 1; i <= b; i++)
        scanf("%d", &vol[i]);
    int ans = INF;
    for (int l = 1; l <= b; l++)
    {
        for (int r = l; r <= b; r++)
        {
            if (r - l > ans)
                continue;
            init();
            for (int i = 1; i <= n; i++)
            {
                g[s].push_back((data){i, 1});
                for (int j = l; j <= r; j++)
                    g[i].push_back((data){n + love[i][j], 1});
            }
            for (int i = 1; i <= b; i++)
                g[n + i].push_back((data){t, vol[i]});
            if (EK() >= n)
                ans = min(ans, r - l);
        }
    }
    printf("%d", ans + 1);
    return 0;
}