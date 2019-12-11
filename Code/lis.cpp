int lis(vector<int> a){
   // strictly-increasing LIS in nlogn
   /*
      in case of longest nondecreasing sequences
      change lower_bound to upper_bound
   */
   vector<int> v;
   for (int i = 0; i < sz(a); i++) {
       auto it = lower_bound(v.begin(), v.end(), a[i]);
       if (it != v.end()) *it = a[i];
       else v.push_back(a[i]);
   }
   return sz(v);
}
