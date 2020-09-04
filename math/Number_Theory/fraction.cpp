#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T, class U> using Pa = pair<T, U>;
template <class T> using vec = vector<T>;
template <class T> using vvec = vector<vec<T>>;

struct fraction {
    ll num, deno;//denoが分母
    inline void simplify() {
        if(deno<0){
            num *= -1; deno *= -1;
        }
        ll g = gcd(num<0 ? -num:num,deno);
        num /= g;
        deno /= g;
    }

    fraction(){}
    fraction(ll num,ll deno):num(num),deno(deno){simplify();}

    inline bool operator<(const fraction &r)const{
        return num*r.deno<deno*r.num;
    }
    inline bool operator>(const fraction &r)const{
        return num*r.deno>deno*r.num;
    }
    inline bool operator != (const fraction &r)const{
        return num*r.deno != deno*r.num;
    }
};

fraction operator+(fraction& a,fraction& b){
    ll l = lcm(a.deno,b.deno);
    fraction res(a.num*(l/a.deno)+b.num*(l/b.deno),l);
    return res;
}

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
    void set(int k, const Monoid &x){
        seg[k+sz] = x;
    }
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

auto op = [](ll a,ll b){return a+b;};

struct plane{
    fraction t1,t2;
    int id;
};

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N;
    ll W;
    cin >> N >> W;
    vec<ll> X(N),V(N);
    vec<plane> P(N);
    for(int i=0;i<N;i++){
        cin >> X[i] >> V[i];
        P[i] = {fraction(-X[i],V[i]-W),fraction(-X[i],V[i]+W),i};
    }
    sort(P.begin(),P.end(),[](plane& a,plane& b){
        if(a.t2!=b.t2) return a.t2<b.t2;
        else return a.t1>b.t1;
    });
    vec<int> id(N);
    int n = 0;
    for(int i=0;i<N;i++){
        id[P[i].id] = n;
        if(i+1<N && P[i].t1!=P[i+1].t1) n++;
    }
    SegmentTree<ll,decltype(op)> seg(N,op,0);
    sort(P.begin(),P.end(),[&](plane& a,plane& b){
        if(a.t1!=b.t1) return a.t1<b.t1;
        else return a.t2>b.t2;
    });
    ll ans = 0;
    for(int i=0;i<N;i++){
        ans += seg.query(id[P[i].id],N);
        seg.update(id[P[i].id],1);
    }
    cout << ans << "\n";
}