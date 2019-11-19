#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>
using namespace std;

typedef long long ll;

template<typename T>
class MonotoneCHT{
private:
    struct line{
        T a,b;
        line(T a,T b):a(a),b(b){}
        bool operator<(const line& r)const{
            return (a!=r.a? a<r.a:b<r.b);
        }
        bool operator>(const line& r)const{
            return (a!=r.a? a>r.a:b>r.b);
        } 
    };
    //直線群
    vector<line> lines;
    //単調性があるか
    bool isMonotonicX;
    function<bool(T l, T r)> comp;

public:
    MonotoneCHT(bool flagX,function<bool(T l, T r)> compFunc)
                :isMonotonicX(flagX),comp(compFunc){
//                    lines.emplace_back(0,0);
    }
    
    bool check(line l1,line l2,line l3){
        if(l1<l3) swap(l1,l3);
        return (l3.b-l2.b)*(l2.a-l1.a)>=(l2.b-l1.b)*(l3.a-l2.a);
    }

    void add(T a,T b){
        line l(a,b);
        while(lines.size()>=2 && check(*(lines.end()-2),lines.back(),l)) lines.pop_back();
        lines.emplace_back(l);
    }

    T f(int i,T x){
        return lines[i].a*x+lines[i].b;
    }

    T f(line l,T x){
        return l.a*x+l.b;
    }
    //最小値/最大値を返す
    T get(T x){
        if(isMonotonicX){
            static int head = 0;
            while(lines.size()-head>=2 && comp(f(head, x), f(head + 1, x))) head++;
            return f(head,x);
        }else{
            int l = -1,r = lines.size()-1;
            while(l+1<r){
                int m = (l+r)/2;
                (comp(f(m,x),f(m+1,x))? l:r) = m;
            }
            return f(r,x);
        }
    }
};

int main(){
    int N;
    cin >> N;
    MonotoneCHT<ll> cht(true,[](ll a,ll b){return a>=b;});
    for(ll i=1;i<=N;i++){
        ll a;
        cin >> a;
        cht.add(-2*i,a+i*i);
    }
    for(ll i=1;i<=N;i++){
        cout << cht.get(i)+i*i << endl;;
    }
}