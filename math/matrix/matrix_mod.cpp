#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;

const ll mod = 2;
struct mint {
    ll x;
    mint(ll x=0):x((x%mod+mod)%mod){}
    mint& operator+=(const mint a) {
        if ((x += a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += mod-a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator*=(const mint a) {
        (x *= a.x) %= mod;
        return *this;
    }
    mint operator+(const mint a) const {
        mint res(*this);
        return res+=a;
    }
    mint operator-(const mint a) const {
        mint res(*this);
        return res-=a;
    }
    mint operator*(const mint a) const {
        mint res(*this);
        return res*=a;
    }
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }
    mint add_inv() const{
        if(x==0) return 0;
        return mod-x;
    }
    // for prime mod
    mint inv() const {
        return pow(mod-2);
    }
    mint& operator/=(const mint a) {
        return (*this) *= a.inv();
    }
    mint operator/(const mint a) const {
        mint res(*this);
        return res/=a;
    }
};

class matrix{
public:
    vector<vector<mint>> A;
    int N,M;
    matrix(int n,int m,vector<vector<mint>> v){
        N = n; M = m;
        A = v;
    }
    void row_reduction(){
        int p = 0;
        //連立方程式を解くときはM-1にする？
        for(int j=0;j<M-1;j++){
            int row = p;
            while(row<N && !A[row][j].x) row++;
            if(row==N) continue;
            swap(A[p],A[row]);
            for(int i=p+1;i<N;i++){
                if(A[i][j].x){
                    mint a = A[i][j]/A[p][p];
                    for(int k=0;k<M;k++){
                        A[i][k] -= a*A[p][k];
                    }
                }
            }
            p++;
        }
    }
};

int main(){
    int M,N,D;
    while(cin >> M >> N >> D && M){
        vector<vector<mint>> v(N*M,vector<mint>(N*M+1));
        for(int i=0;i<N;i++) for(int j=0;j<M;j++){
            int a;
            cin >> a;
            if(a) v[i*M+j][N*M] = 1;
            for(int k=0;k<N;k++) for(int l=0;l<M;l++){
                int d = abs(i-k)+abs(j-l);
                if(d==0 || d==D) v[i*M+j][k*M+l] = 1;
            }        
        }
        matrix mat(N*M,N*M+1,v);
        mat.row_reduction();
        bool ok = true;
        for(int i=0;i<N*M;i++){
            if(!mat.A[i][N*M].x) continue;
            ok = false;
            for(int j=0;j<N*M;j++) if(mat.A[i][j].x) ok = true;
            if(!ok) break;
        }
        cout << ok << endl;
    }
}