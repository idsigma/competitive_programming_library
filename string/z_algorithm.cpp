#include <iostream>
#include <vector>
#include <string>
using namespace std;
string S,T;
//int A[500010] = {};
int cnt[2] = {};
char ans[500010] = {};

vector<int> Z_algorithm(string& S){
    int M = S.size();
    vector<int> A(M,0);
    A[0] = M;
    int i = 1,j = 0;
    while(i<M){
        while(i+j<M && S[j]==S[i+j]) j++;
        A[i] = j;
        if(j==0){
            i++;
            continue;
        }
        int k = 1;
        while(i+k<M && k+A[k]<j){
            A[i+k] = A[k];
            k++;
        }
        i += k; j -= k;
    }
    return A;
}

int main(){
    cin >> S >> T;
    int N = S.size(),M = T.size();
    if(N<M){
        cout << S << endl;
        return 0;
    }
    for(int i=0;i<N;i++) cnt[S[i]-'0']++;
    int id = M;
    vector<int> A = Z_algorithm(T);
    for(int i=M-1;i>=1;i--){
        if(M-i==A[i]) id = i;
    }
    string t = T.substr(M-id,id);
    int t_id = 0;
    for(int i=0;i<N;i++){
        if(i<M){
            if(cnt[T[i]-'0']>=1){
                ans[i] = T[i];
                cnt[T[i]-'0']--;
            }
            else{
                if(T[i]=='0') ans[i] = '1';
                else ans[i] = '0';
            }
        }else{
            if(cnt[t[t_id]-'0']>=1){
                ans[i] = t[t_id];
                cnt[t[t_id]-'0']--;
            }else{
                if(t[t_id]=='0') ans[i] = '1';
                else ans[i] = '0';
            }
            t_id++;
            if(t_id==t.size()) t_id = 0;
        }
    }
    cout << ans << endl;
}