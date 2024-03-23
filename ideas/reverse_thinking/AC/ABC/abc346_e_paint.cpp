// https://atcoder.jp/contests/abc342/tasks/abc342_e
#include<iostream>
#include<vector>
#include<map>
using namespace std;
using LL = long long;
int main(){
    int H, W, M;
    cin >> H >> W >> M;
    vector<vector<int>> query(M, vector<int>(3));
    for (int i = 0; i < M; i++){
        cin >> query[i][0] >> query[i][1] >> query[i][2];
    }
    int q, idx, x;
    map<int, LL> cnt;
    LL tot = (LL)H*W;
    vector<int> row(H, 0), col(W, 0);
    for (int i = M - 1; i >= 0; i--){
        q = query[i][0];
        idx = --query[i][1];
        x = query[i][2];
        if (q == 1){ // row
            if (row[idx]) continue;  
            row[idx] = 1;
            cnt[x] += (LL)W;
            H --;
        } else {// column
            if (col[idx]) continue;    
            col[idx] = 1;
            cnt[x] += (LL)H;
            W --;
        }
    }
    for (auto [k, v] : cnt){
        if (k !=0)tot -= v;
    }
    cnt[0] = tot;
    if (cnt[0] == 0){
        cnt.erase(0);
    }
    int  zero = 0;
    for (auto [k, v] : cnt){
        if (v == 0){
            zero++;
        }
    }
    cout << (int)cnt.size()  - zero<< endl;
    for (auto [k, v] : cnt){
        if (v == 0) continue;
        cout << k << " " << v << endl;
    }
    return 0;
}


