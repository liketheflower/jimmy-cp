// https://www.luogu.com.cn/problem/P3372
// This is a standard segment tree problem. The supported operations are: range update and range sum query.

#include <iostream>
#include <vector>
using namespace std;
using LL = long long;
const int N = 1e5 + 10;
int a[N];
struct segment_tree{
    int l, r;
    LL sum;
    LL lazy;
}tree[N << 2];

void build(int u, int l, int r) {
    tree[u].l = l;
    tree[u].r = r;
    if (l == r) {
	tree[u].sum = a[l];
	return;
    }
    int mid = (l + r) >> 1;
    int L = u << 1, R = u << 1 | 1;
    build(L, l, mid);
    build(R, mid + 1, r);
    tree[u].sum = tree[L].sum + tree[R].sum;
}

void pushdown(int u) {
    int l = tree[u].l, r = tree[u].r;
    int mid = (l + r) >> 1;
    int L = u << 1, R = u << 1 | 1;
    tree[L].sum += tree[u].lazy * (mid - l + 1);
    tree[R].sum += tree[u].lazy * (r - mid);
    tree[L].lazy += tree[u].lazy;
    tree[R].lazy += tree[u].lazy;
    tree[u].lazy = 0;
}

void update(int u, int x, int y, int k) {
    int l = tree[u].l, r = tree[u].r;
    if (x <= l && r <= y) {
	tree[u].sum += k * (r - l + 1);
	tree[u].lazy += k;
	return;
    }
    pushdown(u);
    int mid = (l + r) >> 1;
    int L = u << 1, R = u << 1 | 1;
    if (x <= mid) {
	update(L, x, y, k);
    }
    if (y > mid) {
	update(R, x, y, k);
    }
    tree[u].sum = tree[L].sum + tree[R].sum;
    return;
}

LL query(int u, int x, int y) {
    int l = tree[u].l, r = tree[u].r;
    if (x <= l && r <= y) {
	return tree[u].sum;
    }
    pushdown(u);
    int mid = (l + r) >> 1;
    int L = u << 1, R = u << 1 | 1;
    LL ret = 0;
    if (x <= mid) {
	ret += query(L, x, y);
    }
    if (y > mid) {
	ret += query(R, x, y);
    }
    return ret;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
	cin >> a[i];
    }
    build(1, 1, n);
    int op, x, y, k;
    vector<LL> ret;
    while (m--) {
	cin >> op;
	if (op == 1) {
	    cin >> x >> y >> k;
	    update(1, x, y, k);
	} else {
	    cin >> x >> y;
	    ret.push_back(query(1, x, y));
	}
    }
    for (auto x : ret) {
	cout << x << endl;
    }
    return 0;
}
