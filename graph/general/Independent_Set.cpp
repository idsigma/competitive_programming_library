#include <iostream>
#include <vector>
using namespace std;

int N,M;
int G[41][41] = {};
int is_independent1[1<<20] = {};
int is_independent2[1<<20] = {};
int is_unconnected[1<<20] = {};
int dp[1<<20] = {};

int independent_set(){
    int n1 = (N+1)/2;
    int n2 = N-n1;
    //Sが独立集合か
    for(int S=0;S<(1<<n1);S++) is_independent1[S] = true;
    for(int i=0;i<n1;i++) for(int j=i+1;j<n1;j++) if(G[i][j]==1) is_independent1[(1<<i)+(1<<j)] = false;
    for(int S=0;S<(1<<n1);S++){
        if(!is_independent1[S]) for(int i=0;i<n1;i++) is_independent1[S|(1<<i)] = false;
    }

    for(int S=0;S<(1<<n2);S++) is_independent2[S] = true;
    for(int i=0;i<n2;i++) for(int j=i+1;j<n2;j++) if(G[i+n1][j+n1]==1) is_independent2[(1<<i)+(1<<j)] = false;
    for(int S=0;S<(1<<n2);S++){
        if(!is_independent2[S]) for(int i=0;i<n2;i++) is_independent2[S|(1<<i)] = false;
    }
    //S\in V1 と結ばれていないV2の集合
    is_unconnected[0] = (1<<n2)-1;
    for(int i=0;i<n1;i++) for(int j=0;j<n2;j++) if(G[i][n1+j]==0) is_unconnected[(1<<i)] |= (1<<j);
    for(int S=0;S<(1<<n1);S++) for(int i=0;i<n1;i++) is_unconnected[S|(1<<i)] = (is_unconnected[S] & is_unconnected[(1<<i)]);
    //V2の独立集合のサイズ
    for(int S=0;S<(1<<n2);S++){
        if(is_independent2[S]) dp[S] = __builtin_popcount(S);
        else dp[S] = 0;
    }
    for(int S=0;S<(1<<n2);S++){
        for(int i=0;i<n2;i++){
            if(S&(1<<i)) continue;
            dp[S|(1<<i)] = max(dp[S|(1<<i)],dp[S]);
        }
    }
    int ans = 0;
    for(int S=0;S<(1<<n1);S++){
        if(!is_independent1[S]) continue;
        ans = max(ans,__builtin_popcount(S)+dp[is_unconnected[S]]);
    }
    return ans;
}

int main(){
    cin >> N >> M;
    int a,b;
    for(int i=0;i<M;i++){
        cin >> a >> b;
        a--; b--;
        G[a][b] = 1;
        G[b][a] = 1;
    }
    cout << independent_set() << endl;
}