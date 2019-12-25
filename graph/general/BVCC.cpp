#include <bits/stdc++.h>
using namespace std;
using ll = long long;
template<class T,class U> using P = pair<T,U>;
template<class T> using vec = vector<T>;
template<class T> using vvec = vector<vec<T>>;

class BVCC{
private:
    vector<int> ord,low,used;
    vector<vector<int>> g;
    vector<vector<P<int,int>>> bc;
    vector<P<int,int>> tmp;
    int N,K = 0;
public:
    set<int> ap;
    BVCC(int n,vector<vector<int>> v){
        N = n;
        g = v;
        ord = low = vector<int>(N,-1);
        used = vector<int>(N,0);
    }
    void dfs(int now,int prev){
        used[now] = 1;
        ord[now] = K++;
        low[now] = ord[now];
        int cnt = 0;
        for(auto x:g[now]) if(x!=prev){
            if(ord[x]<ord[now]){
                tmp.emplace_back(min(now,x),max(now,x));
            }
            if(!used[x]){
                cnt++;
                dfs(x,now);
                low[now] = min(low[now],low[x]);
                if(low[x]>=ord[now]){
                    if(now!=0) ap.insert(now);
                    bc.push_back({});
                    while(true){
                        P<int,int> e = tmp.back();
                        bc.back().emplace_back(e);
                        tmp.pop_back();
                        if(min(now,x)==e.first && max(now,x)==e.second) break;
                    }
                }
            }else low[now] = min(low[now],ord[x]);
        }
        if(now==0 && cnt>=2) ap.insert(now);
    }
    void decomposition(){
        dfs(0,-1);
    }
};

int N,M;
int main(){
    cin >> N >> M;
    vector<vector<int>> v(N);
    int a,b;
    for(int i=0;i<M;i++){
        cin >> a >> b;
        v[a].push_back(b); v[b].push_back(a);
    }
    BVCC bvcc(N,v);
    bvcc.decomposition();
    for(auto x:bvcc.ap) cout << x << endl;
}