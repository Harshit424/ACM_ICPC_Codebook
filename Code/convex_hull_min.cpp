struct Convex{
   typedef pair<int,int> PII;
   vector<PII> lns;
   bool shit(int a,int b,int c){
      return (lns[c].second-lns[a].second)*(lns[a].first-lns[b].first)<(lns[b].second-lns[a].second)*(lns[a].first-lns[c].first);//if WA comes, it might be because this has overflowen. In that case make, floating point comparison
   }
   //line equation is Ax + B
   void add_line(int A,int B){
      lns.push_back({A,B});
      while(sz(lns)>=3&&shit(sz(lns)-3,sz(lns)-2,sz(lns)-1)){
         lns[sz(lns)-2]=lns[sz(lns)-1];
         lns.pop_back();
      }
   }
   int get(int whr,int x){
      return lns[whr].first*x+lns[whr].second;
   }
   int query(int x){
      int l=0,r=sz(lns)-1;
      while(r>l){
         int m=(l+r)>>1;
         if(get(m,x)>=get(m+1,x)){
            l=m+1;
         }else{
            r=m;
         }
      }
      return get(l,x);
   }
}s;
