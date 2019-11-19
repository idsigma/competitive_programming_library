#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int main(){
	cin >> N;
	vector<int> C(N+1,0),L(N+1,1e9);
	for(int i=1;i<=N;i++) cin >> C[i];
	int len = 0;
	L[0] = 0;
	for(int i=1;i<=N;i++){
		if(i==1){
			len++;
			L[len] = C[i];
		}else{
			int t = lower_bound(L.begin(),L.end(),C[i])-L.begin();
			if(t>len){
				len++;
				L[len] = C[i];
			}else{
				L[t] = min(L[t],C[i]);
			}
		}
	}
	cout << N-len << endl;
}