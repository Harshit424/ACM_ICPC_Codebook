//Bellman Ford Algo to find the single source shortest distance
//works even for negative cycle graph
//logic a shortest path can be atmost (n-1) edges long. So run n-1 iteration to find 
//shortest distance from source to other vertices.
//also, even after n-1 iteration the distance of any vertex decreases, then we are sure
//that graph consists of negative cycle 

vector<pair<pair<int, int>, int> > v;//stores edges and wts in graph in form ((edges), wt)
bool bellman_ford(int source){
   for (int i = 0; i <= n ; ++i){
      dis[i] = inf;//assign max distance to all
   }

   dis[source] = 0;

   for (int i = 0; i < edges; ++i){
      cin>>from>>next>>weight;
      v.push_back({{from, next}, weight});
   }

   for (int i = 0; i < n-1; ++i)
   {
      for(auto it: v){
         int x = it.F.F, y = it.F.S;
         int wt = it.S;
         if(dis[y] > dis[x] + wt){
            dis[y] = dis[x] + wt;
         }
      }
   }

   //we do this process for n-1 times since max. times the change in the distance can occur is n-1;
   for(auto it: v){
      int x = it.F.F, y = it.F.S;
      int wt = it.S;
      if(dis[y] > dis[x] + wt){
         return 0;//negative cycle is present
      }
   }

   return 1;//no negative cycle found. dist[i] stores min distance from the source vertex
}