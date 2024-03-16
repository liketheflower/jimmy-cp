// https://atcoder.jp/contests/abc305/tasks/abc305_e
// this code can AC
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
using PII = pair<int, int>;
int main() {
	int n, m , k; cin>>n>>m>>k;
	vector<bool> good(n+1, false);
	vector<vector<int>> g(n+1);
	int u, v;
	for(int i = 0; i < m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	priority_queue<PII> curr_level;
	vector<int> dist(n+1, -1);
	int p, h;
	for (int i = 0; i < k; i++) {
		cin >> p >> h;
		good[p] = true;
		dist[p] = h;
		curr_level.push({h, p});
	}
	while (!curr_level.empty()) {
		auto [h, p] = curr_level.top(); curr_level.pop();
		if (dist[p] > h) continue;
		for (auto nei: g[p]){
		if (dist[nei] < h - 1) {
				dist[nei] = h -1;
				curr_level.push({h-1, nei});
				good[nei] = true;
			} 
		}
	}
	vector<int>ret;
	for (int i = 1; i <= n; i++) {
		if (good[i])ret.push_back(i);
	}
	cout << ret.size() << endl;
	for (auto x : ret) cout << x << " ";
	cout << endl;
	return 0;
}
