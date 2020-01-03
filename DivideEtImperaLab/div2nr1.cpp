/* given the postorder and inorder traversals of a binary tree, find whether they are correct and if they are
find the preorder traversal too - O(n*logn) */
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");

unordered_map<int, int> hasht;
queue<int> preorder;
vector<int> post;

struct Node {
    int value;
    Node *left, *right;
    Node(int val) {
        value = val;
        left = NULL, right = NULL;
    }
};

Node* build(int left, int right, int* pos) {
    if(left > right)
        return NULL;
    int head = post[*pos];
    
    Node* nou = new Node(head);
    (*pos)--;

    if(left == right)
        return nou;
    
    int pos_inord = hasht[head];
    nou->right = build(pos_inord + 1, right, pos);
    nou->left = build(left, pos_inord - 1, pos); 
    return nou;
}

void preord(Node* curr) {
    if(curr == NULL)
        return;
    preorder.push(curr->value);
    preord(curr->left);
    preord(curr->right);
}

int main() {
    int n, i, x;
    fin>>n;

    for(i = 1; i <= n; i++) {
        fin>>x;
        post.push_back(x);
    }
    for(i = 0; i < n; i++) {
        fin>>x;
        hasht.insert(make_pair(x, i));
    }
    int p_pos = n - 1;
    Node* root = build(0, n - 1, &p_pos);
    preord(root);

    if(preorder.size() != n) 
        fout<<"the traversals are not correct";
    else {
        while(!preorder.empty()) {
            fout<<preorder.front()<<" ";
            preorder.pop();
        }
    }
    return 0;
}
