#include <iostream>
#include <vector>
using namespace std;

int n;
int fact[10];
int used[10] = {0};
int A[10];
vector<int> v;
vector<int> num = {1,2,3,4,5,6,7,8,9};

void permutation(int n,int i){
	int c = n,t = i;
	for(int j=0;j<n;j++){
		if(c>0){
			v.push_back(num[t/fact[c-1]]);
			num.erase(num.begin()+t/fact[c-1]);
			t -= (t/fact[c-1])*fact[c-1];
			c--;
		}else{
			v.push_back(num[0]);
		}
	}
	num.clear();
	for(int j=0;j<n;j++){
		if(j!=n-1) cout << v[j] << " ";
		else cout << v[j] << endl;
		used[j] = 0;
		num.push_back(j+1);
	}
	v.clear();
}

int main(){
	cin >> n;
	for(int i=0;i<n;i++) cin >> A[i];
	for(int i=0;i<=n;i++){
		if(i==0) fact[i] = 1;
		else fact[i] = fact[i-1]*i;
	}
	int ord = 0,now = n-1;
	for(int i=0;i<n;i++){
		ord += fact[now]*(A[i]-1);
		for(int j=i+1;j<n;j++){
			if(A[j]>A[i]) A[j]--;
		}
		now--;
	}
	if(ord-1>=0) permutation(n,ord-1);
	permutation(n,ord);
	if(ord+1<fact[n]) permutation(n,ord+1);
}