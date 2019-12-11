// set the max value of bits in mask
const int C = 20;
vector<int32_t> max_subset(1 << C, 0);
 
// For every mask, computes the max of values[sub] where sub is a submask of mask.
template<typename T_out, typename T_in>
vector<T_out> submask_max(int n, const vector<T_in> &values) {
    vector<T_out> dp(values.begin(), values.end());
 
    for (int bit = 0; bit < n; bit++)
        for (int mask = 0; mask < 1 << n; mask++)
            if (mask >> bit & 1)
                dp[mask] = max(dp[mask], dp[mask ^ 1 << bit]);
 
    return dp;
}

/***
make changes to max_subset as question demands, and then use below to get the SOS dp
max_subset = submask_max<int32_t>(C, max_subset);
***/
