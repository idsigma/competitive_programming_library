bool dfs(int n,int c){
	color[n] = c;
	for(int i=0;i<v[n].size();i++){
		if(color[v[n][i]] == c) return false;
		else if(color[v[n][i]] == 0 && !dfs(v[n][i],-c)) return false;
	}
	return true;
}