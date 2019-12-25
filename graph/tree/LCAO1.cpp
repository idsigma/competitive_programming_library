#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<typename T,typename U> using P = pair<T,U>;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

struct edge{
    int to,id;
    ll dist;
    edge(int to,ll dist=1,int id=1):to(to),id(id),dist(dist){};
};

template<typename T>
struct SparseTable {
    vector<vector<T>> st;
    vector<int> lookup;

    SparseTable(){}
    SparseTable(const vector<T> &v) {
        int b = 0;
        while((1<<b)<=v.size()) ++b;
            st.assign(b,vector<T>(1<<b));
            for(int i=0;i<v.size();i++) {
                st[0][i] = v[i];
            }
            for(int i=1;i<b;i++) {
            for(int j=0;j+(1<<i)<=(1<<b);j++) {
                st[i][j] = min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
            }
        }
        lookup.resize(v.size()+1);
        for(int i=2;i<lookup.size();i++) {
            lookup[i] = lookup[i>>1]+1;
        }
    }

    inline T query(int l,int r) {
        int b = lookup[r-l];
        return min(st[b][l],st[b][r-(1<<b)]);
    }
};

class LCA{
private:
    vec<int> idx,dep,vs;
    vec<P<int,int>> init;
    
    SparseTable<P<int,int>> st;

    vvec<edge> g;
    
    int pos;
    
    void dfs(int cur,int par,int d){
        idx[cur] = pos;
        vs[pos] = cur;
        dep[pos++] = d;
        for(auto& e:g[cur]) if(e.to!=par){
            dfs(e.to,cur,d+1);
            vs[pos] = cur;
            dep[pos++] = d;
        }
    }

public:
    LCA(){};
    LCA(int N,int root,vvec<edge> g):idx(N),dep(2*N),vs(2*N),init(2*N),g(g){
        pos = 0;
        dfs(root,-1,0);
        for(int i=0;i<2*N;i++){
            init[i] = {dep[i],vs[i]};
        }
        st = SparseTable<P<int,int>>(init);
    }

    int lca(int u,int v){
        if(idx[u]>idx[v]) swap(u,v);
        return st.query(idx[u],idx[v]+1).second;
    }
    int vid(int v){return idx[v];}
    int idv(int i){return vs[i];}
    int depth(int i){return dep[i];}
};

int main(){
    int N;
    cin >> N;
    vvec<edge> tree(N);
    for(int i=0;i<N;i++){
        int k;
        cin >> k;
        for(int j=0;j<k;j++){
            int c;
            cin >> c;
            tree[i].push_back(c);
        }
    }
    LCA lca(N,0,tree);

    int Q;
    cin >> Q;
    for(int i=0;i<Q;i++){
        int a,b;
        cin >> a >> b;
        cout << lca.lca(a,b) << endl;
    }
}