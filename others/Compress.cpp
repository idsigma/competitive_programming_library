#include <iostream>
#include <vector>
#include <climits>
#include <functional>
#include <map>
#include <algorithm>
using namespace std;

using ll = long long;
template<class T> using vec = vector<T>;

template<typename Monoid>
class SegmentTree{
private:
    using F = function<Monoid(Monoid,Monoid)>;
    int sz;
    vector<Monoid> seg;
    const F op;//演算
    const Monoid e;//単位元
public:
    SegmentTree(){}
    SegmentTree(int n,const F op,const Monoid &e):op(op),e(e){
        sz = 1;
        while(sz<n) sz <<= 1;
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
        seg[k] = max(seg[k],x);
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

struct Q{
    ll l,r,col;
    bool operator<(const Q& q)const{
        if(l!=q.l) return l<q.l;
        else if(r!=q.r) return r<q.r;
        else return col<q.col;
    }
};

struct Compress{
    map<ll,int> idx;
    map<int,ll> value;
    vector<ll> cmp;
    int N;
    Compress(vector<ll> v){
        for(auto& x:v) cmp.push_back(x);
        sort(cmp.begin(),cmp.end());
        cmp.erase(unique(cmp.begin(),cmp.end()),cmp.end());
        N = cmp.size();
        for(int i=0;i<N;i++) idx[cmp[i]] = i;
    }
    int id(ll val){return idx[val];}
    ll val(int id){return cmp[id];}
};

int main(){
    ll N,M,X,Y;
    cin >> N >> M >> X >> Y;
    vec<Q> q(M);
    for(int i=0;i<M;i++){
        ll l,r,c;
        cin >> c >> l >> r;
        c--;
        q[i] = {l,r,c};
    }
    sort(q.begin(),q.end());
    vec<ll> v = {0};
    for(auto& x:q){
        v.push_back(x.l); v.push_back(x.r);
    }
    Compress cmp(v);
    int n = cmp.N;
    ll inf = 1e18;
    SegmentTree<ll> seg(n,[](ll a,ll b){return max(a,b);},-inf);
    vec<SegmentTree<ll>> segs;
    for(int i=0;i<7;i++){
        segs.push_back(seg);
        if(i==6) segs[i].set(0,0);
        segs[i].build();
    }
    ll ans = 0;
    for(auto& x:q){
        int l = cmp.id(x.l),r = cmp.id(x.r);
        ll val = segs[6].query(0,l)+(x.r-x.l+1)*X;
        for(int c=0;c<3;c++){
            if(x.col==c) continue;
            val = max(val,segs[c].query(l,r)+(x.l+x.r-1)*X+(x.l-1)*Y);
        }
        val = max(val,segs[x.col+3].query(l,r)+x.r*X);
        ans = max(ans,val);
        segs[6].update(r,val);
        segs[x.col].update(r,val-x.r*(2*X+Y));
        segs[x.col+3].update(r,val-x.r*X);
    }
    cout << ans << endl;
}