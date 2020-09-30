#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template <class T> using vec = vector<T>;
template <class T> using vvec = vector<vec<T>>;
template<class T> bool chmin(T& a,T b){if(a>b) {a = b; return true;} return false;}
template<class T> bool chmax(T& a,T b){if(a<b) {a = b; return true;} return false;}
#define all(x) (x).begin(),(x).end()
#define debug(x)  cerr << #x << " = " << (x) << endl;

constexpr int si = 300;
constexpr int inf = 1e9;

class SqrtDecomposition{
private:

    class bucket{
        vec<ll> val;
        int sum,lazy;
        int N,l,r;

        bool invalid(int a,int b){
            return max(l,a)>min(b,r);
        }

        //lazy update
        void reflect(){
            if(lazy!=inf){
                sum = 0;
                for(int i=0;i<N;i++){
                    val[i] = lazy;
                    sum += val[i];
                }
            }
            lazy = inf;
        }

        void update_all(int x){
            lazy = x;
        }

        void update_partial(int a,int b,int x){
            reflect();
            sum = 0;
            for(int i=0;i<N;i++){
                if(a<=i && i<b) val[i] = x;
                sum += val[i];
            }
        }

        int query_all(){
            return (lazy!=inf? lazy*(r-l):sum);
        }

        int query_partial(int a,int b){
            reflect();
            int res = 0;
            for(int i=a;i<b;i++) res += val[i];
            return res;
        }

    public:
        bucket(int l,int r,vec<ll> A):N(r-l),l(l),r(r),sum(0),lazy(inf),val(A){}

        void update(int a,int b,int x){
            if(invalid(a,b)) return ;
            if(a<=l && r<=b) update_all(x);
            else update_partial(max(l,a)-l,min(r,b)-l,x);
        }

        int query(int a,int b){
            if(invalid(a,b)) return 0;
            if(a<=l && r<=b) return query_all();
            else return query_partial(max(l,a)-l,min(r,b)-l);
        }
    };

    int N;
    vec<bucket> B;

public:
    SqrtDecomposition(int N,vec<int> A):N(N){
        for(int l=0;l<N;l+=si){
            int r = min(N,si+l);
            vec<ll> val;
            for(int i=l;i<r;i++) val.push_back(A[i]);
            bucket b(l,r,val);
            B.push_back(b);
        }
    }

    void update(int l,int r,int x){
        for(auto& b:B) b.update(l,r,x);
    }

    int query(int l,int r){
        int res = 0;
        for(auto& b:B) res += b.query(l,r);
        return res;
    }

};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N,Q;
    cin >> N >> Q;
    vec<int> A(N,0);
    SqrtDecomposition SD(N,A);
    while(Q--){
        int t,l,r;
        ll x;
        cin >> t >> l >> r;
        if(t==0){
            int x;
            cin >> x;
            SD.update(l,r+1,x);
        }else{
            cout << SD.query(l,r+1) << "\n";
        }
    }
}