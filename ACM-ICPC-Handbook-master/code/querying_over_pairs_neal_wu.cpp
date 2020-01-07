// https://www.hackerearth.com/challenges/competitive/october-easy-19/algorithm/absolute-tree-6aed7d30/submission/31998549/
// Enables online insertion of (key, value) pairs and querying of maximum value over keys less than a given limit.
// To query minimums instead, set maximum_mode = false.
template<typename T_key, typename T_value, T_value V_INF, bool maximum_mode = true>
struct online_prefix_max {
    map<T_key, T_value> optimal;
    bool better(T_value a, T_value b) {
        return (a < b) ^ maximum_mode;
    }
    // Queries the maximum value in the map over all entries with key < `key_limit`.
    T_value query(T_key key_limit) const {
        auto it = optimal.lower_bound(key_limit);
        if (it == optimal.begin())
            return maximum_mode ? (is_signed<T_value>::value ? -V_INF : 0) : V_INF;
        it--;
        return it->second;
    }
    // Adds an entry to the map and discards entries that are now obsolete.
    void insert(T_key key, T_value value) {
        auto it = optimal.lower_bound(key);
        // Quit if value is suboptimal.
        if (it != optimal.end() && it->first == key) {
            if (!better(value, it->second))
                return;
        } else if (it != optimal.begin()) {
            auto prev_it = it;
            prev_it--;
            if (!better(value, prev_it->second))
                return;
        }
        while (it != optimal.end() && !better(it->second, value))
            it = optimal.erase(it);
        optimal.insert(it, {key, value});
    }
    //joins b inside a => (curr, b) => curr U B
    void join_into(online_prefix_max b) {
       if (optimal.size() < b.optimal.size())
           swap(*this, b);
       for (auto &p : b.optimal)
           insert(p.first, p.second);
    }
};
// Usage
// online_prefix_max<int, int, inf, false>
//vector<online_prefix_max<int, int, inf, false>> pos;
