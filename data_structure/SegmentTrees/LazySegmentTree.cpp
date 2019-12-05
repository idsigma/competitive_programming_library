#include <iostream>
#include <vector>
#include <functional>
using namespace std;
using ll = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

template< typename Monoid, typename OperatorMonoid = Monoid >
struct LazySegmentTree {
  using F = function< Monoid(Monoid, Monoid) >;
  using G = function< Monoid(Monoid, OperatorMonoid) >;
  using H = function< OperatorMonoid(OperatorMonoid, OperatorMonoid) >;

  int sz, height;
  vector< Monoid > data;
  vector< OperatorMonoid > lazy;
  const F f;
  const G g;
  const H h;
  const Monoid M1;
  const OperatorMonoid OM0;


  LazySegmentTree(int n, const F f, const G g, const H h,
                  const Monoid &M1, const OperatorMonoid OM0)
      : f(f), g(g), h(h), M1(M1), OM0(OM0) {
    sz = 1;
    height = 0;
    while(sz < n) sz <<= 1, height++;
    data.assign(2 * sz, M1);
    lazy.assign(2 * sz, OM0);
  }

  void set(int k, const Monoid &x) {
    data[k + sz] = x;
  }

  void build() {
    for(int k = sz - 1; k > 0; k--) {
      data[k] = f(data[2 * k + 0], data[2 * k + 1]);
    }
  }

  inline void propagate(int k) {
    if(lazy[k] != OM0) {
      lazy[2 * k + 0] = h(lazy[2 * k + 0], lazy[k]);
      lazy[2 * k + 1] = h(lazy[2 * k + 1], lazy[k]);
      data[k] = reflect(k);
      lazy[k] = OM0;
    }
  }

  inline Monoid reflect(int k) {
    return lazy[k] == OM0 ? data[k] : g(data[k], lazy[k]);
  }

  inline void recalc(int k) {
    while(k >>= 1) data[k] = f(reflect(2 * k + 0), reflect(2 * k + 1));
  }

  inline void thrust(int k) {
    for(int i = height; i > 0; i--) propagate(k >> i);
  }

  void update(int a, int b, const OperatorMonoid &x) {
    thrust(a += sz);
    thrust(b += sz - 1);
    for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) lazy[l] = h(lazy[l], x), ++l;
      if(r & 1) --r, lazy[r] = h(lazy[r], x);
    }
    recalc(a);
    recalc(b);
  }

  Monoid query(int a, int b) {
    thrust(a += sz);
    thrust(b += sz - 1);
    Monoid L = M1, R = M1;
    for(int l = a, r = b + 1; l < r; l >>= 1, r >>= 1) {
      if(l & 1) L = f(L, reflect(l++));
      if(r & 1) R = f(reflect(--r), R);
    }
    return f(L, R);
  }

  Monoid operator[](const int &k) {
    return query(k, k + 1);
  }

  template< typename C >
  int find_subtree(int a, const C &check, Monoid &M, bool type) {
    while(a < sz) {
      propagate(a);
      Monoid nxt = type ? f(reflect(2 * a + type), M) : f(M, reflect(2 * a + type));
      if(check(nxt)) a = 2 * a + type;
      else M = nxt, a = 2 * a + 1 - type;
    }
    return a - sz;
  }

  template< typename C >
  int find_first(int a, const C &check) {
    Monoid L = M1;
    if(a <= 0) {
      if(check(f(L, reflect(1)))) return find_subtree(1, check, L, false);
      return -1;
    }
    thrust(a + sz);
    int b = sz;
    for(a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
      if(a & 1) {
        Monoid nxt = f(L, reflect(a));
        if(check(nxt)) return find_subtree(a, check, L, false);
        L = nxt;
        ++a;
      }
    }
    return -1;
  }


  template< typename C >
  int find_last(int b, const C &check) {
    Monoid R = M1;
    if(b >= sz) {
      if(check(f(reflect(1), R))) return find_subtree(1, check, R, true);
      return -1;
    }
    thrust(b + sz - 1);
    int a = sz;
    for(b += sz; a < b; a >>= 1, b >>= 1) {
      if(b & 1) {
        Monoid nxt = f(reflect(--b), R);
        if(check(nxt)) return find_subtree(b, check, R, true);
        R = nxt;
      }
    }
    return -1;
  }
};

int main(){
    int N;
    cin >> N;
    string S;
    cin >> S;
    int n = 0,d = 0;
    for(int i=0;i<N;i++){
        if(S[i]=='R') d++;
        if(S[i]=='L') d = max(0,d-1);
        n = max(n,d);
    }
    int inf = 1e9;
    auto add = [](int a,int b){return a+b;};
    auto mult = [](int a,int b){return a;};
    LazySegmentTree<int,int> segmin(n+1,[](int a,int b){return min(a,b);},
    add,add,inf,0);
    LazySegmentTree<int,int> segmax(n+1,[](int a,int b){return max(a,b);},
    add,add,-inf,0);
    for(int i=0;i<n+1;i++){
        segmin.set(i,0); segmax.set(i,0);
    }
    segmin.build(); segmax.build();
    vec<char> C(n+1,' ');
    vec<int> ans(N);
    int id = 0,eid = 0;
    for(int i=0;i<N;i++){
        if(S[i]=='L') id = max(0,id-1);
        else if(S[i]=='R') id++;
        else if(C[id]!=S[i]){
            if(C[id]=='('){
                segmin.update(id,n+1,-1);
                segmax.update(id,n+1,-1);
            }
            if(C[id]==')'){
                segmin.update(id,n+1,1);
                segmax.update(id,n+1,1);
            }
            C[id] = S[i];
            if(C[id]=='('){
                segmin.update(id,n+1,1);
                segmax.update(id,n+1,1);
            }
            if(C[id]==')'){
                segmin.update(id,n+1,-1);
                segmax.update(id,n+1,-1);
            }
        }
        eid = max(eid,id);
        int mi = segmin.query(0,eid+1);
        if(mi<0 || segmin[n]!=0){
            ans[i] = -1;
        }else{
            ans[i] = segmax.query(0,eid+1);
        }
    }
    for(int i=0;i<N;i++) cout << ans[i] << (i!=N-1? " ":"\n");
}