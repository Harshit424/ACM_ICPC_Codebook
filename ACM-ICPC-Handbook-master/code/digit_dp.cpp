/*
f => 1 => tight
f => 0 => restrictless
*/
int si, dp[19][1<<8][2520];
std::vector<int> v;
int dfs(int idx, int f, int mask, int rem){
	// digit dp from idx = sz-1 to 0 is better than 0 to sz-1.
	// reason, you don't need to memset again and agains
	if(idx <= -1){
		int tt = 1;
		bool good = true;
		for (int i = 2; i <= 9; ++i)
		{
			if(mask & (1<<(i-2))){
				good &= (rem % i == 0);
			}
		}
		return good;
	}
	if(f == 0 and dp[idx][mask][rem] != -1){
		return dp[idx][mask][rem];
	}
	int lim = (f) ? v[idx] : 9;
	int ans = 0;
	for (int i = 0; i <= lim; ++i)
	{
		int nf = (v[idx] == i) ? f : 0;
		int nmask = mask;
		if(i > 1){
			nmask |= (1LL<<(i-2));
		}
		ans += dfs(idx-1, nf, nmask, (rem*10+i)%2520);
	}
	if (f == 0)
		dp[idx][mask][rem] = ans; 
	return ans;
}
int get(int num){
	v.clear();
	while(num){
		v.pb(num % 10);
		num /= 10;
	}
	si = sz(v);
	int tt = dfs(si-1, 1, 0, 0);
	return tt;
}
int32_t main(){
	int t;
	scanf("%lld", &t);
	memset(dp, -1, sizeof dp);
	while(t--){
		int l, r;
		scanf("%lld %lld", &l, &r);
		int gg = get(r);
		int tt = get(l-1);
		printf("%lld\n", gg-tt);
	}	
	return 0;
}
