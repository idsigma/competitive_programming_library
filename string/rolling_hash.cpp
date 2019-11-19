#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;
typedef long long ll;

const int MAX = 500000, MS = 2;
const ll mod[] = {999999937LL, 1000000007LL}, base = 9973;
struct rolling_hash {
    //全て開区間であることに注意
    int n;
    vector<ll> hs[MS], pw[MS];
    rolling_hash(){}
    rolling_hash(const string &s) {
        n = s.size();
        for (int i = 0; i < MS; i++) {
            hs[i].assign(n+1,0);
            pw[i].assign(n+1,0);
            hs[i][0] = 0;
            pw[i][0] = 1;
            for (int j = 0; j < n; j++) {
                pw[i][j+1] = pw[i][j]*base%mod[i];
                hs[i][j+1] = (hs[i][j]*base+s[j])%mod[i];
            }
        }
    }
    ll hash(int l, int r, int i) { return ((hs[i][r]-hs[i][l]*pw[i][r-l])%mod[i]+mod[i])%mod[i]; }
    bool match(int l1, int r1, int l2, int r2) {
        bool ret = 1;
        for (int i = 0; i < MS; i++) ret &= hash(l1,r1,i)==hash(l2,r2,i);
        return ret;
    }
    bool match(int l, int r, ll h[]) {
        bool ret = 1;
        for (int i = 0; i < MS; i++) ret &= hash(l,r,i)==h[i];
        return ret;
    }
};

int main(){
    string S;
    cin >> S;
    int N = S.size();
    rolling_hash rh(S);
    map<pair<ll,ll>,ll> m[11];
    for(int i=0;i<N;i++){
        for(int j=0;j<10;j++){
            if(i+j>=N) break;
            m[j+1][{rh.hash(i,i+j+1,0),rh.hash(i,i+j+1,1)}]++;
        }
    }
    int M;
    cin >> M;
    ll ans = 0;
    for(int i=0;i<M;i++){
        string C;
        cin >> C;
        rolling_hash now(C);
        ans += m[C.size()][{now.hash(0,C.size(),0),now.hash(0,C.size(),1)}];
    }
    cout << ans << endl;
}