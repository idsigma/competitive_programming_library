#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
typedef pair<int,int> P;

class BVCC{
private:
    vector<int> ord,low,used;
    vector<vector<int>> g;
    vector<vector<P>> bc;
    vector<P> tmp;
    int N,K = 1;
public:
    set<int> ap;
    BVCC(int n,vector<vector<int>> v){
        N = n;
        g = v;
        ord = low = vector<int>(N+1,-1);
        used = vector<int>(N+1,0);
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
                    if(now!=1) ap.insert(now);
                    bc.push_back({});
                    while(true){
                        P e = tmp.back();
                        bc.back().emplace_back(e);
                        tmp.pop_back();
                        if(min(now,x)==e.first && max(now,x)==e.second) break;
                    }
                }
            }else low[now] = min(low[now],ord[x]);
        }
        if(now==1 && cnt>=2) ap.insert(now);
    }
    void decomposition(){
        dfs(1,-1);
    }
};

int N,M;
int main(){
    cin >> N >> M;
    vector<vector<int>> v(N+2);
    int a,b;
    for(int i=0;i<M;i++){
        cin >> a >> b;
        a++; b++;
        v[a].push_back(b); v[b].push_back(a);
    }
    BVCC bvcc(N,v);
    bvcc.decomposition();
    for(auto x:bvcc.ap) cout << --x << endl;
}