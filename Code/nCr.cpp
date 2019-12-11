#define ll int
ll power(ll a, ll b, ll m = mod){if(b < 0)b += m-1; ll r = 1; while(b){if(b&1)r=(r*a)%m; a = (a*a)%m; b>>=1;}return r;}

int fact[N+10], ifact[N+10];
void pre(int N){
	fact[0] = 1;
	for (int i = 1; i <= N; ++i)
	{
		fact[i] = (i*fact[i-1])%mod;
	}
	ifact[N] = power(fact[N], -1);
	for (int i = N-1; i >= 0; --i)
	{
		ifact[i] = ((i+1)*ifact[i+1])%mod;
	}
}

int nCr(int n, int r){
	if(n < r)return 0;
	return ((fact[n]*ifact[r])%mod * ifact[n-r])%mod;
}
