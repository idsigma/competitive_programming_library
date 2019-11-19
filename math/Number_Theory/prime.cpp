#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

vector<int> v(100000);
vector<int> prime;

void erast(){
	for(int i=0;i<100000;i++){
		v[i] = 1;
	}
	for(int i=2;i*i<=100000;i++){
		if(v[i]){
			for(int j=0;i*(j+2)<100000;j++){
				v[i*(j+2)]=0;
			}
		}
	}
	for(int i=2;i*i<=2e9;i++){
		if(v[i]){
			prime.push_back(i);
		}
	}
}

int main(){
	erast();
	cout << prime.size() << endl;
}