#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
struct edge
{
    int u, v, w;
};
const int MAXN = 2e3;
vector<edge> e;
int fa[MAXN];
int p[MAXN];
inline int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}
inline void merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    fa[fx] = fy;
}
inline bool cmp(edge x, edge y) { return x.w < y.w; }
inline void init()
{
    memset(p, 0, sizeof(p));
    for (int i = 0; i < MAXN; i++)
        fa[i] = i;
    e.clear();
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        init();
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> p[i];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                int w;
                cin >> w;
                e.push_back((edge){i, j, w + p[i] + p[j]});
            }
            for (int j = i; j < n; j++)
            {
                int dum;
                cin >> dum;
            }
        }
        sort(e.begin(), e.end(), cmp);
        int ans = 0;
        for (int i = 0; i < e.size(); i++)
        {
            int u = e[i].u;
            int v = e[i].v;
            int w = e[i].w;
            if (find(u) != find(v))
            {
                merge(u, v);
                ans += w;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}