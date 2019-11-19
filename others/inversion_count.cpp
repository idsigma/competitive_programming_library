#include <iostream>
#include <climits>
#include <algorithm>
#include <cassert>
using namespace std;

int N,A[200000];
int W[200000];

long long merge_and_count(int l,int r){
	if(l+1>=r) return 0;
	if(l+2==r){
		if(A[l]<=A[l+1]) return 0;
		swap(A[l],A[l+1]);
		return 1;
	}
	int m=(l+r)/2;
	long long cl = merge_and_count(l,m);
	long long cr = merge_and_count(m,r);
	long long c = 0;
	int i = l, j = m;
	int k = l;
	while(i<m && j<r){
		if(A[i] <= A[j]) W[k++] = A[i++];
		else{
			W[k++] = A[j++];
			c += m-i;
		}
	}
	while(i<m) W[k++] = A[i++];
	while(j<r) W[k++] = A[j++];
	assert(k==r);
	copy(W+l,W+r,A+l);
	return cl+cr+c;
}

int main(){
	while(cin >> N && N>0){
		for(int i=0;i<N;i++){
			cin >> A[i];
		}
		long long ans = merge_and_count(0,N);
		cout << ans << endl;
	}
}
