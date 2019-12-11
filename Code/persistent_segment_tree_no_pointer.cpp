#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define ll long long 
#define pb push_back
#define sz(i) (int)(i.size())
#define fi first
#define se second
#define ld long double
#define P pair<int, int>
using namespace std;
const int N = 5e5 + 10;
// make sure N size is correctttt!!!!!!!!!

int n, root[N], a[N], seg[4*N], rev[N], NEXT_FREE_INDEX = 1, ir = 0, L[4*N], R[4*N];
void build(int id = ir, int l = 1, int r = n){
   if(l == r){
      seg[id] = 0;
      return;
   }
   L[id] = NEXT_FREE_INDEX++;
   R[id] = NEXT_FREE_INDEX++;
   int mid = (l+r)>>1;
   build(L[id], l, mid);
   build(R[id], mid+1, r);
   seg[id] = seg[L[id]] + seg[R[id]];
}

int update(int pos, int id, int l, int r){
   int newID = NEXT_FREE_INDEX++;
   if(l == r){ 
      seg[newID] = seg[id] + 1;
      return newID;
   }
   int mid = (l + r) >> 1;
   L[newID] = L[id], R[newID] = R[id];
   if(pos <= mid){
      L[newID] = update(pos, L[id], l, mid);
   }
   else{
      R[newID] = update(pos, R[id], mid+1, r);
   }
   seg[newID] = seg[L[newID]] + seg[R[newID]];
   return newID;
}

int query(int id, int newID, int l, int r, int k){
   if(l == r){
      return l;
   }
   int mid = (l + r)>>1;
   if(seg[L[newID]] - seg[L[id]] >= k){
      return query(L[id], L[newID], l, mid, k);
   }
   else{
      return query(R[id], R[newID], mid+1, r, k-seg[L[newID]]+seg[L[id]]);
   }
}

int32_t main(){_

   int q;
   cin>>n;
   cin>>q;

   std::map<int, int> M;
   for (int i = 1; i <= n; ++i)
   {
      cin>>a[i];
      M[a[i]];
   }

   int cnt = 0;
   for(auto it: M)
      M[it.fi] = ++cnt;

   for (int i = 1; i <= n; ++i)
   {
      int x = a[i];
      rev[M[a[i]]] = x;
      a[i] = M[a[i]];  
   }

   build(0,1,n);
   root[0] = ir;

   for (int i = 1; i <= n; ++i)
   {
      root[i] = update(a[i], root[i-1], 1, n);
   }

   while(q--){
      int l, r, k;
      cin>>l>>r>>k;
      int tt = query(root[l-1], root[r], 1, n, k);
      cout<<rev[tt]<<'\n';
   }

   //make sure N size is correct!!!!!!!!!
   return 0;
}
