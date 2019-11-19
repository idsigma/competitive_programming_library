#include <iostream>
#include <vector>
#include <climits>
#include <functional>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> Pa;
struct edge{
    int to;
    ll w;
};

template<typename Monoid, typename OpMonoid = Monoid>
class LazySegmentTree{
private:
    using F = function<Monoid(Monoid, Monoid)>;
    using G = function<Monoid(Monoid,OpMonoid)>;
    using H = function<OpMonoid(OpMonoid,OpMonoid)>;
    using P = function<OpMonoid(OpMonoid,ll)>;
    int sz,height;
    vector<Monoid> data;
    vector<OpMonoid> lazy;
    F func;
    G op;
    H mergeOp;
    P multmergeOp;
    Monoid e;
    OpMonoid op_e;
public:
    LazySegmentTree(){}
    LazySegmentTree(int n, const F f, const G g, const H h, const P p,
    const Monoid &e, const OpMonoid op_e)
    :func(f), op(g), mergeOp(h), multmergeOp(p), e(e), op_e(op_e){
        sz = 1;
        while(sz<n) sz <<= 1;
        data.assign(2*sz,e);
        lazy.assign(2*sz,op_e);
    }
    void init(int n, const F f, const G g, const H h, const P p,
    const Monoid &e1, const OpMonoid op_e1){
        func = f;
        op = g;
        mergeOp = h;
        multmergeOp = p;
        e = e1;
        op_e = op_e1;
        sz = 1;
        height = 0;
        while(sz<n){
            sz <<= 1;
            height++;
        }
        data.assign(2*sz,e);
        lazy.assign(2*sz,op_e);
    }
    //初期化
    void set(int k, const Monoid &x){
        data[k+sz] = x;
    }
    //前計算
    void build(){
        for(int k=sz-1;k>0;k--){
            data[k] = func(data[2*k],data[2*k+1]);
        }
    }
    //kの子に長さlenの遅延を伝搬
    void propagate(int k, int len){
        if(lazy[k]!=op_e){
            if(k<sz){
                //遅延を下の段に伝搬、結果を分割する
                lazy[2*k] = mergeOp(lazy[2*k],lazy[k]);
                lazy[2*k+1] = mergeOp(lazy[2*k+1],lazy[k]);
            }
            data[k] = op(data[k],multmergeOp(lazy[k],len));
            lazy[k] = op_e;
        }
    }
    //更新
    Monoid update(int a, int b, const OpMonoid &x, int k, int l, int r){
        propagate(k,r-l);
        if(r<=a || b<=l) return data[k];
        else if(a<=l && r<=b){
            lazy[k] = mergeOp(lazy[k],x);
            propagate(k,r-l);
            return op(data[k],multmergeOp(lazy[k],r-l));
        }else{
            return data[k] = func(update(a,b,x,2*k,l,(l+r)>>1),update(a,b,x,2*k+1,(l+r)>>1,r));
        }
    }
    Monoid update(int a, int b, const OpMonoid &x){
        return update(a,b,x,1,0,sz);
    }
    //クエリ回答
    Monoid query(int a, int b, int k, int l, int r){
        propagate(k,r-l);
        if(r<=a || b<=l){
            return e;
        }else if(a<=l && r<=b){
            return data[k];
        }else{
            return func(query(a,b,2*k,l,(l+r)>>1),query(a,b,2*k+1,(l+r)>>1,r));
        }
    }
    Monoid query(int a, int b){
        return query(a,b,1,0,sz);
    }
    Monoid operator[](const int &k){
        return query(k,k+1);
    }
};

const auto fm = [](Pa a, Pa b){
    return Pa(a.first+b.first,a.second+b.second);
};

const auto fa = [](Pa a, ll b){
    return Pa(a.first + b*a.second,a.second);
};

const auto fl = [](ll d, ll e){
    return d+e;
};

const auto mult = [](ll x,ll y){
    return x;
};

class EulerTour{
private:
    vector<vector<edge>> v;
    vector<vector<int>> parent;
    vector<int> depth;
    vector<int> ds,us;
    LazySegmentTree<Pa,ll> seg;
    //uからvに降りるパスが、区間[ds[u]+1,ds[v]+1)に対応
    void dfs(int n,int m,int d,int &id){
        parent[0][n] = m;
        depth[n] = d;
        for(auto x:v[n]){
            if(x.to!=m){
                ds[x.to] = id++;
                seg.set(id-1,Pa(x.w,1));
                dfs(x.to,n,d+1,id);
                us[x.to] = id++;
                seg.set(id-1,Pa(-x.w,-1));
            }
        }
    }
public:
    EulerTour(int N,int root,vector<vector<edge>>& tree){
        v = tree;
        parent = vector<vector<int>>(20,vector<int>(N,0));
        depth = ds = us = vector<int>(N,0);
        seg.init(2*N+1,fm,fa,fl,mult,Pa(0,0),0);
        int id = 1;
        dfs(root,-1,0,id);
        us[root] = id;
        seg.build();
        for(int j=0;j+1<20;j++){
            for(int i=0;i<N;i++){
                if(parent[j][i]<0) parent[j+1][i] = -1;
                else parent[j+1][i] = parent[j][parent[j][i]];
            }
        }
    }
    int lca(int n,int m){
        if(depth[n]>depth[m]) swap(n,m);
        for(int j=0;j<20;j++){
            if((depth[m]-depth[n]) >> j&1) m = parent[j][m];
        }
        if(n==m) return n;
        for(int j=19;j>=0;j--){
            if(parent[j][n]!=parent[j][m]){
                n = parent[j][n];
                m = parent[j][m];
            }
        }
        return parent[0][n];
    }
    void update(int node, ll x){
        seg.update(ds[node]+1,us[node],x);
    }

    long long query(int node){
        return seg.query(0,us[node]).first;
    }
    int dep(int n){return depth[n];}
    int getds(int u){return ds[u];}
    int getus(int u){return us[u];}
};

int main(){
    int N;
    cin >> N;
    vector<vector<edge>> v(N);
    for(int i=0;i<N-1;i++){
        int s,t;
        ll w;
        cin >> s >> t >> w;
        v[s].push_back({t,w});
        v[t].push_back({s,w});
    }
    EulerTour et(N,0,v);
    int Q;
    cin >> Q;
    for(int i=0;i<Q;i++){
        int t;
        cin >> t;
        if(t==1){
            int a;
            ll x;
            cin >> a >> x;
            et.update(a,x);
        }else{
            int a;
            cin >> a;
            cout << et.query(a) << endl;
        }
    }
}