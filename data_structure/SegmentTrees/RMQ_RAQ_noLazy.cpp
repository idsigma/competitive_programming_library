#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

template<typename Monoid>
class SegmentTree{
private:
    using F = function<Monoid(Monoid&,Monoid&)>;
    int sz;
    vector<Monoid> seg;
    const F op;//演算
    const Monoid e;//単位元
public:
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
        seg[k] = x;
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

    int gets(){return sz;}

    Monoid getseg(int i){return seg[i];}
};

struct state{
    ll sum,mi;
};

state op(state& a,state& b){
    return (state) {a.sum+b.sum,min(a.mi,b.mi+a.sum)};
}

int main(){
    int N,Q;
    cin >> N >> Q;
    ll inf = 1e15;
    SegmentTree<state> seg(N+1,op,(state){0,inf});
    for(int i=0;i<N+1;i++) seg.set(i,(state){0,0});
    seg.build();
    for(int i=0;i<Q;i++){
        int c;
        cin >> c;
        if(c==0){
            int s,t,x;
            cin >> s >> t >> x;
            seg.update(s,(state){seg[s].sum+x,seg[s].mi+x});
            seg.update(t+1,(state){seg[t+1].sum-x,seg[t+1].mi-x});
        }else{
            int s,t;
            cin >> s >> t;
            cout << seg.query(0,s).sum+seg.query(s,t+1).mi << endl;
        }
    }
}