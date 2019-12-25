#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

/*
op(operation):二項演算
homo(homomorphic):Monoidに作用させる準同型写像
comp(compose):homoをマージする

頻出系
区間update
homo:代入
comp:代入

区間加算・区間min
op:min
homo:add
comp:add

区間加算・区間和
struct state{
	ll sum,len;
};
auto op = [](state L,state R){
	return (state){L.sum+R.sum,L.len+R.len};
}
auto homo = [](state S,ll x){
	return (state){S.sum+x*S.len,S.len};
}
comp:add

区間update・区間和
struct state{
	ll sum,len;
};
auto op = [](state L,state R){
	return (state){L.sum+R.sum,L.len+R.len};
}
auto homo = [](state S,ll x){
	return (state){*S.len,S.len};
}
comp:in



代入:auto in = [](int a,int b){return b!=e? a:b;};
加算:auto add = [](int a,int b){return a+b;};


*/
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

	template<typename C>
	int find_subtree(int a,const C &check,Monoid &M,bool type) {
		while(a<sz) {
			propagate(a);
			Monoid nxt = type ? op(reflect(2*a+type),M):op(M,reflect(2*a+type));
			if(check(nxt)) a = 2*a+type;
			else M = nxt, a = 2*a+1-type;
		}
		return a - sz;
	}

	template<typename C>
	int find_first(int a,const C &check) {
		Monoid L = e;
		if(a<=0) {
			if(check(op(L,reflect(1)))) return find_subtree(1,check,L,false);
			return -1;
		}
		thrust(a+sz);
		int b=sz;
		for(a+=sz, b+=sz; a<b;a>>=1,b>>=1) {
			if(a&1) {
				Monoid nxt = op(L,reflect(a));
				if(check(nxt)) return find_subtree(a,check,L,false);
				L = nxt;
				++a;
			}
		}
		return -1;
	}


	template<typename C>
	int find_last(int b,const C &check) {
		Monoid R = e;
		if(b>=sz) {
		if(check(op(reflect(1),R))) return find_subtree(1,check,R,true);
			return -1;
		}
		thrust(b+sz-1);
		int a = sz;
		for(b+=sz;a<b;a>>=1,b>>=1) {
			if(b&1) {
				Monoid nxt = op(reflect(--b),R);
				if(check(nxt)) return find_subtree(b,check,R,true);
				R = nxt;
			}
		}
		return -1;
	}
};


int main(){
	cin.tie(0);
    ios::sync_with_stdio(false);
    int N,Q;
	cin >> N >> Q;
	auto mymin = [](int a,int b){return min(a,b);};
	auto add = [](int a,int b){return a+b;};
	LazySegmentTree<int,int,decltype(mymin),decltype(add),decltype(add)> seg(N,mymin,add,add,INT_MAX,0);
	for(int i=0;i<N;i++) seg.set(i,0);
	seg.build();
	for(int i=0;i<Q;i++){
		int t;
		cin >> t;
		if(t==0){
			int l,r;
			ll x;
			cin >> l >> r >> x;
			seg.update(l,r+1,x);
		}else{
			int l,r;
			cin >> l >> r;
			cout << seg.query(l,r+1) << endl;
		}
	}
}