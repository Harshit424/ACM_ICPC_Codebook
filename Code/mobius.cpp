const int MAX = 1000001;

vector<int> lp, primes, mobius;

void factor_sieve() {
	lp.resize(MAX);
	lp[1] = 1;
	for (int i = 2; i < MAX; ++i) {
		if (lp[i] == 0) {
			lp[i] = i;
			primes.emplace_back(i);
		}
		for (int j = 0; j < primes.size() && primes[j] <= lp[i]; ++j) {
			int x = i * primes[j];
			if (x >= MAX) break;
			lp[x] = primes[j];
		}
	}
}

//Complexity : O(n)
void mobius_sieve() {
	mobius.resize(MAX);
	mobius[1] = 1;
	for(int i = 2; i < MAX; ++i) {
		int w = lp[i];
		if (lp[i/w] == w) {
			mobius[i] = 0;
		}
		else {
			mobius[i] = -mobius[i/w];
		}
	}
}
