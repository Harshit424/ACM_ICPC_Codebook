const int INF = 1e9 + 5;

struct point {
    int x, y;

    point() : x(0), y(0) {}

    point(int _x, int _y) : x(_x), y(_y) {}
};

// reverse_monotonic_dp_hull enables you to do the following two operations in amortized O(1) time:
// 1. Insert a pair (a_i, b_i) into the structure. a_i must be non-decreasing.
// 2. For any value of x, query the maximum value of a_i * x + b_i. x must be non-increasing.
// All values a_i, b_i, and x can be positive or negative.
struct reverse_monotonic_dp_hull {
    vector<point> points;

    int size() const {
        return (int) points.size();
    }

    void clear() {
        points.clear();
        prev_x = INF;
    }

    static int floor_div(int a, int b) {
        return a / b - ((a ^ b) < 0 && a % b != 0);
    }

    static bool bad_middle(const point &a, const point &b, const point &c) {
        // This checks whether the x-value where b becomes better than a comes after the x-value where c becomes better
        // than a. It's fine to round down here if we will only query integer x-values. (C++ division rounds to zero)
        return floor_div(a.y - b.y, b.x - a.x) >= floor_div(b.y - c.y, c.x - b.x);
    }

    void insert(const point &p) {
        assert(size() == 0 || p.x >= points.back().x);

        if (size() > 0 && p.x == points.back().x) {
            if (p.y <= points.back().y)
                return;

            points.pop_back();
        }

        while (size() >= 2 && bad_middle(points[points.size() - 2], points.back(), p))
            points.pop_back();

        points.push_back(p);
    }

    void insert(int a, int b) {
        insert(point(a, b));
    }

    int prev_x = INF;

    // Queries the maximum value of ax + b.
    int query(int x) {
        assert(x <= prev_x);
        prev_x = x;

        while (size() >= 2 && x * (points.back().x - points[size() - 2].x) <= points[size() - 2].y - points.back().y)
            points.pop_back();

        return points.back().x * x + points.back().y;
    }
};
