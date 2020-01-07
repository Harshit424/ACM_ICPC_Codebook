//more details about dynamic seg tree => https://codeforces.com/blog/entry/69957
//blog1 => https://codeforces.com/blog/entry/19080
//comment of blog1 => https://codeforces.com/blog/entry/19080?#comment-239938
//blog2 => https://www.quora.com/What-are-the-differences-among-dynamic-segment-tree-%E2%80%98implicit-segment-tree%E2%80%99-and-persistent-segment-tree/answer/Egor-Suvorov
//blog3 => https://codeforces.com/blog/entry/60837
//http://p.ip.fi/FG_F
//pointer implementation => https://github.com/ADJA/algos/blob/master/DataStructures/ImplicitSegmentTree.cpp (nice implementation)
//implementation2 => http://ideone.com/0QK4CX
//implementation3 => http://ideone.com/hdI5aX (nice implementation)
//implementation4 => https://ideone.com/bdSh9H
//implementation5 => https://ideone.com/6wyGFR, https://ideone.com/LpAQFl
//implementation4 => http://ideone.com/Oe6jZ2
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define int long long
typedef struct data
{
	data* bit[2];
	int cnt = 0;
	int sum = 0;
}trie;
trie* head;
//insert val into the node
//(0000, value) => increment value to 0, 00, 000, 0000
//(0110, value) => increment value to 0, 01, 011, 0110
//(1101, value) => increment value to 1, 11, 110, 1101
//i.e, this function increments the value to all the prefix of the bit representation of x
//function to update value of x.
void insert(int x, int val)
{
	trie* cur = head;
	for(int i = 60; i >= 0; i--)
	{
		int b = (x >> i) & 1;
		if(!cur->bit[b])
			cur -> bit[b] = new trie();
		cur = cur -> bit[b];
		cur->cnt++;
		cur->sum += val;
	}
}
// given x, find the sum of all elements in array with index < x.
int query(int x)
{
	trie* cur = head;
	int ans = 0;
	for(int i = 60; i >= 0; i--)
	{
		int b = (x >> i) & 1;
		if(b == 0 && !cur->bit[b])
			return ans;
		else if(b == 0)
			cur = cur->bit[b];
		else
		{
			if(cur->bit[0] != NULL)
				ans += (cur->bit[0])->sum;//increment count of 0th bit when u move to 1, since
				//we want sum of all elements < x. So if 010, sum(0[0]) + sum(010)
			if(!cur->bit[b])
				return ans;
			cur = cur->bit[b];
		}
	}
	return ans;
}
// this is codenation problem. given x <= 1e18, update a[x] = y
// query, sum of all elements <= x.
int32_t main()
{
	IOS;
	head = new trie();
	int prev = 0;
	int q, m1 = 1e9, m2 = 1e9;
	cin >> q >> m1 >> m2;
	map<int, int> val;
	while(q--)
	{
		int type, a, b;
		cin >> type;
		if(type == 1)
		{
			cin >> a >> b;
			int x = (a + prev) % m1 + 1;
			int y = (b + prev) % m2 + 1;
			if(val.find(x) != val.end())
				insert(x, -val[x]);
			val[x] = y;
			insert(x, val[x]);
		}
		else
		{
			cin >> a;
			int x = (a + prev) % m1 + 1;
			prev = query(x);
			if(val.find(x) != val.end())
				prev += val[x];
			cout << prev << endl;
		}
	}
	return 0;
}
