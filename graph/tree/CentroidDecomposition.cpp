#include <iostream>
#include <vector>
using namespace std;
typedef pair<int,int> P;

class CentroidDecomposition{
public:
    int N;
    vector<vector<int>> v;
    vector<int> size;
    vector<int> used;
    vector<char> ans;

    CentroidDecomposition(int N,vector<vector<int>> tree): N(N),v(tree){
        size = used = vector<int>(N,0);
        ans = vector<char>(N);
    }

    int calc_size(int cur,int par){
        int c = 1;
        for(auto x:v[cur]){
            if(x==par || used[x]) continue;
            c += calc_size(x,cur);
        }
        return size[cur] = c;
    }

    //tは連結成分の大きさ
    //cur以下のうち、削除して残る最大の部分木の大きさを返す
    P search_centroid(int cur,int par,int cmp_size){
        P res = {1e9,-1};
        int s = 1,ma = 0;
        for(auto x:v[cur]){
            if(x==par || used[x]) continue;
            res = min(res,search_centroid(x,cur,cmp_size)); 
            ma = max(ma,size[x]);
            s += size[x];
        }
        //子と親の部分木の大きい方
        ma = max(ma,cmp_size-s);
        res = min(res,{ma,cur});
        return res;
    }

    //テンプレここまで
    void solve(int n,char c){
        calc_size(n,-1);
        int centroid = search_centroid(n,-1,size[n]).second;
        used[centroid] = true;
        ans[centroid] = c;
        for(auto x:v[centroid]){
            if(!used[x]) solve(x,c+1);
        }
    }
    vector<char> solve(){
        solve(0,'A');
        return ans;
    }
};

int main(){
    int N;
    cin >> N;
    vector<vector<int>> tree(N);
    for(int i=0;i<N-1;i++){
        int a,b;
        cin >> a >> b;
        a--; b--;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    CentroidDecomposition CD(N,tree);
    vector<char> ans = CD.solve();
    for(auto x:ans) cout << x << " ";
    cout << endl;
}