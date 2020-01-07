// dp_hull enables you to do the following two operations in amortized O(log n) time:
// 1. Insert a pair (a_i, b_i) into the structure
// 2. For any value of x, query the maximum value of a_i * x + b_i
// All values a_i, b_i, and x can be positive or negative.
struct dp_hull {
    struct segment {
        point p;
        mutable point next_p;
        segment(point _p = {0, 0}, point _next_p = {0, 0}) : p(_p), next_p(_next_p) {}
        bool operator<(const segment &other) const {
            // Sentinel value indicating we should binary search the set for a single x-value.
            if (p.y == LL_INF)
                return p.x * (other.next_p.x - other.p.x) <= (other.p.y - other.next_p.y) * next_p.x;
            return make_pair(p.x, p.y) < make_pair(other.p.x, other.p.y);
        }
    };
    set<segment> segments;
    bool empty() const {
        return segments.empty();
    }
    set<segment>::iterator prev(set<segment>::iterator it) const {
        return it == segments.begin() ? it : --it;
    }
    set<segment>::iterator next(set<segment>::iterator it) const {
        return it == segments.end() ? it : ++it;
    }
    bool bad(set<segment>::iterator it) const {
        return it != segments.begin() && next(it) != segments.end() && left_turn(prev(it)->p, it->p, next(it)->p);
    }
    void insert(const point &p) {
        set<segment>::iterator it = segments.insert(segment(p, p)).first;
        if (bad(it) || (next(it) != segments.end() && it->p.x == next(it)->p.x)) {
            segments.erase(it);
            return;
        }
        if (it != segments.begin() && it->p.x == prev(it)->p.x)
            segments.erase(prev(it));
        while (bad(prev(it)))
            segments.erase(prev(it));
        while (bad(next(it)))
            segments.erase(next(it));
        if (it != segments.begin())
            prev(it)->next_p = it->p;
        if (next(it) != segments.end())
            it->next_p = next(it)->p;
    }
    void insert(long long a, long long b) {
        insert(point(a, b));
    }
    // Queries the maximum value of ax + by.
    long long query(long long x, long long y = 1) const {
        assert(y > 0);
        set<segment>::iterator it = segments.upper_bound(segment(point(x, LL_INF), point(y, LL_INF)));
        return it->p.x * x + it->p.y * y;
    }
};
