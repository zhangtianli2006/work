#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
struct node
{
    int next[26];
    int len;
    int sufflink;
    int num;
};
int len;
char s[MAXN];
node tree[MAXN];
int num;
int suff;
long long ans;
bool addLetter(int pos)
{
    int cur = suff, curlen = 0;
    int let = s[pos] - 'a';
    while (true)
    {
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
            break;
        cur = tree[cur].sufflink;
    }
    if (tree[cur].next[let])
    {
        suff = tree[cur].next[let];
        return false;
    }
    num++;
    suff = num;
    tree[num].len = tree[cur].len + 2;
    tree[cur].next[let] = num;
    if (tree[num].len == 1)
    {
        tree[num].sufflink = 2;
        tree[num].num = 1;
        return true;
    }
    while (true)
    {
        cur = tree[cur].sufflink;
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])
        {
            tree[num].sufflink = tree[cur].next[let];
            break;
        }
    }
    tree[num].num = 1 + tree[tree[num].sufflink].num;
    return true;
}
void initTree()
{
    num = 2;
    suff = 2;
    tree[1].len = -1;
    tree[1].sufflink = 1;
    tree[2].len = 0;
    tree[2].sufflink = 1;
}
int main()
{
    scanf("%s", s);
    len = strlen(s);
    initTree();
    for (int i = 0; i < len; i++)
    {
        addLetter(i);
        ans += tree[suff].num;
    }
    cout << ans << endl;
    return 0;
}