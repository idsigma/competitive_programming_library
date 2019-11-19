#include <iostream>
#include <vector>
#include <map>
using namespace std;

int N;
int B[100010],C[100010],D[100010];
vector<vector<int>> v(100010);
vector<int> ans;

void dfs(int n,vector<int> &now){
    while(!v[n].empty()){
        int m = v[n].back();
        v[n].pop_back();
        for(int i=0;i<v[m].size();i++){
            if(v[m][i]==n){
                v[m].erase(v[m].begin()+i);
                break;
            }
        }
        dfs(m,now);
    }
    now.push_back(n);
}

int main(){
    cin >> N;
    map<int,int> m;
    int cnt = 1;
    for(int i=1;i<=N-1;i++){
        cin >> B[i];
        if(!m.count(B[i])){
            m[B[i]] = cnt;
            D[cnt] = B[i];
            cnt++;
        }
    }
    for(int i=1;i<=N-1;i++){
        cin >> C[i];
        if(!m.count(C[i])){
            m[C[i]] = cnt;
            D[cnt] = C[i];
            cnt++;
        }
    }
    for(int i=1;i<=N-1;i++){
        v[m[B[i]]].push_back(m[C[i]]);
        v[m[C[i]]].push_back(m[B[i]]);
        if(B[i]>C[i]){
            cout << -1 << endl;
            return 0;
        }
    }
    int start = 1,c = 0;
    for(int i=1;i<cnt;i++){
        if(v[i].size()%2==1){
            start = i;
            c++;
        }
    }
    if(!(c==0 || c==2)){
        cout << -1 << endl;
        return 0;
    }
    dfs(start,ans);
    if(ans.size()!=N){
        cout << -1 << endl;
        return 0;
    }
    for(auto x:ans) cout << D[x] << " ";
    cout << endl;
}