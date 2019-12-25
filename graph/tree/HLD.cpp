#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

template<typename Monoid,typename OperatorMonoid,typename F,typename G,typename H>
struct LazySegmentTree {
	int sz,height;
	vec<Monoid> data;
	vec<OperatorMonoid> lazy;
	const F op;
	const G homo;
	const H comp;
  	const Monoid e;
	const OperatorMonoid Oe;

	LazySegmentTree(int n,const F op,const G homo,const H comp,
					const Monoid &e,const OperatorMonoid Oe)
		: op(op),homo(homo),comp(comp),e(e),Oe(Oe) {
		sz = 1;
		height = 0;
		while(sz<=n) sz <<= 1,height++;
		data.assign(2*sz,e);
		lazy.assign(2*sz,Oe);
	}

	void set(int k,const Monoid &x) {
		data[k+sz] = x;
	}

	void build() {
		for(int k=sz-1;k>0;k--) {
			data[k] = op(data[2*k], data[2*k+1]);
		}
	}

	inline void propagate(int k) {
		if(lazy[k]!=Oe) {
			lazy[2*k] = comp(lazy[2*k], lazy[k]);
			lazy[2*k+1] = comp(lazy[2*k+1], lazy[k]);
			data[k] = reflect(k);
			lazy[k] = Oe;
		}
	}

	inline Monoid reflect(int k) {
		return lazy[k] == Oe? data[k]:homo(data[k],lazy[k]);
	}

	inline void recalc(int k) {
		while(k>>=1) data[k] = op(reflect(2*k), reflect(2*k+1));
	}

	inline void thrust(int k) {
		for(int i=height;i>0;i--) propagate(k>>i);
	}

	void update(int a, int b, const OperatorMonoid &x) {
		thrust(a+=sz);
		thrust(b+=sz-1);
		for(int l=a,r=b+1;l<r;l>>=1,r>>=1) {
			if(l&1) lazy[l] = comp(lazy[l],x),++l;
			if(r&1) --r, lazy[r] = comp(lazy[r],x);
		}
		recalc(a);
		recalc(b);
	}

	Monoid query(int a, int b) {
		thrust(a+=sz);
		thrust(b+=sz-1);
		Monoid L = e, R = e;
		for(int l=a, r=b+1;l<r;l>>= 1,r>>=1) {
			if(l&1) L = op(L,reflect(l++));
			if(r&1) R = op(reflect(--r),R);
		}
		return op(L,R);
	}

	Monoid operator[](const int &k) {
		return query(k,k+1);
	}
};

struct edge{
    int to,id;
    ll dist;
    edge(int to,ll dist=1,int id=1):to(to),id(id),dist(dist){};
};

class HeavLightDecomposition{
private:
    vvec<edge> g;
    vec<int> sz,in,out,head,par;
    int pos;

    void dfs_sz(int cur,int p){
        sz[cur] = 1;
        par[cur] = p;
        for(auto& e:g[cur]) if(e.to!=p){
            dfs_sz(e.to,cur);
            sz[cur] += sz[e.to];
            if(sz[e.to]>sz[g[cur][0].to]) swap(e,g[cur][0]);
        }
    }

    void dfs_hld(int cur,int p){
        in[cur] = pos++;
        for(auto& e:g[cur]) if(e.to!=p){
            head[e.to] = (e.to==g[cur][0].to? head[cur]:e.to);
            dfs_hld(e.to,cur);
        }
        out[cur] = pos;
    }
public:
    HeavLightDecomposition(){}
    HeavLightDecomposition(int N,int root,vvec<edge> tree):
    g(tree),sz(N),in(N),out(N),head(N),par(N){
        pos = 0;
        dfs_sz(root,-1);
        dfs_hld(root,-1);
    }

    int lca(int u,int v){
        while(true){
            if(in[u]>in[v]) swap(u,v);
            if(head[u]==head[v]) return u;
            v = par[head[v]];
        }
    }

    template<class T,class G>
    void update(int u,int v,const T& x,const G& g, bool isedge=false){
        while(true){
            if(in[u]>in[v]) swap(u,v);
            if(head[u]==head[v]) break;
            g(in[head[v]],in[v]+1,x);
            v = par[head[v]];
        }
        g(in[u]+isedge,in[v]+1,x);
    }

    template<class T,class F,class Q>
    T query(int u,int v,const T &e,const F& f,const Q& q,bool isedge=false){
        T l = e,r = e;
        while(true){
            if(in[u]>in[v]){
                swap(u,v); swap(l,r);
            }
            if(head[u]==head[v]) break;
            l = f(q(in[head[v]],in[v]+1),l);
            v = par[head[v]];
        }
        return f(f(q(in[u]+isedge,in[v]+1),l),r);
    }

};

int main(){
	cin.tie(0);
    ios::sync_with_stdio(false);
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
    HeavLightDecomposition HLD(N,0,tree);
    struct state{
	ll sum,len;
    };
    auto op = [](state L,state R){
        return (state){L.sum+R.sum,L.len+R.len};
    };
    auto homo = [](state S,ll x){
        return (state){S.sum+x*S.len,S.len};
    };
    auto comp = [](ll a, ll b){return a+b;};
    state e = {0,0};
    LazySegmentTree<state,ll,decltype(op),decltype(homo),decltype(comp)>
    seg(N,op,homo,comp,(state){0,0},0);
    for(int i=0;i<N;i++) seg.set(i,(state) {0,1});
    seg.build();
    
    int Q;
    cin >> Q;

    auto q = [&](int l,int r){return seg.query(l,r);};
    auto update = [&](int l,int r,ll x){seg.update(l,r,x);};
    for(int i=0;i<Q;i++){
        int t;
        cin >> t;
        if(t==0){
            int v; ll w;
            cin >> v >> w;
            HLD.update(0,v,w,update,true);
        }else{
            int v;
            cin >> v;
            state res = HLD.query(0,v,e,op,q,true);
            cout << res.sum << endl;
        }
    }
}