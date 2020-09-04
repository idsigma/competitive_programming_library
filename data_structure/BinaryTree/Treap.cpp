#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T, class U> using Pa = pair<T, U>;
template <class T> using vec = vector<T>;
template <class T> using vvec = vector<vec<T>>;


template<class T>
class Treap{
private:

    inline int xor128() {
        static int x = 123456789;
        static int y = 362436069;
        static int z = 521288629;
        static int w = 88675123;
        int t;

        t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }
    struct Node{
        T val;
        int priority;
        int cnt;
        Node* par;
        Node* left;
        Node* right;
        Node(){}
        Node(T val,int p):val(val),priority(p){}
    };
    Node *root;
    //cnt of subtree
    int size(Node* t){
        if(t==nullptr) return 0;
        return t->cnt;
    }

    Node* rightRotate(Node* t){
        Node* s = t->left;
        t->cnt -= size(t->left);
        t->left = s->right;
        t->cnt += size(t->left);
        s->cnt -= size(t->left);
        s->right = t;
        s->cnt += size(t);
        return s;
    }

    Node* leftRotate(Node* t){
        Node* s = t->right;
        t->cnt -= size(t->right);
        t->right = s->left;
        t->cnt += size(t->right);
        s->cnt -= size(t->right);
        s->left = t;
        s->cnt += size(t);
        return s;
    }

    Node* insert(Node* t,T val,int priority){
        if(t == nullptr){
            t = new Node;
            t->left = nullptr;
            t->right = nullptr;
            t->val = val;
            t->priority = priority;
            t->cnt = 1;
            return t;
        }
        /*
        if(val == t->val){
            return t;
        }
        */
        if(val < t->val){
            t->left = insert(t->left,val,priority);
            t->cnt += 1;
            if(t->priority < t->left->priority){
                t = rightRotate(t);
            }
        }else{
            t->right = insert(t->right,val,priority);
            t->cnt += 1;
            if(t->priority < t->right->priority){
                t = leftRotate(t);
            }
        }
        return t;
    }

    Node* erase(Node* t,T val){
        if(t == nullptr){
            return nullptr;
        }
        if(val < t->val){
            t->left = erase(t->left,val);
            t->cnt -= 1;
        }else if(val > t->val){
            t->right = erase(t->right,val);
            t->cnt -= 1;
        }else{
            return _erase(t,val);
        }
        return t;
    }

    Node* _erase(Node* t,T val){
        if(t->left == nullptr && t->right == nullptr){
            return nullptr;
        }else if(t->left == nullptr){
            t = leftRotate(t);
        }else if(t->right == nullptr){
            t = rightRotate(t);
        }else{
            if(t->left->priority > t->right->priority){
                t = rightRotate(t);
            }else{
                t = leftRotate(t);
            }
        }
        return erase(t,val);
    }

    bool find(Node* now,T x){
        if(now==nullptr) return false;
        if(now->val == x) return true;
        if(x < now->val){
            if(now->left != nullptr) return find(now->left,x);
        }else{
            if(now->right != nullptr) return find(now->right,x);
        }
        return false;
    }

    T find_kth(Node* now,int k){
        if(now==nullptr) assert(false);
        if(k==size(now)-size(now->right)) return now->val;
        if(size(now->left)+1 < k){
            return find_kth(now->right,k-size(now->left)-1);
        }else{
            return find_kth(now->left,k);
        }
    }

    void inorder_walk(Node* now,vec<T>& v){
        if(now==nullptr) return ;
        if(now->left!=nullptr) inorder_walk(now->left,v);
        v.push_back(now->val);
        if(now->right!=nullptr) inorder_walk(now->right,v);
    }
    void preorder_walk(Node* now,vec<T>& v){
        if(now==nullptr) return ;
        v.push_back(now->val);
        if(now->left!=nullptr) preorder_walk(now->left,v);
        if(now->right!=nullptr) preorder_walk(now->right,v);
    }

public:
    Treap():root(nullptr){}
    
    void insert(T val){
        int priority = xor128();
        if(root == nullptr){
            root = new Node;
            root->left = nullptr;
            root->right = nullptr;
            root->val = val;
            root->priority = priority;
            root->cnt = 1;
            return ;
        }
        root = insert(root,val,priority);
    }

    void erase(T val){
        root = erase(root,val);
    }

    bool find(T val){
        return find(root,val);
    }

    T find_kth(int k){
        return find_kth(root,k);
    }
    vec<T> inorder_walk(){
        if(root==nullptr) return {};
        vec<T> res;
        inorder_walk(root,res);
        return res;
    }
    vec<T> preorder_walk(){
        if(root==nullptr) return {};
        vec<T> res;
        preorder_walk(root,res);
        return res;
    }

};

int main(){
    Treap<int> treap;
    int Q;
    cin >> Q;
    while(Q--){
        int t,x;
        cin >> t >> x;
        if(t==1) treap.insert(x);
        else{
            int res = treap.find_kth(x);
            treap.erase(res);
            cout << res << "\n";
        }
    }
}