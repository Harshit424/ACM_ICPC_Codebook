int phi[N+5];
void phi_calc(){
   for (int i = 0; i < N; i++) {
      phi[i] = i; 
   }
   for (int i = 1; i < N; i++)
      for (int j = 2 * i; j < N; j += i)
         phi[j] -= phi[i];
}
