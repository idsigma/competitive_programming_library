#include <iostream>
#include <vector>
#include <stack>
#include <stdio.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;

//A[N] = 0にしておく
ll largest_rectangle(vector<ll>& A){
    int N = A.size()-1;
    ll ans = 0;
    stack<P> s;
    for(ll i=0;i<=N;i++){
        ll pos = i;
        while(!s.empty() && s.top().first>=A[i]){
            P p = s.top(); s.pop();
            ans = max(ans,p.first*(i-p.second));
            pos = p.second;
        }
        s.push(P(A[i],pos));
    }
    return ans;
}

int main(){
    int N;
    while(scanf("%d",&N) && N){
        vector<ll> A(N+1,0);
        for(int i=0;i<N;i++) scanf("%lld",&A[i]);
        printf("%lld\n",largest_rectangle(A));
    }
}