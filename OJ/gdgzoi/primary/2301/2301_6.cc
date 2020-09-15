#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

const int MAXN = 1e5 + 10;
std::vector<int> ordered_value[600];
int value[MAXN];
int block[MAXN];
int block_size;
int tag[MAXN];
int n;

inline void commit(int k)
{
    ordered_value[k].clear();
    for (int i = (k - 1) * block_size + 1; i <= std::min(k * block_size, n); i++)
        ordered_value[k].push_back(value[i]);

    std::sort(ordered_value[k].begin(), ordered_value[k].end());
}

inline void add(int l, int r, int val)
{
    for (int i = l; i <= std::min(block[l] * block_size, r); i++)
        value[i] += val;
    commit(block[l]);

    if (block[l] != block[r])
    {
        for (int i = (block[r] - 1) * block_size + 1; i <= r; i++)
            value[i] += val;
        commit(block[r]);
    }

    for (int i = block[l] + 1; i <= block[r] - 1; i++)
        tag[i] += val;
}

inline int query(int l, int r, int val)
{
    int ans = 0;
    for (int i = l; i <= std::min(block[l] * block_size, r); i++)
        if (value[i] + tag[block[l]] < val)
            ans++;

    if (block[l] != block[r])
        for (int i = (block[r] - 1) * block_size + 1; i <= r; i++)
            if (value[i] + tag[block[r]] < val)
                ans++;

    for (int i = block[l] + 1; i <= block[r] - 1; i++)
    {
        int k = val - tag[i];
        ans += std::lower_bound(ordered_value[i].begin(), ordered_value[i].end(), k) - ordered_value[i].begin();
    }
    return ans;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n;
    block_size = std::sqrt(n);
    for (int i = 1; i <= n; i++)
        std::cin >> value[i];
    for (int i = 1; i <= n; i++)
    {
        block[i] = (i - 1) / block_size + 1;
        ordered_value[block[i]].push_back(value[i]);
    }
    for (int i = 1; i <= block[n]; i++)
        std::sort(ordered_value[i].begin(), ordered_value[i].end());

    for (int i = 1; i <= n; i++)
    {
        int op, l, r, val;
        std::cin >> op >> l >> r >> val;
        if (op == 0)
            add(l, r, val);
        else
            std::cout << query(l, r, val * val) << "\n";
    }
    return 0;
}