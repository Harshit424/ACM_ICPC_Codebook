const int MOD = (int)1e9 + 7;
 
struct mod_int {
    int val;
 
    mod_int(long long v = 0) {
        if (v < 0)
            v = v % MOD + MOD;
 
        if (v >= MOD)
            v %= MOD;
 
        val = v;
    }
 
    static int mod_inv(int a, int m = MOD) {
        // https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Example
        int g = m, r = a, x = 0, y = 1;
 
        while (r != 0) {
            int q = g / r;
            g %= r; swap(g, r);
            x -= q * y; swap(x, y);
        }
 
        return x < 0 ? x + m : x;
    }
 
    explicit operator int() const {
        return val;
    }
 
    mod_int& operator+=(const mod_int &other) {
        val += other.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }
 
    mod_int& operator-=(const mod_int &other) {
        val -= other.val;
        if (val < 0) val += MOD;
        return *this;
    }
 
    mod_int& operator*=(const mod_int &other) {
        val = (uint64_t) val * other.val % MOD;
        return *this;
    }
 
    mod_int& operator/=(const mod_int &other) {
        return *this *= other.inv();
    }
 
    friend mod_int operator+(const mod_int &a, const mod_int &b) {
        return mod_int(a) += b;
    }
 
    friend mod_int operator-(const mod_int &a, const mod_int &b) {
        return mod_int(a) -= b;
    }
 
    friend mod_int operator*(const mod_int &a, const mod_int &b) {
        return mod_int(a) *= b;
    }
 
    friend mod_int operator/(const mod_int &a, const mod_int &b) {
        return mod_int(a) /= b;
    }
 
    mod_int& operator++() {
        val = val == MOD - 1 ? 0 : val + 1;
        return *this;
    }
 
    mod_int operator++(int) {
        mod_int before = *this;
        ++*this;
        return before;
    }
 
    mod_int& operator--() {
        val = val == 0 ? MOD - 1 : val - 1;
        return *this;
    }
 
    mod_int operator--(int) {
        mod_int before = *this;
        --*this;
        return before;
    }
 
    mod_int operator-() const {
        return val == 0 ? 0 : MOD - val;
    }
 
    bool operator==(const mod_int &other) const {
        return val == other.val;
    }
 
    bool operator!=(const mod_int &other) const {
        return val != other.val;
    }
 
    mod_int inv() const {
        return mod_inv(val);
    }
 
    mod_int pow(long long p) const {
        assert(p >= 0);
        mod_int a = *this, result = 1;
 
        while (p > 0) {
            if (p & 1)
                result *= a;
 
            a *= a;
            p >>= 1;
        }
 
        return result;
    }
};
 
vector<mod_int> factorial, inv_factorial;
vector<mod_int> inv;
 
void prepare_factorials(int max) {
    inv.assign(max + 1, 1);
 
    // Make sure MOD is prime, which is necessary for the inverse algorithm below.
    for (int p = 2; p * p <= MOD; p++)
        assert(MOD % p != 0);
 
    for (int i = 2; i <= max; i++)
        inv[i] = inv[MOD % i] * (MOD - MOD / i);
 
    factorial.resize(max + 1);
    inv_factorial.resize(max + 1);
    factorial[0] = inv_factorial[0] = 1;
 
    for (int i = 1; i <= max; i++) {
        factorial[i] = i * factorial[i - 1];
        inv_factorial[i] = inv[i] * inv_factorial[i - 1];
    }
}
 
mod_int choose(int n, int r) {
    if (r < 0 || r > n)
        return 0;
 
    return factorial[n] * inv_factorial[r] * inv_factorial[n - r];
}
