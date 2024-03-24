// https://leetcode.com/problems/longest-common-suffix-queries/description/
//  the foloowing solution will get MLE as this problem is very sensitive to memory.

const int INF= 1e6;
struct vertex {
    int idx;
    int len;
    vector<vertex*> child;
    vertex(){
        idx = INF;
        len = INF;
        child.assign(26, nullptr);
    }
};
class Trie {
    public:
    vertex* root;
    Trie() {
        root = new vertex();
    }
    void insert(string word, int idx) {
        vertex* curr = root;
        int this_len = word.size();
        if (this_len < curr -> len){
                curr -> idx = idx;
                curr -> len = this_len;
            }
            if (this_len == curr -> len){
                curr -> idx = min(idx, curr -> idx);
            }
        for (int i = 0; i < (int)word.size(); ++i) {
            int alphaNum = word[i] - 'a';
            if (curr->child[alphaNum] == nullptr) {
                curr->child[alphaNum] = new vertex();
            }
            curr = curr->child[alphaNum];
             if (this_len < curr -> len){
                curr -> idx = idx;
                curr -> len = this_len;
            }
            if (this_len == curr -> len){
                curr -> idx = min(idx, curr -> idx);
            }   
        }
    }
    
};

class Solution {
    public:
    void  reverse_s(vector<string>& words){
        int n = words.size();
        for (int i = 0; i < n;++i){
            reverse(words[i].begin(), words[i].end());
        }
    }

    int find_ret(string &word, vertex* curr){
        vector<string> ret;
        int i = 0;
        int n = word.size();
        while (true){
            if (i == n){
                return curr->idx;
            }
            int idx = word[i] - 'a';
            if (curr->child[idx ]== nullptr){
                return curr -> idx;
            } else {
                curr = curr->child[idx];
                i++;
            }
        }
        return 0;
    }
    vector<int> stringIndices(vector<string>& words, vector<string>& words2) {
        Trie trie;
        reverse_s(words);
        reverse_s(words2);
        const int n = words.size();
        for (int i = 0; i < n; ++i){
            trie.insert(words[i], i);
        }
        const int m = words2.size();
        vector<int> ret(m, 0);
        auto root = trie.root;
        for (int i = 0; i < m; ++i){
            ret[i] = find_ret(words2[i], root);
        }
        return ret;
    }
};
