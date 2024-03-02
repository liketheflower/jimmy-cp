# https://atcoder.jp/contests/abc342/tasks/abc342_d
#include<iostream>
#include<vector>
#include<map>
using namespace std;
using LL = long long;
vector<int> minp, primes;


/*
 * Sieve of Eratosthenes
 * minp[i] = smallest prime factor of i
 * primes = list of primes
 * time complexity: O(n log log n)
 */
void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();
    for (int i = 2; i <= n; i++) {
	if (minp[i] == 0) {
	    minp[i] = i;
	    primes.push_back(i);
	}
	for (auto p : primes) {
	    if (i * p > n) {
		break;
	    }
	    minp[i * p] = p;
	    if (p == minp[i]) {
		break;
	    }
	}
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    sieve(2E5);
    map<int, int> f;
    LL ret = 0;
    int zero = 0;
    for (int i = 0; i < N; i++) {
	int num;
	cin >> num;
	if (num == 0) {
	    zero++;
	    continue;
	}
	for (auto p : primes) {
	    if (p * p > num) {
		break;
	    }
	    while (num % (p * p) == 0) {
		num /= (p * p);
	    }
	}
	ret += f[num]++;
    }

    ret += 1LL * zero * (N - zero);
    ret += 1LL * zero * (zero - 1) / 2;
    cout << ret << endl;

    return 0;
}
