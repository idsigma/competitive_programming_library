#include <iostream>
#include <vector>
#include <climits>
#include <functional>
using namespace std;
typedef long long ll;
template<typename Monoid, typename OpMonoid = Monoid>
class LazySegmentTree{
private:
    using F = function<Monoid(Monoid, Monoid)>;
    using G = function<Monoid(Monoid,OpMonoid)>;
    using H = function<OpMonoid(OpMonoid,OpMonoid)>;
    using P = function<OpMonoid(OpMonoid,int)>;
    int sz;
    vector<Monoid> data;
    vector<OpMonoid> lazy;
    const F func;
    const G op;
    const H mergeOp;
    const P multmergeOp;
    const Monoid e;
    const OpMonoid op_e;
public:
    LazySegmentTree(int n, const F f, const G g, const H h, const P p,
    const Monoid &e, const OpMonoid op_e)
    :func(f), op(g), mergeOp(h), multmergeOp(p), e(e), op_e(op_e){
        sz = 1;
        while(sz<n) sz <<= 1;
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
        a += sz; b += sz-1;
        for(int i=height;i>0;i--) propagate(a>>i,1<<(height-i)),propagate(b>>i,1<<(height-i));
        b++;
        Monoid res1 = e,res2 = e;
        while(a<b){
            if(a&1) res1 = func(res1,op(data[a],lazy[a])),a++;
            if(b&1) b--,res2 = func(res2,op(data[b],lazy[b]));
            a >>= 1; b >>= 1;
        }
        return func(res1,res2);
//        return update(a,b,x,1,0,sz);
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


int main(){
    int N,Q;
    cin >> N >> Q;
    auto func = [](ll a, ll b){return min(a,b);};
    auto op = [](ll a, ll b){return (b!=INT_MAX? b:a);};
    auto multmergeop = [](ll a, ll b){return a;};
    LazySegmentTree<ll,ll>
    seg(N,func,op,op,multmergeop,INT_MAX,INT_MAX);
    for(int i=0;i<Q;i++){
        ll c,s,t,x;
        cin >> c;
        if(c==0){
            cin >> s >> t >> x;
            seg.update(s,t+1,x);
        }else{
            cin >> s;
            cout << seg.query(s,s+1) << endl;
        }
    }
}
