#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T> using vec = vector<T>;
template <class T> using vvec = vector<vec<T>>;

template<typename OperatorMonoid,typename H>
struct DualSegmentTree {
    int sz, height;
    vector<OperatorMonoid> lazy;
    const H h;
    const OperatorMonoid OM0;
    DualSegmentTree(int n, const H h, const OperatorMonoid OM0)
        : h(h), OM0(OM0) {
        sz = 1;
        height = 0;
        while(sz<n) sz <<= 1, height++;
        lazy.assign(2*sz, OM0);
    }

    inline void propagate(int k) {
        if(lazy[k] != OM0) {
        lazy[2*k] = h(lazy[2*k], lazy[k]);
        lazy[2*k+1] = h(lazy[2*k+1], lazy[k]);
        lazy[k] = OM0;
        }
    }

    inline void thrust(int k) {
        for(int i=height;i>0;i--) propagate(k>>i);
    }

    void update(int a, int b, const OperatorMonoid &x) {
        thrust(a += sz);
        thrust(b += sz-1);
        for(int l=a,r=b+1;l<r;l>>=1,r>>=1) {
        if(l&1) lazy[l] = h(lazy[l],x),++l;
        if(r&1) --r,lazy[r] = h(lazy[r],x);
        }
    }

    OperatorMonoid operator[](int k) {
        thrust(k += sz);
        return lazy[k];
    }
};


const int M = 101;
using arr = array<int,M>;

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    vec<int> A(N);
    for(auto& x:A) cin >> x;
    auto comp = [](arr f,arr g){
        arr res{};
        for(int i=1;i<M;i++){
            res[i] = g[f[i]];
        }
        return res;
    };
    arr e{};
    iota(e.begin(),e.end(),0);
    DualSegmentTree seg(N,comp,e);
    int Q;
    cin >> Q;
    for(int _=0;_<Q;_++){
        int l,r,x,y;
        cin >> l >> r >> x >> y;
        l--; r--;
        arr a = e;
        a[x] = y;
        seg.update(l,r+1,a);
    }
    for(int i=0;i<N;i++) cout << seg[i][A[i]] << " ";
    cout << "\n";
}