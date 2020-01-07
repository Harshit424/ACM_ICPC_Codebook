struct log_lca {
    int n = 0;
    vector<int> parent, depth;
    vector<vector<int>> adj;
    vector<vector<int>> ancestor;
    log_lca(int _n = 0) {
        init(_n);
    }
    void init(int _n) {
        n = _n;
        parent.resize(n);
        depth.resize(n);
        adj.assign(n, {});
    }
    static int largest_bit(int x) {
        return 31 - __builtin_clz(x);
    }
    void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    void dfs(int node, int par) {
        depth[node] = par < 0 ? 0 : depth[par] + 1;
        parent[node] = par;
        for (int neighbor : adj[node])
            if (neighbor != par)
                dfs(neighbor, node);
    }
    void build() {
        dfs(0, -1);
        ancestor.assign(largest_bit(n) + 1, vector<int>(n));
        ancestor[0] = parent;
        for (int k = 0; k < largest_bit(n); k++)
            for (int i = 0; i < n; i++)
                ancestor[k + 1][i] = ancestor[k][i] < 0 ? -1 : ancestor[k][ancestor[k][i]];
    }
    int get_lca(int a, int b) const {
        if (depth[a] > depth[b])
            swap(a, b);
        int difference = depth[b] - depth[a];
        for (int k = 0; 1 << k <= difference; k++)
            if (difference & 1 << k)
                b = ancestor[k][b];
        if (a == b)
            return a;
        assert(a != b && depth[a] == depth[b]);
        for (int k = largest_bit(depth[a]); k >= 0; k--)
            if (ancestor[k][a] != ancestor[k][b]) {
                a = ancestor[k][a];
                b = ancestor[k][b];
            }
        assert(parent[a] == parent[b]);
        return parent[a];
    }
    int get_dist(int a, int b) const {
        return depth[a] + depth[b] - 2 * depth[get_lca(a, b)];
    }
    int get_kth_ancestor(int v, int k) const {
        for (int i = 0; 1 << i <= k; i++)
            if (k & 1 << i) {
                v = ancestor[i][v];
                if (v < 0)
                    break;
            }
        return v;
    }
    int get_kth_node_on_path(int a, int b, int k) const {
        int anc = get_lca(a, b);
        int first_half = depth[a] - depth[anc];
        int second_half = depth[b] - depth[anc];
        assert(0 <= k && k <= first_half + second_half);
        if (k < first_half)
            return get_kth_ancestor(a, k);
        else
            return get_kth_ancestor(b, first_half + second_half - k);
    }
};
int N;
log_lca lca;
vector<int> center = {-1, -1};
int diameter = 0;
void add_to_center(int p) {
    if (center[0] < 0) {
        center = {p, p};
        return;
    }
    int dist0 = lca.get_dist(p, center[0]);
    int dist1 = lca.get_dist(p, center[1]);
    if (dist0 + dist1 <= diameter)
        return;
    if (dist0 < dist1) {
        swap(dist0, dist1);
        swap(center[0], center[1]);
    }
    int new_diameter = diameter / 2 + dist0;
    center[0] = lca.get_kth_node_on_path(center[0], p, new_diameter / 2 - diameter / 2);
    center[1] = lca.get_kth_node_on_path(center[0], p, new_diameter % 2);
    diameter = new_diameter;
}
int main() {
    scanf("%d", &N);
    lca.init(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        lca.add_edge(a, b);
    }
    lca.build();
    for (int i = 0; i < N; i++) {
        int p;
        scanf("%d", &p);
        p--;
        add_to_center(p);
        printf("%d%c", min(center[0], center[1]) + 1, i < N - 1 ? ' ' : '\n');
    }
}
