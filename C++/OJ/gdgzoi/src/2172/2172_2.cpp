#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
struct edge
{
	int u, v, w;
};
vector<edge> e;
bool cmp(edge x, edge y)
{
	return x.w < y.w;
}
int fa[10000];
int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
void merge(int u, int v)
{
	int fu = find(u), fv = find(v);
	fa[fu] = fv;
}
int main()
{
	int ans = 0;
	for (int i = 0; i < 10000; i ++) fa[i] = i;
	int n;
	cin >> n;
	for (int i = 1; i <= n; i ++)
	{
		for (int j = 1; j <= n; j ++)
		{
			int w;
			cin >> w;
			e.push_back((edge){i, j, w});
		}
	}
	int q;
	cin >> q;
	int u, v;
	for (int i = 0; i < q; i ++)
	{
		cin >> u >> v;
		merge(u, v);
	}
	sort(e.begin(), e.end(), cmp);
	for (int i = 0; i < e.size(); i ++)
	{
		int u = e[i].u, v = e[i].v, w = e[i].w;
		if (find(u) != find(v))
		{
			merge(u, v);
			ans += w;
		}
	}
	cout << ans;
	return 0;
}