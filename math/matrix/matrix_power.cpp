#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef vector<ll> vec;
typedef vector<vec> mat;

ll N,M,inf = 1e9+7;

mat mult(mat &A,mat &B){
	mat C(A.size(),vec(B[0].size()));
	for(int i=0;i<A.size();i++){
		for(int k=0;k<B.size();k++){
			for(int j=0;j<B[0].size();j++){
				(C[i][j] += A[i][k]*B[k][j])%=inf;
			}
		}
	}
	return C;
}

mat pow(mat A, ll n){
	if(n==1) return A;
	else if(n%2==0){
		mat B = pow(A,n/2);
		return mult(B,B);
	}else{
		mat B = pow(A,n-1);
		return mult(A,B);
	}
}

int main(){
	cin >> N >> M;
	mat A(M,vec(M,0));
	A[0][0] = 1; A[0][M-1] = 1;
	for(int i=1;i<M;i++){
		A[i][i-1] = 1;
	}
	mat res = pow(A,N);
	cout << res[0][0] << endl;
}