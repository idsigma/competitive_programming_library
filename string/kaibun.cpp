#include <iostream>
using namespace std;
string S;
int K;
int dp[310][310][310] = {{{0}}};
int main(){
	cin >> S >> K;
	int N = S.size();
	for(int i=0;i<N;i++){
		for(int j=0;j<=K;j++){
			dp[i][1][j] = 1;
		}
	}
	for(int j=2;j<=N;j++){
		for(int i=0;i<=N-j;i++){
			for(int x=0;x<=K;x++){
				if(S[i]==S[i+j-1]) dp[i][j][x] = max(dp[i][j][x],dp[i+1][j-2][x]+2);
				else{
					dp[i][j][x+1] = max(dp[i][j][x+1],dp[i+1][j-2][x]+2);
					dp[i][j][x] = max(dp[i][j][x],max(dp[i][j-1][x],dp[i+1][j-1][x]));
				}
			}
		}
	}
	cout << dp[0][N][K] << endl;
}
