#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1000010;
char s[N];
int n, sa[N], rk[N << 1], oldrk[N << 1], id[N], cnt[N];
int main()
{
    int i, m, p, w;
    scanf("%s", s + 1);
    n = strlen(s + 1);
    m = max(n, 300);
    //离散化
    for (i = 1; i <= n; ++i)
        ++cnt[rk[i] = s[i]];
    for (i = 1; i <= m; ++i)
        cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; --i)
        sa[cnt[rk[i]]--] = i;
    for (int i = 1; i <= n; i++)
        cout << sa[i];
    cout << "\n";
    //倍增基数排序
    for (w = 1; w < n; w <<= 1)
    {
        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; ++i)
            ++cnt[rk[(id[i] = sa[i]) + w]];
        for (i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i)
            sa[cnt[rk[id[i] + w]]--] = id[i];
        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; ++i)
            ++cnt[rk[id[i] = sa[i]]];
        for (i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i)
            sa[cnt[rk[id[i]]]--] = id[i];
        memcpy(oldrk, rk, sizeof(rk));
        for (p = 0, i = 1; i <= n; ++i)
        {
            if (oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
                rk[sa[i]] = p;
            else
                rk[sa[i]] = ++p;
        }
    }
    for (i = 1; i <= n; ++i)
        printf("%d ", sa[i]);
    puts("");
    return 0;
}