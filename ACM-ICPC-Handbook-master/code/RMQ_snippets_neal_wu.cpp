template<typename T>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
template<typename T>
struct RMQ {
    int n = 0, levels = 0;
    vector<T> values;
    vector<vector<int>> range_low;
    RMQ(const vector<T> &_values = {}) {
        if (!_values.empty())
            build(_values);
    }
    static int largest_bit(int x) {
        return 31 - __builtin_clz(x);
    }
    int min_index(int a, int b) const {
        return values[a] < values[b] ? a : b;
    }
    void build(const vector<T> &_values) {
        values = _values;
        n = values.size();
        levels = largest_bit(n) + 1;
        range_low.resize(levels);
        for (int k = 0; k < levels; k++)
            range_low[k].resize(n - (1 << k) + 1);
        for (int i = 0; i < n; i++)
            range_low[0][i] = i;
        for (int k = 1; k < levels; k++)
            for (int i = 0; i <= n - (1 << k); i++)
                range_low[k][i] = min_index(range_low[k - 1][i], range_low[k - 1][i + (1 << (k - 1))]);
    }
    int rmq_index(int a, int b) const {
        assert(a < b);
        int level = largest_bit(b - a);
        return min_index(range_low[level][a], range_low[level][b - (1 << level)]);
    }
    T rmq_value(int a, int b) const {
        return values[rmq_index(a, b)];
    }
};
template<typename T>
struct RMQ4 {
    static const int BLOCK = 4;
    int n = 0, levels = 0;
    vector<T> values;
    vector<int> block_index;
    RMQ<T> rmq;
    RMQ4(const vector<T> &_values = {}) {
        if (!_values.empty())
            build(_values);
    }
    int min_index(int a, int b) const {
        return values[a] < values[b] ? a : b;
    }
    void build(const vector<T> &_values) {
        values = _values;
        n = values.size();
        block_index.resize(n / BLOCK);
        vector<T> block_values(n / BLOCK);
        for (int i = 0; i < n / BLOCK; i++) {
            block_values[i] = values[BLOCK * i];
            block_index[i] = BLOCK * i;
            for (int j = BLOCK * i + 1; j < BLOCK * (i + 1); j++)
                if (values[j] < block_values[i]) {
                    block_values[i] = values[j];
                    block_index[i] = j;
                }
        }
        rmq.build(block_values);
    }
    int rmq_index(int a, int b) const {
        assert(a < b);
        int answer = a;
        while (a % BLOCK != 0 && a < b)
            answer = min_index(answer, a++);
        while (b % BLOCK != 0 && a < b)
            answer = min_index(answer, --b);
        if (a < b)
            answer = min_index(answer, block_index[rmq.rmq_index(a / BLOCK, b / BLOCK)]);
        return answer;
    }
    T rmq_value(int a, int b) const {
        return values[rmq_index(a, b)];
    }
};
struct LCA {
    int n = 0;
    vector<vector<int>> adj;
    vector<int> parent;
    vector<int> depth;
    vector<int> euler;
    vector<int> first_occurrence;
    RMQ4<int> rmq;
    LCA(int _n = 0) {
        init(_n);
    }
    LCA(const vector<vector<int>> &_adj) {
        init(_adj);
    }
    void init(int _n) {
        n = _n;
        adj.assign(n, {});
        parent.resize(n);
        depth.resize(n);
        first_occurrence.resize(n);
    }
    void init(const vector<vector<int>> &_adj) {
        init(_adj.size());
        adj = _adj;
    }
    void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    void dfs(int node, int par) {
        parent[node] = par;
        depth[node] = par < 0 ? 0 : depth[par] + 1;
        first_occurrence[node] = euler.size();
        euler.push_back(node);
        for (int neighbor : adj[node])
            if (neighbor != par) {
                dfs(neighbor, node);
                euler.push_back(node);
            }
    }
    void build(int root = 0) {
        if (n == 0) return;
        dfs(root, -1);
        assert((int) euler.size() == 2 * n - 1);
        vector<int> euler_depths;
        for (int node : euler)
            euler_depths.push_back(depth[node]);
        rmq.build(euler_depths);
    }
    int get_lca(int a, int b) const {
        a = first_occurrence[a];
        b = first_occurrence[b];
        if (a > b)
            swap(a, b);
        return euler[rmq.rmq_index(a, b + 1)];
    }
    bool is_ancestor(int a, int b) const {
        return get_lca(a, b) == a;
    }
    bool on_path(int x, int a, int b) const {
        int anc = get_lca(a, b);
        return is_ancestor(anc, x) && (is_ancestor(x, a) || is_ancestor(x, b));
    }
    int get_dist(int a, int b) const {
        return depth[a] + depth[b] - 2 * depth[get_lca(a, b)];
    }
};
template<typename T>
struct fenwick_tree {
    int tree_n = 0;
    vector<T> tree;
    fenwick_tree(int n = 0) {
        if (n > 0)
            init(n);
    }
    void init(int n) {
        tree_n = n;
        tree.assign(tree_n + 1, 0);
    }
    // O(n) initialization of the Fenwick tree.
    void build(const auto &initial) {
        assert((int) initial.size() == tree_n);
        for (int i = 1; i <= tree_n; i++) {
            tree[i] = initial[i - 1];
            for (int k = (i & -i) >> 1; k > 0; k >>= 1)
                tree[i] += tree[i - k];
        }
    }
    // index is in [0, tree_n).
    void update(int index, const T &change) {
        for (int i = index + 1; i <= tree_n; i += i & -i)
            tree[i] += change;
    }
    // Returns the sum of the range [0, count).
    T query(int count) const {
        T sum = 0;
        for (int i = count; i > 0; i -= i & -i)
            sum += tree[i];
        return sum;
    }
    // Returns the sum of the range [a, b).
    T query(int a, int b) const {
        return query(b) - query(a);
    }
    // Returns the last i in [0, N] such that tree_query(i) <= sum, or -1 if no such i exists.
    int find_last_prefix(T sum) const {
        if (sum < 0)
            return -1;
        int prefix = 0;
        for (int k = 31 - __builtin_clz(tree_n); k >= 0; k--)
            if (prefix + (1 << k) <= tree_n && tree[prefix + (1 << k)] <= sum) {
                prefix += 1 << k;
                sum -= tree[prefix];
            }
        return prefix;
    }
};
template<typename T>
struct path_sum_DS {
    int n = 0;
    bool vertex_mode;
    vector<vector<int>> adj;
    vector<int> parent, depth;
    vector<int> tour_start, tour_end, postorder;
    vector<T> values;
    fenwick_tree<T> tour_tree, postorder_tree;
    LCA lca;
    path_sum_DS() {}
    path_sum_DS(int _n, bool _vertex_mode) {
        init(_n, _vertex_mode);
    }
    void init(int _n, bool _vertex_mode) {
        n = _n;
        vertex_mode = _vertex_mode;
        adj.assign(n, {});
        parent.resize(n);
        depth.resize(n);
        tour_start.resize(n);
        tour_end.resize(n);
        postorder.resize(n);
        values.assign(n, 0);
        tour_tree.init(n);
        postorder_tree.init(n);
        lca.init(n);
    }
    void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
        lca.add_edge(a, b);
    }
    void dfs(int node, int par) {
        static int tour1, tour2;
        if (par < 0)
            tour1 = tour2 = 0;
        parent[node] = par;
        depth[node] = par < 0 ? 0 : depth[par] + 1;
        tour_start[node] = tour1++;
        for (int neighbor : adj[node])
            if (neighbor != par)
                dfs(neighbor, node);
        tour_end[node] = tour1;
        postorder[node] = tour2++;
    }
    void build() {
        if (n == 0) return;
        dfs(0, -1);
        lca.build();
    }
    void update_node(int node, int change) {
        values[node] += change;
        tour_tree.update(tour_start[node], change);
        postorder_tree.update(postorder[node], change);
    }
    void update_edge(int a, int b, int change) {
        // Edge values are stored at the deeper node.
        if (depth[a] < depth[b])
            swap(a, b);
        update_node(a, change);
    }
    // Returns the sum of tree values for all nodes on the path from `node` to the root, inclusive.
    int query_root_path(int node) {
        // The set of nodes whose tour_start is less than tour_end[node] minus the set of nodes whose postorder is less
        // than postorder[node] is exactly the path from node to the root, inclusive.
        return tour_tree.query(tour_end[node]) - postorder_tree.query(postorder[node]);
    }
    // Returns the sum of tree values for all nodes / edges on the path from `u` to `v`, inclusive.
    int query_path(int u, int v, int ancestor = -1) {
        if (ancestor < 0)
            ancestor = lca.get_lca(u, v);
        return query_root_path(u) + query_root_path(v) - 2 * query_root_path(ancestor) + (
            vertex_mode ? values[ancestor] : 0);
    }
};
struct query {
    int x, y, q_index, sign;
    query(int _x = -1, int _y = -1, int _q_index = -1, int _sign = 0) : x(_x), y(_y), q_index(_q_index), sign(_sign) {}
};
int N, Q;
LCA lca;
vector<vector<query>> queries;
vector<int> answers;
path_sum_DS<int> path_sums;
void solve(int node) {
    path_sums.update_node(node, +1);
    for (query &q : queries[node])
        answers[q.q_index] += q.sign * path_sums.query_path(q.x, q.y);
    for (int neighbor : lca.adj[node])
        if (neighbor != lca.parent[node])
            solve(neighbor);
    path_sums.update_node(node, -1);
}
int main() {
    scanf("%d %d", &N, &Q);
    lca.init(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        lca.add_edge(a, b);
    }
    lca.build();
    path_sums.init(N, true);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        path_sums.add_edge(a, b);
    }
    path_sums.build();
    queries.assign(N, {});
    answers.assign(Q, 0);
    for (int q = 0; q < Q; q++) {
        int u, v, x, y;
        scanf("%d %d %d %d", &u, &v, &x, &y);
        u--; v--; x--; y--;
        int anc = lca.get_lca(u, v);
        queries[u].emplace_back(x, y, q, +1);
        queries[v].emplace_back(x, y, q, +1);
        queries[anc].emplace_back(x, y, q, -1);
        if (lca.parent[anc] >= 0)
            queries[lca.parent[anc]].emplace_back(x, y, q, -1);
    }
    solve(0);
    for (int q = 0; q < Q; q++)
        printf("%d\n", answers[q]);
}
