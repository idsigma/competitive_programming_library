#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T,class U> using P = pair<T,U>;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

vec<int> KMP(string S){
    int M = S.size();
    vec<int> kmp(M+1,0);
    int i = 0,j = kmp[0] = -1;
    while(i<M){
        while(j>-1 && S[i]!=S[j]) j = kmp[j];
        i++; j++;
        if(S[i]==S[j]) kmp[i] = kmp[j];
        else kmp[i] = j;
    }
    return kmp;
};

int calcne(string& S,vec<int>& kmpnext,int pos,char c){
    while(pos>-1 && c!=S[pos]) pos = kmpnext[pos];
    return pos+1;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    string S,T;
    cin >> S >> T;
    int N = S.size(),M = T.size();
    vvec<int> ne(M+1,vec<int>(26,-1));
    vec<int> kmp = KMP(T);
    for(int i=0;i<=M;i++){
        for(char c='a';c<='z';c++){
            if(i==0) ne[i][c-'a'] = (c==T[0]? 1:0);
            else ne[i][c-'a'] = calcne(T,kmp,i,c);
        }
    }
    
    vvec<int> dp(N+1,vec<int>(M+1,-1));
    dp[0][0] = 0;
    for(int i=0;i<N;i++) for(int j=0;j<=M;j++){
        if(dp[i][j]==-1) continue;
        if(S[i]!='?'){
            int nj = ne[j][S[i]-'a'];
            dp[i+1][nj] = max(dp[i+1][nj],dp[i][j]+(nj==M));
        }else{
            for(int k=0;k<26;k++){
                int nj = ne[j][k];
                dp[i+1][nj] = max(dp[i+1][nj],dp[i][j]+(nj==M));
            }
        }
    }
    int ans = 0;
    for(int j=0;j<=M;j++) ans = max(ans,dp[N][j]);
    cout << ans << endl;
}