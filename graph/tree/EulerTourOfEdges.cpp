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


template<typename Monoid,typename F>
class SegmentTree{
private:
    int sz;
    vector<Monoid> seg;
    const F op;//演算
    const Monoid e;//単位元
public:
    SegmentTree(int n,const F op,const Monoid &e):op(op),e(e){
        sz = 1;
        while(sz<=n) sz <<= 1;
        seg.assign(2*sz,e);
    }
    //代入
    void set(int k, const Monoid &x){
        seg[k+sz] = x;
    }
    //前計算(?)
    void build(){
        for(int i=sz-1;i>0;i--){
            seg[i] = op(seg[2*i],seg[2*i+1]);
        }
    }
    void update(int k,const Monoid &x){
        k += sz;
        seg[k] += x;
        while(k>>=1){
            seg[k] = op(seg[2*k],seg[2*k+1]);
        }
    }
    Monoid query(int l,int r){
        Monoid L = e,R = e;
        for(l+=sz,r+=sz;l<r;l>>=1,r>>=1){
            if(l&1) L = op(L,seg[l++]);
            if(r&1) R = op(seg[--r],R);
        }
        return op(L,R);
    }
    Monoid operator[](const int &k)const{
        return seg[k+sz];
    }
};

class EulerTourForEdge{
private:
    vec<int> down,up,dep,id;
    vvec<edge> g;
    void dfs(int cur,int par,int d){
        dep[cur] = d;
        for(auto& e:g[cur]) if(e.to!=par){
            down[e.to] = id.size();
            id.push_back(e.to);
            dfs(e.to,cur,d+1);
            up[e.to] = id.size();
            id.push_back(e.to);
        }
    }

public:
    EulerTourForEdge(){}
    EulerTourForEdge(int N,int root,vvec<edge> g):down(N),up(N),dep(N),g(g){
        id.clear();
        down[root] = id.size();
        id.push_back(root);
        dfs(root,-1,0);
        up[root] = id.size();
        id.push_back(root);
    }

    int child(int u,int v){return dep[u]<dep[v]? v:u;}

    int bottom(int e){return id[e];}

    template<class T,class G>
    void update(int u,T x,G g){
        g(down[u],x);
        g(up[u],-x);//inverse
    }

    template<class F>
    //u-v path s.t. lca(u,v) = u or v
    void query(int u,int v,F f){
        if(dep[u]>dep[v]) swap(u,v);
        f(down[u]+1,down[v]);
    }
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

    EulerTourForEdge et(N,0,tree);
    auto add = [](ll a,ll b){return a+b;};
    SegmentTree<ll,decltype(add)> seg(2*N,add,0);
    int Q;
    cin >> Q;

    auto g = [&](int i,ll x){seg.update(i,x);};
    auto f = [&](int l,int r){cout << seg.query(l,r+1) << "\n";};
    for(int i=0;i<Q;i++){
        int t;
        cin >> t;
        if(t==0){
            int v; ll w;
            cin >> v >> w;
            et.update(v,w,g);
        }else{
            int v;
            cin >> v;
            et.query(0,v,f);
        }
    }
}
