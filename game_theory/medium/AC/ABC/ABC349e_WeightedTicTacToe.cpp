// problem link: https://atcoder.jp/contests/abc349/tasks/abc349_e
#include<iostream>
#include<vector>
using namespace std;
using LL = long long;
using PII = pair<int, int>;
const int A_WIN = 1, B_WIN =2, TIE = 0;
int get_ij(int i, int j){
    return i * 3 + j;
}
PII decode(int ij){
    return {ij / 3, ij % 3};
}

bool good(vector<vector<int>>&a){
    // check row all 1s?
    for (int i = 0; i < 3; ++i){
	if (a[i][0] == 1 and a[i][1] == 1 and a[i][2] == 1){
	    return true;
	}
    }
    // check column all 1s?
    for (int j = 0; j < 3; ++j){
	if (a[0][j] == 1 and a[1][j] == 1 and a[2][j] == 1){
	    return true;
	}
    }
    // check diagonal all 1 s?
    if (a[0][0] == 1 and a[1][1] == 1 and a[2][2] == 1){
	return true;
    }
    // check anti-diagonal all 1s?
    if (a[0][2] == 1 and a[1][1] == 1 and a[2][0] == 1){
	return true;
    }

    return false;
}
int dp(int i, int j, int mask, LL A_SCORE, LL B_SCORE, vector<vector<int>>&grids, vector<vector<int>>&red, vector<vector<int>>&blue, int turn){
    mask |= (1 << get_ij(i, j));
    if (turn == 0){
	red[i][j] = 1;
	A_SCORE += grids[i][j];
    }
    else{
	blue[i][j] = 1;
	B_SCORE += grids[i][j];
    }
    if (__builtin_popcount(mask) == 9){
	if (A_SCORE > B_SCORE){
	    return A_WIN ;
	}
	else if (A_SCORE < B_SCORE){
	    return B_WIN;
	}
	else{
	    return  TIE;
	}
    }
    if (turn == 0){
	if (good(red)){
	    return A_WIN ;
	}
    } else {
	if (good(blue)){
	    return B_WIN;
	}
    }
    int next_turn = 1- turn;
    for (int idx = 0; idx < 9; ++idx){
	if (mask & (1 << idx)){
	    continue;
	}
	auto [ii, jj] = decode(idx);
	int ret = dp(ii, jj, mask, A_SCORE, B_SCORE, grids, red, blue, next_turn);
	if (next_turn == 0){
	    red[ii][jj] = 0;
	} else {
	    blue[ii][jj] = 0;
	}
	if (ret == A_WIN && next_turn == 0){
	    return A_WIN;
	}
	if (ret ==B_WIN && next_turn == 1){
	    return B_WIN;
	}
    }
    if (turn == 0){
	return A_WIN;
    } else {
	return B_WIN;
    }
}
int main(){
    vector<vector<int>> grids(3, vector<int>(3, 0));
    for (int i = 0; i < 3; i++){
	for (int j = 0; j < 3; j++){
	    cin >> grids[i][j];
	}
    }
    LL A_SCORE = 0, B_SCORE = 0;
    int ret = B_WIN;
    int mask = 0;
    int ij;
    for (int i = 0; i < 3;++i){
	for (int j = 0; j < 3; ++j){
	    vector<vector<int>> red(3, vector<int>(3, 0));
	    vector<vector<int>> blue(3, vector<int>(3, 0));
	    ij	 = get_ij(i, j);
	    ret = dp(i, j, mask, A_SCORE, B_SCORE, grids, red, blue, 0);
	    if (ret == A_WIN){
		cout << "Takahashi" << endl;
		return 0;
	    }
	}
    }
    cout << "Aoki" << endl;
    return 0;
}
