bool vis[N], OnStack[N];
bool iscyclic(int ver){
   vis[ver] = true;
   OnStack[ver] = true;
   for(auto it: v[ver]){
      //adjust as per if graph has weight or not.
      if(!vis[it.fi]){
         if(iscyclic(it.fi)){
            return true;
         }
      }
      else{
         if(OnStack[it.fi]){
            return true;
         }
      }
   }
   OnStack[ver] = false;
   return false;
}

bool cycle(){
   memset(vis, 0, sizeof vis);
   memset(OnStack, 0, sizeof OnStack);
      
   for (int i = 1; i <= n; ++i)if(iscyclic(i)){
      return true;
   }

   return false;
}
