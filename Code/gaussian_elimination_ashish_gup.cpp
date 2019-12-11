struct Gauss 
{
	static const int bits = 20;

	int table[bits];

	Gauss() 
	{
		for(int i = 0; i < bits; i++) 
			table[i] = 0;
	}

	int size() 
	{
		int ans = 0;
		for(int i = 0; i < bits; i++) 
		{
			if(table[i]) 
				ans++;
		}
		return ans;
	}

	// Returns true if there exists subset with xor x
	bool can(int x) 
	{
		for(int i = bits-1; i >= 0; i--) 
			x = min(x, x ^ table[i]);
		return x == 0;
	}

	void add(int x) 
	{
		for(int i = bits-1; i >= 0 && x; i--) 
		{
			if(table[i] == 0) 
			{
				table[i] = x;
				x = 0;
			} 
			else 
				x = min(x, x ^ table[i]);
		}
	}

	// Returns maximum xor of any subset
	int getBest() 
	{
		int x = 0;
		for(int i = bits-1; i >= 0; i--) 
			x = max(x, x ^ table[i]);
		return x;
	}

	// Returns minimum xor of any subset with num
	// num = 0 -> minimum subset xor
	int getMin(int num = 0) {
		int res = num;
		for(int i = bits-1; i >= 0; --i) {
			if ((res ^ table[i]) < res) {
				res ^= table[i];
			}
		}
		return res;
	}

	void merge(Gauss &other)
	{
		for(int i = bits-1; i >= 0; i--)
			add(other.table[i]);
	}
};
