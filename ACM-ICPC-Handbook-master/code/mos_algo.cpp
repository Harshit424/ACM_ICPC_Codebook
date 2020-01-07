   cin>>q;//no of queries
   #define ppp pair<pair<int, int> , int>
   vector<ppp> queries;
   for (int i = 0; i < q; ++i)
   {
      int l, r;
      cin>>l>>r;
      queries.pb({{l, r}, i});
   }
   int root = sqrt(q);
   sort(all(queries), [&](ppp x, ppp y){
      int block_x = x.first.first / root;
      int block_y = y.first.first / root;
      if(block_x != block_y)
         return block_x < block_y;
      return x.first.second < y.first.second;
   });
   #define ll int
   ll curl = 0, curr = -1;
   vector<int> answer(q);
   for(auto i: v){
      ll l = i.fi.fi, r = i.fi.se;
      while(curr<r){//add
         ++curr;
         add(a[curr]);
      }
      while(curl>l){//add
         --curl;
         add(a[curl]);
      }
      while(curr>r){//remove
         remove(a[curr]);
         --curr;
      }
      while(curl<l){//remove
         remove(a[curl]);
         ++curl;
      }
      answer[i.se] = ans;
      //compute answer accordingly with the add and remove function
   }
   for(auto it: answer)
      cout<<it<<endl;
