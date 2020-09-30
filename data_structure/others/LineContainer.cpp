#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T> using vec = vector<T>;
template <class T> using vvec = vector<vec<T>>;
template<class T> bool chmin(T& a,T b){if(a>b) {a = b; return true;} return false;}
template<class T> bool chmax(T& a,T b){if(a<b) {a = b; return true;} return false;}
#define all(x) (x).begin(),(x).end()
#define debug(x)  cerr << #x << " = " << (x) << endl;

/**
* Author: Simon Lindholm
https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/LineContainer.h
*/

struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    vvec<int> g(N);
    vec<ll> A(N),B(N);
    for(auto& x:A) cin >> x;
    for(auto& x:B) cin >> x;
    for(int i=0;i<N-1;i++){
        int a,b;
        cin >> a >> b;
        a--,b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vec<ll> ans(N);
    auto dfs = [&](auto&& self,int cur,int par)->LineContainer{
        LineContainer cht;
        for(auto& to:g[cur]) if(to!=par){
            LineContainer res = self(self,to,cur);
            if(cht.size()<res.size()) swap(cht,res);
            for(auto& x:res) cht.add(x.k,x.m);
        }
        if(!cht.empty()) ans[cur] = cht.query(A[cur]);
        cht.add(-B[cur],ans[cur]);
        return cht;
    };
    dfs(dfs,0,-1);
    for(int i=0;i<N;i++) cout << -ans[i] << (i!=N-1? " ":"\n");
}