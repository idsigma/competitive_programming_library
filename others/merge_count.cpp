ll merge_count(vector<ll> &a){
	int n = a.size();
	if(n<=1) return 0;
	ll cnt = 0;
	vector<ll> b(a.begin(),a.begin() + n/2);
	vector<ll> c(a.begin() + n/2, a.end());
	cnt += merge_count(b);
	cnt += merge_count(c);
	int ai = 0,bi = 0,ci = 0;
	while(ai<n){
		if(bi<b.size() && (ci == c.size() || b[bi] <= c[ci])){
			a[ai++] = b[bi++];
		}else{
			cnt += n/2 - bi;
			a[ai++] = c[ci++];
		}
	}
	return cnt;
}
