#include <iostream>
#include <vector>
#include <deque>
using namespace std;
typedef long long ll;

int main(){
    ll N,M,A,B;
    cin >> N >> M >> A >> B;
    vector<vector<ll>> H(N+1,vector<ll>(M+1,0));
    ll G,X,Y,Z;
    cin >> G >> X >> Y >> Z;
    for(int i=1;i<=N*M;i++){
        ll n = (i+M-1)/M;
        H[n][i-(n-1)*M] = G;
        G = (G*X+Y)%Z;
    }
    vector<vector<ll>> min_row(N-A+2,vector<ll>(M+1,1e9));
    for(int j=1;j<=M;j++){
        deque<ll> deq;
        for(int i=1;i<=N;i++){
            while(!deq.empty() && H[deq.back()][j]>H[i][j]) deq.pop_back();
            deq.push_back(i);
            if(i-A+1>=1){
                min_row[i-A+1][j] = H[deq.front()][j];
            }
            if(i-A+1==deq.front()) deq.pop_front();
        }
    }
    ll ans = 0;
    for(int i=1;i<=N-A+1;i++){
        deque<ll> deq;
        for(int j=1;j<=M;j++){
            while(!deq.empty() && min_row[i][deq.back()]>min_row[i][j]) deq.pop_back();
            deq.push_back(j);
            if(j-B+1>=1){
                ans += min_row[i][deq.front()];
            }
            if(j-B+1==deq.front()) deq.pop_front();
        }
    }
    cout << ans << endl;
}