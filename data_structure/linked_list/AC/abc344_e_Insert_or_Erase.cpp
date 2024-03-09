// https://atcoder.jp/contests/abc344/tasks/abc344_e
#include <bits/stdc++.h>
using namespace std;

// structure to define a node of the doubly linked list
struct node{

    // part which will store data
    int data;
    // pointer to the previous node
    struct node *prev;
    // pointer to the next node
    struct node *next;

};

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin>>n;
    vector<int>nums(n, 0);
    int this_num;
    unordered_map<int, node*> num_to_node;
    node* head_node = new node;
    auto curr = head_node;
    for (int i = 0; i < n; i++){
	cin >> this_num;
	node* new_node = new node;
	new_node->data = this_num;
	num_to_node[this_num] = new_node;
	curr->next = new_node;
	new_node->prev = curr;
	curr = new_node;
    }
    int Q;cin>>Q;
    int type, x, y;
    for (int i = 0; i < Q; i++){
	cin >> type;
	if (type == 1){
	    cin	>> x >> y;
	    auto x_node = num_to_node[x];
	    auto y_node = new node;
	    y_node->data = y;
	    num_to_node[y] = y_node;
	    auto curr_next = x_node->next;
	    y_node->next = curr_next;
	    if (curr_next != nullptr)curr_next->prev = y_node;
	    x_node->next = y_node;
	    y_node->prev = x_node;
	}else{
	    cin >> x;
	    auto x_node = num_to_node[x];
	    auto prev_node = x_node->prev;
	    auto next_node = x_node->next;
	    prev_node->next = next_node;
	    if (next_node != nullptr)next_node->prev = prev_node;
	}
    }
    auto  this_curr = head_node->next;
    while (this_curr != nullptr){
	cout << this_curr->data << " ";
	this_curr = this_curr->next;
    }
    cout << endl;
    return 0;
}
