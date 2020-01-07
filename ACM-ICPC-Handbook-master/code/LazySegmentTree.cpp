#include<bits/stdc++.h>
using namespace std;
#define N 100010
int tree[4*N];
int lazy[4*N];
int a[N];
void updateRange(int node, int start, int end, int l, int r, int val) {
    if(lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if(start != end) {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if(start > end || start > r || end < l)
        return;
    if(start >= l && end <= r) {
        tree[node] += (end - start + 1) * val;
        if(start != end) {
            lazy[node*2] += val;
            lazy[node*2+1] += val;
        }
        return;
    }
    int mid = (start + end) / 2;
    updateRange(node*2, start, mid, l, r, val);
    updateRange(node*2 + 1, mid + 1, end, l, r, val);
    tree[node] = tree[node*2] + tree[node*2+1];
}
void updateRange(int l,int r,int val) {
	updateRange(1,0,N-1,l,r,val);
}
int queryRange(int node, int start, int end, int l, int r) {
    if(start > end || start > r || end < l)
        return 0;
    if(lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if(start != end) {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if(start >= l && end <= r)
        return tree[node];
    int mid = (start + end) / 2;
    int p1 = queryRange(node*2, start, mid, l, r);
    int p2 = queryRange(node*2 + 1, mid + 1, end, l, r);
    return (p1 + p2);
}
int queryRange(int l,int r) {
	return queryRange(1,0,N-1,l,r);
}
void make(int node=1,int start=0,int end=N-1) {
	if(start == end)
		tree[node]=a[start];
	else {
		int mid = (start+end)/2;
		make(2*node,start,mid);
		make(2*node+1,mid+1,end);
		tree[node] = tree[2*node] + tree[2*node+1];
	}
}
int main() {
	int n;
	cin>>n;		// n=10
	for(int i=0;i<n;i++)
	cin>>a[i];				//input 1 2 3 4 5 6 7 8 9 10
	make();
	cout<<queryRange(0,9)<<"\n";
	updateRange(5,9,10);
	cout<<queryRange(4,9)<<"\n";
	updateRange(0,2,20);
	cout<<queryRange(1,7)<<"\n";
}
