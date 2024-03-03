//https://leetcode.com/contest/weekly-contest-387/problems/distribute-elements-into-two-arrays-ii/
//Solution is adjusted from https://cp-algorithms.com/data_structures/fenwick.html

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
	    for (++idx; idx < n; idx += idx & -idx)
		bit[idx] += delta;
	}
};


class Solution {
    public:
	vector<int> resultArray(vector<int>& nums) {
	    // discretization
	    std::vector<int> tmp(nums);  
	    sort(tmp.begin(), tmp.end());
	    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
	    unordered_map<int, int> old_new;
	    const int m = tmp.size();
	    for (int i = 0; i < m;++i){
		old_new[tmp[i]] = i;
	    }

	    const int n = nums.size();
	    // one based index, as when the checking number is the maximum one, we need add by 1 which is m + 1,
	    // we have 0 to m + 1 which in total is m + 2 numbers
	    const int M = m + 2;
	    FenwickTreeOneBasedIndexing ft1(M), ft2(M);

	    ft1.add(old_new[nums[0]], 1); ft2.add(old_new[nums[1]], 1);
	    vector<int> arr1, arr2;
	    arr1.push_back(nums[0]);arr2.push_back(nums[1]);
	    int cnt_a = 0, cnt_b = 0;
	    for (int i = 2; i < n; ++i){
		auto x = nums[i];
		int x_ = old_new[x];  
		cnt_a = ft1.sum(x_+1,m+1);cnt_b = ft2.sum(x_+1, m+1);

		if (cnt_a > cnt_b){
		    arr1.push_back(x);
		    ft1.add(x_, 1);

		} else if (cnt_a < cnt_b){
		    arr2.push_back(x);
		    ft2.add( x_, 1);

		} else {
		    if (arr2.size() < arr1.size()){
			arr2.push_back(x);
			ft2.add(x_, 1);

		    } else {
			arr1.push_back(x);
			ft1.add( x_, 1);
		    }
		}

	    }

	    for (auto x: arr2){
		arr1.push_back(x);
	    }  
	    return arr1;
	}
};
