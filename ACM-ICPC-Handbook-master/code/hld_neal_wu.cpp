struct subtree_heavy_light {
    int n = 0;
    bool vertex_mode;
    vector<vector<int>> adj;
    vector<int> parent;
    vector<int> depth;
    vector<int> subtree_size;
    vector<int> tour_start, tour_end;
    vector<int> chain_root;
    list_fenwick_tree full_tree;
    subtree_heavy_light() {}
    subtree_heavy_light(int _n, bool _vertex_mode) {
        init(_n, _vertex_mode);
    }
    void init(int _n, bool _vertex_mode) {
        n = _n;
        vertex_mode = _vertex_mode;
        adj.assign(n, {});
        parent.resize(n);
        depth.resize(n);
        subtree_size.resize(n);
        tour_start.resize(n);
        tour_end.resize(n);
        chain_root.resize(n);
    }
    void add_edge(int a, int b) {
         adj[a].push_back(b);
         adj[b].push_back(a);
    }
    void dfs(int node, int par) {
        parent[node] = par;
        depth[node] = par < 0 ? 0 : depth[par] + 1;
        subtree_size[node] = 1;
        // Erase the edge to the parent.
        for (int &neighbor : adj[node])
            if (neighbor == par) {
                swap(neighbor, adj[node].back());
                adj[node].pop_back();
                break;
            }
        for (int &child : adj[node]) {
            dfs(child, node);
            subtree_size[node] += subtree_size[child];
            if (subtree_size[child] > subtree_size[adj[node].front()])
                swap(child, adj[node].front());
        }
    }
    void chain_dfs(int node, int par, bool heavy) {
        static int tour;
        if (par < 0)
            tour = 0;
        chain_root[node] = heavy ? chain_root[parent[node]] : node;
        tour_start[node] = tour++;
        bool heavy_child = true;
        for (int child : adj[node]) {
            chain_dfs(child, node, heavy_child);
            heavy_child = false;
        }
        tour_end[node] = tour;
    }
    void build(const auto &values) {
        if (n == 0) return;
        dfs(0, -1);
        chain_dfs(0, -1, false);
        full_tree.init(n);
        assert((int) values.size() == n);
        for (int i = 0; i < n; i++)
            full_tree.update(tour_start[i], values[i]);
        full_tree.build();
    }
    bool is_ancestor(int a, int b) const {
        return tour_start[a] <= tour_start[b] && tour_start[b] < tour_end[a];
    }
    // Returns the child of a that is an ancestor of b.
    int child_ancestor(int a, int b) const {
        assert(is_ancestor(a, b));
        assert(!adj[a].empty());
        int low = 0, high = adj[a].size() - 1;
        while (low < high) {
            int mid = (low + high) / 2;
            if (tour_start[b] < tour_end[adj[a][mid]])
                high = mid;
            else
                low = mid + 1;
        }
        int child = adj[a][low];
        assert(is_ancestor(child, b));
        return child;
    }
    // void update_subtree(int v, const segment_change &change) {
    //     full_tree.update(tour_start[v] + (vertex_mode ? 0 : 1), tour_end[v], change);
    // }
    int query_subtree(int v, int L, int R) {
        return full_tree.query(tour_start[v] + (vertex_mode ? 0 : 1), tour_end[v], L, R);
    }
    template<typename T_tree_op>
    void process_path(int u, int v, T_tree_op &&op) {
        while (chain_root[u] != chain_root[v]) {
            // Always pull up the chain with the deeper root.
            if (depth[chain_root[u]] > depth[chain_root[v]])
                swap(u, v);
            int root = chain_root[v];
            op(full_tree, tour_start[root], tour_start[v] + 1);
            v = parent[root];
        }
        if (depth[u] > depth[v])
            swap(u, v);
        // u is now an ancestor of v.
        op(full_tree, tour_start[u] + (vertex_mode ? 0 : 1), tour_start[v] + 1);
    }
    int query_path(int u, int v, int L, int R) {
        int answer = 0;
        process_path(u, v, [&](auto &tree, int a, int b) {
            answer += tree.query(a, b, L, R);
        });
        return answer;
    }
    // void update_path(int u, int v, const segment_change &change) {
    //     process_path(u, v, [&](auto &tree, int a, int b) {
    //         tree.update(a, b, change);
    //     });
    // }
};
