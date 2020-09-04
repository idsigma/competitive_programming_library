#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T, class U> using Pa = pair<T, U>;
template <class T> using vec = vector<T>;
template <class T> using vvec = vector<vec<T>>;

template<class T>
class BinaryTree{
private:
    struct Node{
        T val;
        Node* par;
        Node* left;
        Node* right;
    };
    Node *root;
    void insert(int x,Node* now,Node* par){
        if(x < now->val){
            if(now->left != nullptr){
                insert(x,now->left,now);
            }else{
                now->left = new Node;
                now->left->val = x;
                now->left->left = nullptr;
                now->left->right = nullptr;
                now->left->par = now;
            }
        }else{
            if(now->right != nullptr){
                insert(x,now->right,now);
            }else{
                now->right = new Node;
                now->right->val = x;
                now->right->left = nullptr;
                now->right->right = nullptr;
                now->right->par = now;
            }
        }
    }
    
    void erase(Node* now,bool is_left){
        if(now->left == nullptr && now->right == nullptr){
            if(now->par!=nullptr){
                if(is_left) now->par->left = nullptr;
                else now->par->right = nullptr;
            }
            delete(now);
        }else if(now->left == nullptr){
            now->right->par = now->par;
            if(now->par != nullptr){
                if(is_left) now->par->left = now->right;
                else now->par->right = now->right;
            }
            now->right = nullptr;
            delete(now);
        }else if(now->right == nullptr){
            now->left->par = now->par;
            if(now->par != nullptr){
                if(is_left) now->par->left = now->left;
                else now->par->right = now->left;
            }
            now->left = nullptr;
            delete(now);
        }
    }

    void erase(Node* now,Node* par,bool is_left,T x){
        if(now==nullptr) return ;
        if(now->val==x){
            if(now->left != nullptr && now->right != nullptr){
                Node* ne = preorder_next(now);
                now->val = ne->val;
                erase(ne,(ne->par!=now));
            }else{
                erase(now,is_left);
            }
        }else if(x < now->val){
            if(now->left != nullptr) return erase(now->left,now,true,x);
        }else{
            if(now->right != nullptr) return erase(now->right,now,false,x);
        }
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

    Node* preorder_next(Node* now){
        assert(now!=nullptr);
        now = now->right;
        while(now->left!=nullptr){
            now = now->left;
        }
        return now;
    }

public:
    BinaryTree():root(nullptr){}
    void insert(T x){
        if(root==nullptr){
            root = new Node;
            root->val = x;
            root->left = nullptr;
            root->right = nullptr;
            root->par = nullptr;
        }else{
            insert(x,root,nullptr);
        }
    }

    void erase(T x){
        erase(root,nullptr,false,x);
    }

    bool find(T x){
        if(root==nullptr) return false;
        else return find(root,x);
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
    cin.tie(0);
    ios::sync_with_stdio(false);
    BinaryTree<int> tree;
    int N;
    cin >> N;
    while(N--){
        string s;
        cin >> s;
        if(s=="insert"){
            int x;
            cin >> x;
            tree.insert(x);
        }else if(s=="find"){
            int x;
            cin >> x;
            cout << (tree.find(x)? "yes\n":"no\n");
        }else if(s=="delete"){
            int x;
            cin >> x;
            tree.erase(x);
        }else{
            auto res = tree.inorder_walk();
            int n = res.size();
            for(int i=0;i<n;i++) cout << " " << res[i];
            cout << "\n";
            res = tree.preorder_walk();
            n = res.size();
            for(int i=0;i<n;i++) cout << " " << res[i];
            cout << "\n";
        }
    }
}