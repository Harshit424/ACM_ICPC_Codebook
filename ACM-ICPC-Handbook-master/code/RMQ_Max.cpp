//https://codeforces.com/blog/entry/7677#comment-133682
#define SZ 262144//power of 2, in this case 2^17
int IT[SZ + SZ];
int n, H[N], A[N];
void Put(int a, long long b) {
    a += SZ;
    while (a) {
        IT[a] = max(IT[a], b);
        a >>= 1;
    }
}
long long Max(int b, int e) {
    long long r = 0;
    b += SZ, e += SZ;
    while (b <= e) {
        r = max(r, max(IT[b], IT[e]));
        b = (b + 1) >> 1, e = (e - 1) >> 1;
    }
    return r;
}
