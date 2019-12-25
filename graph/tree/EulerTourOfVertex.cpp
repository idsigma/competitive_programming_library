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


class EulerTourForVertex{
private:
    vector<int> L,R;
    vvec<edge> g;
    int pos;

    void dfs(int cur,int par){
        L[cur] = pos++;
        for(auto& e:g[cur]) if(e.to!=par){
            dfs(e.to,cur);
        }
        R[cur] = pos;
    }
public:
    EulerTourForVertex(){}
    EulerTourForVertex(int N,int root,vvec<edge> g):L(N),R(N),g(g){
        pos = 0;
        dfs(root,-1);
    }

    int vid(int v){return L[v];}

    template<class T,class G>
    void update(int v,T x,G g){
        g(L[v],R[v],x);
    }

    template<class F>
    void query(int v,F f){
        f(L[v],R[v]);
    }
};

int main(){
    int N,Q;
    cin >> N >> Q;
    vvec<edge> tree(N);
    for(int i=1;i<N;i++){
        int p;
        cin >> p;
        p--;
        tree[p].push_back(i);
    }

    EulerTourForVertex et(N,0,tree);

    struct state{
        int g,w;
    };

    auto op = [](state a,state b){
        return (state) {a.g+b.g,a.w+b.w};
    };
    auto homo = [](state a,int b){
        if(!b) return a;
        return (state) {a.w,a.g};
    };
    auto comp = [](int a,int b){return a^b;};

    LazySegmentTree<state,int,decltype(op),decltype(homo),decltype(comp)>
    seg(N,op,homo,comp,(state){0,0},0);
    for(int i=0;i<N;i++){
        char c;
        cin >> c;
        seg.set(et.vid(i),(state){c=='G',c=='W'});
    }
    seg.build();
    auto g = [&](int l,int r,int x){seg.update(l,r,x);};
    for(int i=0;i<Q;i++){
        int v;
        cin >> v;
        v--;
        et.update(v,1,g);
        cout << (2*seg.query(0,N).g>N? "broccoli":"cauliflower") << endl;
    }
}