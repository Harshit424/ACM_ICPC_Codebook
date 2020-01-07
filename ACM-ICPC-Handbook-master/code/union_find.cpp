struct UnionFind
{
   vector<int> parent, size;
   UnionFind(int n){
      parent.resize(n+1);
      size.resize(n+1);
      for (int i = 1; i <= n; ++i)
      {
         parent[i] = i;
         size[i] = 1;         
      }
   }
   int find(int x){
      while(x != parent[x]){
         parent[x] = parent[parent[x]];
         x = parent[x];
      }
      return x;
   }
   bool unite(int x, int y){
      x = find(x), y = find(y);
      if(x == y)
         return false;
      if(size[x] < size[y])swap(x, y);
      size[x] += size[y];
      parent[y] = x;
      return true;
   } 
   int getSize(int x){
      x = find(x);
      return size[x];
   }
};
/*** USAGE
UnionFind S(n);
****/
