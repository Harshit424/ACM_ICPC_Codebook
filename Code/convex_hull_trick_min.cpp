#include <bits/stdc++.h>
using namespace std;

const long long INF = 0x3f3f3f3f3f3f3f3f;

struct Line{
	long long k, b;
	Line(){}
	Line(long long _k, long long _b){k = _k, b = _b;}
	long long get(int x){
		return k * x + b;
	}
}t[200010];

long long h[200010];
int tot;

bool cmp(Line a, Line b, Line c){
	double left = 1.0 * (c.b - a.b) / (a.k - c.k);
	double right = 1.0 * (b.b - a.b) / (a.k - b.k);
	return left < right;
}

void add_line(Line a){
	while (tot > 1 && cmp(t[tot - 2], t[tot - 1], a)){
		tot--;
	}
	t[tot++] = a;
}

long long get_min(int x){
	int l = 0, r = tot - 1;
	while (l < r){
		int mid = (l + r) >> 1;
		if (t[mid].get(x) > (mid != tot - 1 ? t[mid + 1].get(x) : INF)) l = mid + 1;
		else r = mid;
	}
	return t[l].get(x);
}

int main(){
	int n; long long C;
	scanf("%d%lld", &n, &C);
	for (int i = 0; i < n; i++){
		scanf("%lld", &h[i]);
	}
	add_line(Line(-2 * h[0], h[0] * h[0]));
	for (int i = 1; i < n - 1; i++){
		long long minj = get_min(h[i]);
		add_line(Line(-2 * h[i], minj + C + 2ll * h[i] * h[i]));
	}
	printf("%lld\n", get_min(h[n - 1]) + C + 1ll * h[n - 1] * h[n - 1]);
	return 0;
}
