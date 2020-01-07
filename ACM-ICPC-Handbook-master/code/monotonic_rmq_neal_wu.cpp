template<typename T, bool maximum_mode>
struct monotonic_rmq {
    vector<pair<T, int>> values;
    int front = 0, current_index = 0;
    int size() const {
        return (int) values.size() - front;
    }
    bool better(const T &a, const T &b) const {
        return (a < b) ^ maximum_mode;
    }
    // Adds a value and returns its index.
    int add(const T &x) {
        while (size() > 0 && !better(values.back().first, x))
            values.pop_back();
        values.emplace_back(x, current_index);
        return current_index++;
    }
    // Queries for the maximum (minimum) with index at least the given `index`.
    T query(int index) {
        while (size() > 0 && values[front].second < index)
            front++;
        assert(size() > 0);
        return values[front].first;
    }
};
