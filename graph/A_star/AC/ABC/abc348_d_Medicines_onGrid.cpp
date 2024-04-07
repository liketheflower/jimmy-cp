// https://atcoder.jp/contests/abc348/tasks/abc348_d
// blog: https://jimmy-shen.medium.com/a-is-better-than-native-dfs-c08dc81c0302
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
using PII = pair<int, int>;
vector<PII> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
// this is optimized dfs solution with priority queue, it works. Essentially, it is an A* search algorithm
bool dfs(vector<string>&grid, vector<vector<int>>&medicine, vector<vector<int>>&life, PII end, int curr_life, int i, int j){
    priority_queue<pair<int, PII>> pq;
    pq.push({curr_life, {i, j}});
    while (!pq.empty()){
	auto [curr_life, pos] = pq.top();
	auto [ii, jj] = pos;
	pq.pop();
	if (end.first == ii && end.second == jj)return true;
	if (medicine[ii][jj] > curr_life){
	    curr_life = medicine[ii][jj];
	    medicine[ii][jj] = 0;
	}
	if (curr_life == 0)continue;
	if (curr_life <= life[ii][jj])continue;
	life[ii][jj] = curr_life;
	int r, c;
	for (auto [di, dj]: dirs){
	    r = ii + di;
	    c = jj + dj;
	    if (r >= 0 && r < (int)grid.size() && c >= 0 && c < (int)grid[0].size() && grid[r][c] != '#' && curr_life >= 1 && life[r][c] <= curr_life - 1){
		pq.push({curr_life - 1, {r, c}});
	    }
	}
    }
    return false;
}
/*
 * this is a native dfs solution, it works but will get TLE.
bool dfs1(vector<string>&grid, vector<vector<int>>&medicine, vector<vector<int>>&life, PII end, int curr_life, int i, int j){
    if (end.first == i && end.second == j)return true;
    if (medicine[i][j] > curr_life){
	curr_life = medicine[i][j];
	medicine[i][j] = 0;
    }
    if (curr_life == 0)return false;
    if (curr_life <= life[i][j])return false;
    life[i][j] = curr_life);
    int r, c;    
    for (auto [di, dj]: dirs){
	r = i +di;
	c = j + dj;
	if (r >= 0 && r < (int)grid.size() && c >= 0 && c < (int)grid[0].size() && grid[r][c] != '#' && curr_life >= 1 && life[r][c] <= curr_life - 1){
	    if (dfs(grid, medicine, life, end, curr_life - 1, r, c))return true;
	}
    }
    return false;
}
 */


int main(){
    int N, M;
    cin >> N >> M;
    vector<string>grid(N);
    for (int i = 0; i < N; i++)
    {
	cin >> grid[i];
    }
    int Q;
    cin >> Q;
    vector<vector<int>> medicine(N, vector<int>(M, 0));
    int ii, jj, mm;
    for (int i = 0; i < Q; i++){
	cin >> ii >> jj >> mm;
	ii--; jj--;
	medicine[ii][jj] = mm;
    }
    PII begin, end;
    for (int i = 0; i < N; i++){
	for (int j = 0; j < M; j++){
	    if (grid[i][j] == 'S'){begin = {i, j};}
	    if (grid[i][j] == 'T'){end = {i, j};}
	}
    }
    auto [ii_, jj_] = begin;
    vector<vector<int>> life(N, vector<int>(M, 0));
    auto ret = dfs(grid, medicine, life, end, 0, ii_, jj_);
    if (ret)cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}
