#include <iostream>
#include <cmath>
using namespace std;

int V,E,r;
int str[500010],cur[500010],cost[500010];
int C[100010];
const int Inf = 10000*100000+100;
int main(){
	while(cin >> V >> E >> r && V>0){
		for(int i=0;i<E;i++){
			cin >> str[i] >> cur[i] >> cost[i];
		}
		for(int i=0;i<V;i++){
			C[i] = Inf;
		}
		C[r] = 0;
		for(int t=0;t<V;++t){
			bool update = false;
			for(int i=0; i<E; ++i){
				int s = str[i], c = cur[i], d = cost[i];
				if(C[s] < Inf && C[s] + d < C[c]){
					C[c] = min(C[c],C[s] + d);
					update = true;
				}
			}
			if(!update) break;
		}
		for(int i=0;i<V;i++){
			if(C[i] < Inf) cout << C[i] << endl;
			else cout << "INF" << endl;
		}
	}
}

#if 0
所要時間1時間程度。一度TLEして，緩和の条件が甘かったことに気付いたのでやり直してAC
#endif