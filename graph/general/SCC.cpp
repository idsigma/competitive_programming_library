#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

//0-indexed!
class strong_components{
private:
    vector<vector<int>> v,rv,nv;
    vector<int> rs,visited,cmp,cmp_size;
    void dfs(int n){
        visited[n] = 1;
        for(auto x:v[n]) if(!visited[x]) dfs(x);
        rs.push_back(n);
    }
    void rdfs(int n,int cnt){
        visited[n] = 1;
        cmp[n] = cnt;
        for(auto x:rv[n]) if(!visited[x]) rdfs(x,cnt);
    }
public:
    strong_components(int N,vector<vector<int>>& graph){
        v = graph;
        rv = vector<vector<int>>(N);
        visited = cmp = cmp_size = vector<int>(N,0);
        for(int i=0;i<N;i++) for(auto x:v[i]) rv[x].push_back(i);
        for(int i=0;i<N;i++) if(!visited[i]) dfs(i);
        for(int i=0;i<N;i++) visited[i] = 0;
        int now = 0;
        for(int i=rs.size()-1;i>=0;i--) if(!visited[rs[i]]) rdfs(rs[i],now++);
        nv = vector<vector<int>>(now+1);
        for(int i=0;i<N;i++){
            for(auto x:v[i]){
                if(cmp[i]!=cmp[x]){
                    nv[cmp[i]].push_back(cmp[x]);
                    cmp_size[cmp[x]]++;
                }
            }
        }
    }
    int find(int n){return cmp[n];}
    bool is_same_group(int a,int b){return cmp[a]==cmp[b];}
};

int N,M,s,t,Q;
int main(){
    cin >> N >> M;
    vector<vector<int>> v(N+1);
    for(int i=0;i<M;i++){
        cin >> s >> t;
        v[s].push_back(t);
    }
    strong_components scc(N,v);
    cin >> Q;
    for(int i=0;i<Q;i++){
        cin >> s >> t;
        cout << (scc.is_same_group(s,t)? 1:0) << endl;
    }
}