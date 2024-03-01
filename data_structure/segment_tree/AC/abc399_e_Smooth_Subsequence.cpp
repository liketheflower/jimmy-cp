// https://atcoder.jp/contests/abc339/tasks/abc339_e
// The solution is modified from the following link
// https://www.cnblogs.com/kongbursi-2292702937/p/13647619.html
// There is a medium blog to quick explain this solution
// https://jimmy-shen.medium.com/first-time-use-segment-tree-to-ac-a-problem-in-abc-121e4a9dc209
#include<stdio.h>                                                                       
#include<string.h>                                                                      
#include<iostream>                                                                      
#include<algorithm>                                                                     
#include<vector>                                                                        
using namespace std;                                                                    
#define ll long long                                                                    
const int MAX_LEN =1000000;                                                             
int seg_tree[MAX_LEN << 2];                                                             
int Lazy[MAX_LEN << 2];                                                                 
int arr[MAX_LEN];                                                                       
//从下往上更新 节点                                                                     
void push_up (int root) {                                                               
    seg_tree[root] = max(seg_tree[root << 1], seg_tree[root << 1 | 1]);      //最小值改min
}                                                                                       
//从上向下更新，左右孩子                                                                
void push_down (int root, int L, int R) {                                               
    if(Lazy[root]){                                                                     
        Lazy[root << 1] += Lazy [root];                                                 
        Lazy[root << 1 | 1] += Lazy[root];                                              
        int mid = (L + R) >> 1;                                                         
        seg_tree[root << 1] +=  Lazy[root] * (mid - L + 1);                             
        seg_tree[root << 1 | 1] += Lazy[root] * (R - mid);                              
        Lazy[root] = 0;                                                                 
    }                                                                                   
}                                                                                       
//建树                                                                                  
//[L,R]就是对应arr数组里面的数                                                          
void build (int root, int L, int R) {                                                   
    Lazy[root] = 0;                                                                     
    if(L == R) {                                                                        
        seg_tree[root] = arr[L];                                                        
        return ;                                                                        
    }                                                                                   
    int mid = (L + R) >> 1;                                                             
    build(root << 1, L, mid);                                                           
    build(root << 1 | 1, mid + 1, R);                                                   
    push_up(root);                                                                      
}                                                                                       

//区间查询                                                                              
//查找区间[LL,RR]的最大/小值                                                            
int query (int root, int L, int R, int LL, int RR) {                                    
    if (LL <= L && R <= RR) return seg_tree[root];                                      
    push_down(root, L, R);     //每次访问都去检查Lazy 标记                              
    int Ans = 0;                                                                        
    int mid = (L + R) >> 1;                                                             
    if(LL <= mid) Ans = max(Ans, query(root << 1, L, mid, LL, RR));    //最小值改min    
    if(RR > mid) Ans = max(Ans, query(root << 1 | 1, mid + 1, R, LL, RR)); //最小值改min
    return Ans;                                                                         
}                                                                                       
//区间修改 +-某值                                                                       
//使得区间[LL,RR]的值都加上val                                                          
void update_Interval(int root, int L, int R, int LL, int RR, int val){                  
    if (LL <= L && R <= RR) {                                                           
        Lazy[root] += val;                                                              
        seg_tree[root] += val * (R - L + 1);                                            
        return ;                                                                        
    }                                                                                   
    push_down(root, L, R);                                                              
    int mid = (L + R) >> 1;                                                             
    if (LL <= mid) update_Interval(root << 1, L, mid, LL, RR, val);                     
    if (RR > mid) update_Interval(root << 1 | 1, mid + 1, R, LL , RR, val);             
    push_up(root);                                                                      
}                                                                                       
//单点修改 可以改为某值，或者+-某值                                                     
//把pos位置的值改成val                                                                  
void update(int root, int L, int R, int pos, int val) {                                 
    if(L == R){                                                                         
        seg_tree[root] = val;    //点直接变为某值                                       
        return ;                                                                        
    }                                                                                   
    int mid = (L + R) >> 1;                                                             
    if(pos <= mid) update(root << 1, L, mid, pos, val);                                 
    else update(root << 1 | 1, mid + 1, R, pos, val);                                   
    push_up(root);                                                                      
}                                                                                       
int main()                                                                              
{                                                                                       
    int n,d;                                                                            
    scanf("%d%d",&n,&d);                                                                
    vector<int> nums(n+100, 0);                                                         
    int D = 1;                                                                          
    for(int i=1;i<=n;++i)                                                               
    {                                                                                   
        scanf("%d",&nums[i]);                                                           
        D = max(nums[i], D);                                                            
        arr[i] = 0;                                                                     
    }                                                                                   
    //cout << D << endl;                                                                
    build(1,1,D+100);                                                                   
    //cout << D << endl;                                                                
    int ret = 0;                                                                        

    for (int i = 1; i <=n; ++i)                                                         
    {                                                                                   
        int num = nums[i];                                                              
        int l = max(1, num - d);                                                        
        int r = min(D, num + d);                                                        
        int this_ret = query(1,1,D,l,r) + 1;                                            
        ret = max(ret, this_ret);                                                       
        update(1, 1, D, num, this_ret);                                                 
    }                                                                                   
    cout << ret << endl;                                                                
    return 0;                                                                           
}     
