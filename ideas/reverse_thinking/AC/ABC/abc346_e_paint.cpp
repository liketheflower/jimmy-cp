// https://atcoder.jp/contests/abc346/tasks/abc346_e

#include<iostream>
#include<unordered_set>
#include<vector>
#include<map>
using namespace std;
using LL = long long;


class FenwickTreeOneBasedIndexing {
public:
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTreeOneBasedIndexing(int n) {
	this->n = n + 1;
	bit.assign(n + 1, 0);
    }

    FenwickTreeOneBasedIndexing(vector<int> a)
    : FenwickTreeOneBasedIndexing(a.size()) {
	for (size_t i = 0; i < a.size(); i++)
	    add(i, a[i]);
    }

    int sum(int idx) {
	int ret = 0;
	for (++idx; idx > 0; idx -= idx & -idx)
	    ret += bit[idx];
	return ret;
    }

    int sum(int l, int r) {
	return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
	for (++idx; idx < n; idx += idx & -idx){
	    bit[idx] += delta;}
    }
};





int main(){
    int H, W, M;
    cin >> H >> W >> M;
    vector<vector<int>> query(M, vector<int>(3));
    for (int i = 0; i < M; i++){
	cin >> query[i][0] >> query[i][1] >> query[i][2];
    }
    FenwickTreeOneBasedIndexing ft1(H), ft2(W);
    for (int i = 0; i < H; i++){
	ft1.add(i, 1);
    }
    for (int i = 0; i < W; i++){
	ft2.add(i, 1);
    }
    int q, idx, x;
    map<int, LL> cnt;
    LL tot = (LL)H*(LL)W;
    vector<int> seen_row(H+1, 0), seen_col(W+1, 0);
    for (int i = M - 1; i >= 0; i--){
	q = query[i][0];
	idx = --query[i][1];
	x = query[i][2];
	if (q == 1){ // row
	    if(!seen_row[idx]){ft1.add(idx, -1); seen_row[idx] = 1;
		cnt[x] += (LL)ft2.sum(W-1);}
    } else {// column
	    if(!seen_col[idx]){ft2.add(idx, -1); seen_col[idx] = 1;
		cnt[x] += (LL)ft1.sum(H-1);}
	}
    }
    for (auto [k, v] : cnt){
	if (k !=0)tot -= v;
    }
    cnt[0] = tot;
    unordered_set<int> need_remove;
    for (auto [k, v] : cnt){
	if (v ==0ll)need_remove.insert(k);
    }
    cout << cnt.size()  - need_remove.size()<< endl;
    for (auto [k, v] : cnt){
	if (need_remove.count(k)) continue;
	cout << k << " " << v << endl;
    }
    return 0;
}
