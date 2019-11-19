#include <iostream>
#include <vector>
using namespace std;

int n;
int fact[10];
vector<int> v;
vector<int> num = {1,2,3,4,5,6,7,8,9};

int main(){
	cin >> n;
	int used[10] = {0};
	for(int i=0;i<=n;i++){
		if(i==0) fact[i] = 1;
		else fact[i] = fact[i-1]*i;
	}
	for(int i=0;i<fact[n];i++){
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
}