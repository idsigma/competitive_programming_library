#include <iostream>
#include <vector>
using namespace std;

constexpr int si = 512;

class SqrtDecomposition{
private:
    int N,K;
    //もとの配列
    vector<int> v;
    //分割した区間全体のデータ
    vector<int> bucket;
public:
    SqrtDecomposition(int N):N(N){
        //K個のbucketがある
        K = (N+si-1)/si;
        v = vector<int>(K*si,0);
        bucket = vector<int>(K,0);
    }

    //1点更新、x番目にyを加算
    void update(int x,int y){
        //xは何番目のbucketにあるか？
        int k = x/si;
        v[x] += y;
        int sum = 0;
        //bucket内の値を計算
        for(int i=k*si;i<(k+1)*si;i++) sum += v[i];
        bucket[k] = sum;
    }
    
    //区間[x,y)の合計を取得
    int query(int x,int y){
        int res = 0;
        for(int k=0;k<K;k++){
            //k番目のbucketに注目する
            int l = k*si,r = (k+1)*si;
            if(r<=x || y<=l) continue;
            if(x<=l && r<=y) res += bucket[k];
            else{
                for(int i=max(x,l);i<min(y,r);i++) res += v[i];
            }
        }
        return res;
    }
};

int main(){
    int N,Q;
    cin >> N >> Q;
    SqrtDecomposition SD(N);
    for(int i=0;i<Q;i++){
        int c,a,b;
        cin >> c >> a >> b;
        if(!c){
            a--;
            SD.update(a,b);
        }else{
            a--; b--;
            cout << SD.query(a,b+1) << endl;
        }
    }
}