#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int M,N;
vector<ll> Manacher(vector<ll> X){
    int N = X.size();
    vector<ll> res = vector<ll>(N,0);
    int id = 0,r = 0;
    while(id<N){
        while(id-r>=0 && id+r<N && X[id-r]==X[id+r]) r++;
        res[id] = r;
        int k = 1;
        while(id-k>=0 && id+k<N && k+res[id-k]<r){
            res[id+k] = res[id-k];
            k++;
        }
        id += k; r -= k;
    }
    return res;
}

int main(){
    cin >> M >> N;
    string S;
    vector<string> A;
    for(int i=0;i<M;i++){
        cin >> S;
        A.push_back(S);
    }
    vector<ll> X(2*M-1,0),Y(2*N-1,0);
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            if(A[i][j]=='1'){
                X[2*i]++;
                Y[2*j]++;
            }
        }
    }
    //ここからmanacher
    //偶数長検出のためのダミー
    for(int i=0;i<M-1;i++) X[2*i+1] = -1;
    for(int j=0;j<N-1;j++) Y[2*j+1] = -1;
    vector<ll> XR = Manacher(X),YR = Manacher(Y);
    
    ll ansx = 0,ansy = 0;
    for(int i=0;i<(2*M-1)/2;i++){
        int l = M+i;
        if(i+XR[i]-1==2*i && l+XR[l]-1==2*M-2) ansx++;
    }
    for(int i=0;i<(2*N-1)/2;i++){
        int l = N+i;
        if(i+YR[i]-1==2*i && l+YR[l]-1==2*N-2) ansy++;
    }
    cout << ansx*ansy << endl;
}