// https://www.acwing.com/problem/content/1277/ 
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 200010;

int m, p;
struct Node
{
    int l, r;
    int v;  // max number in [l, r]
}tr[N * 4];

void pushup(int u)  // update parent node from children nodes.
{
    tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
}

void build(int u, int l, int r)
{
    tr[u] = {l, r};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

int query(int u, int l, int r)
{
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;   // this node's[L, R] is in [l, r]

    int mid = tr[u].l + tr[u].r >> 1;
    int v = 0;
    if (l <= mid) v = query(u << 1, l, r);
    if (r > mid) v = max(v, query(u << 1 | 1, l, r));

    return v;
}

void modify(int u, int x, int v)
{
    if (tr[u].l == x && tr[u].r == x) tr[u].v = v;
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) modify(u << 1, x, v);
        else modify(u << 1 | 1, x, v);
        pushup(u);
    }
}


int main()
{
    int n = 0, last = 0;
    cin >> m >> p;
    build(1, 1, m);

    int x;
    string op;
    while (m -- )
    {
        cin >> op >>x;
        if (op == "Q")
        {
            last = query(1, n - x + 1, n);
            cout << last << endl;
        }
        else
    {
            modify(1, n + 1, ((LL)last + x) % p);
            n ++ ;
        }
    }

    return 0;
}

