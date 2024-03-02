// https://atcoder.jp/contests/abc342/tasks/abc342_e
#include<iostream>
#include<queue>
#include<vector>
#include<array>
using namespace std;
using LL = long long;
const LL INF = 4e18;
int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<array<int, 5>>> graph(n);
    for(int i = 0; i < m; i++){
        int l, d, k, c, A, B;
        cin >> l >> d >> k >> c >> A >> B;
        A--; B--;
        graph[B].push_back({A, l, d, k, c});
    }
    vector<LL> dist(n, -1);
    priority_queue<pair<LL, int>> pq;
    pq.push({INF, n-1});
    while(!pq.empty()){
        auto [dis, u] = pq.top();
        pq.pop();
        //  Since the weights of the edge are positive, 
        //  we can ensure the first time we reach a node is the longest time. 
        if(dist[u] != -1) continue;
        dist[u] = dis;
        for(auto [v, l, d, k, c] : graph[u]){
            LL this_dis = dis - c;
            if (l > this_dis) continue;
            /*
            * l + d*x <= this_dis -> x <= (this_dis - l) / d
            * x <= k - 1
            * what is the maximum x?
            */
            LL x = min(k - 1ll, (this_dis - l) / d);
            this_dis = l + d * x;
            pq.push({this_dis, v});
        }
    }
    for (int i = 0; i < n - 1; ++i){
        if (dist[i] == -1){
            cout << "Unreachable" << endl;
        }else {
            cout << dist[i] << endl;
        }
    }
    return 0;
}
/*
 * Takeaway:
 * 1) This problem is a variation of Dijkstra's algorithm.
 * Since the weights of the edge are positive, we can ensure the first time we reach a node is the longest time. 
*  2) Reverse thinking is critical to solve this problem. If we think from the beginning to the end, it is hard to solve the problem. Also, the graph has circles, it makes the problem more complicated. However, if we solve it from the end to the beginning, it is much easier. The circle issue can be solved naturally as the later one will for sure not be optimal. 
*  3) The Dijkstra's algorithm is a greedy algorithm. An optimized solution may appear in the later stage, however, this problem the first time to reach the node is alwarys the optimal solution. This is slightly difference.
*/
