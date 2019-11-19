#include <iostream>
#include <vector>
#include <climits>
#include <functional>
using namespace std;

template<typename Monoid>
class SegmentTree{
private:
    using F = function<Monoid(Monoid,Monoid)>;
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
};

int main(){
    int N,Q;
    cin >> N >> Q;
    SegmentTree<int> 
    seg(N,[](int a,int b){return a+b;},0);
    for(int i=0;i<Q;i++){
        int c,x,y;
        cin >> c >> x >> y;
        if(c==0) seg.update(x,y);
        else cout << seg.query(x,y+1) << endl;
    }
}