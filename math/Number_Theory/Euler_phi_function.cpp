#include <iostream>
#include <vector>
#include <map>
using namespace std;
using ll = long long;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

struct prime{
    int p,q;
};

int main(){
    int N;
    cin >> N;
    map<int,int> m;
    int n = N;
    for(int i=2;i*i<=N;i++){
        while(n%i==0){
            n /= i;
            m[i]++;
        }
    }
    if(n!=1) m[n]++;
    vec<prime> P;
    for(auto x:m) P.push_back({x.first,x.second});
    int ans = 0;
    n = P.size();
    for(int S=1;S<(1<<n);S++){
        int val = 1;
        for(int j=0;j<n;j++){
            if(S&(1<<j)) val *= P[j].p;
        }
        int s = __builtin_popcount(S);
        ans += (N/val)*(s%2? 1:-1);
    }
    cout << N-ans << endl;
}