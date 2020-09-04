#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T,class U> using Pa = pair<T,U>;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

template<int char_size,int margin>
class Trie{
private:
    struct Node{
        int ne[char_size];
        int num;
        int subtree_num;
        vec<int> accept;
        Node():num(0){
            memset(ne,-1,sizeof(ne));
        }
    };

    vec<Node> nodes;
    int root;
public:
    Trie():root(0){
        nodes.push_back(Node());
    }

    void update_direct(int node,int id){
        nodes[node].accept.push_back(id);
        nodes[node].num++;
    }

    void update_child(int node,int child){
        nodes[node].subtree_num++;
    }

    void add(const string& S,int s_id,int node_id,int id){
        if(s_id==S.size()) update_direct(node_id,id);
        else{
            int c = S[s_id]-margin;
            if(nodes[node_id].ne[c]==-1){
                nodes[node_id].ne[c] = (int) nodes.size();
                nodes.push_back(Node());
            }
            add(S,s_id+1,nodes[node_id].ne[c],id);
            update_child(node_id,nodes[node_id].ne[c]);
        }
    }

    void add(const string& S,int id){
        add(S,0,0,id);
    }

    void add(const string &S){
        add(S,nodes[0].num);
    }

    template<class F>
    void query(const string& S,F& f,int s_id,int node_id){
        for(auto& id:nodes[node_id].accept) f(id);
        if(s_id==S.size()) return ;
        else{
            int c = S[s_id]-margin;
            if(nodes[node_id].ne[c]==-1) return ;
            query(S,f,s_id+1,nodes[node_id].ne[c]);
        }
    }

    template<class F>
    void query(const string& S,F& f){
        query(S,f,0,0);
    }

    int count()const{
        return nodes[0].num;
    }

    int size()const{
        return (int) nodes.size();
    }

};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    string S;
    cin >> S;
    int N = S.size();
    int M;
    cin >> M;
    Trie<26,'a'> trie;
    vec<string> P(M);
    for(int i=0;i<M;i++){
        cin >> P[i];
        trie.add(P[i]);
    }
    vec<ll> W(M);
    for(int i=0;i<M;i++) cin >> W[i];
    vec<ll> dp(N+1,0);
    for(int i=0;i<N;i++){
        auto update = [&](int id){
            int s = P[id].size();
            dp[i+s] = max(dp[i+s],dp[i]+W[id]);
        };
        trie.query(S,update,i,0);
        dp[i+1] = max(dp[i+1],dp[i]);
    }
    cout << dp[N] << "\n";
}