std::vector<std::vector<int>> adj;
std::vector<int> color;
bool bipartite(int v = 0, int p = -1, int c = 0)
{
    if (p == -1)
        color.assign(adj.size(), -1);

    if (color[v] >= 0)
        return color[v] == c;
    color[v] = c;
    par[v] = p;

    for (auto u : adj[v]) {
        if (u == p)
            continue;
        if (!bipartite(u, v, c ^ 1))
            return false;
    }

    return true;
}

int32_t main(){_

   cin>>n>>m;

   adj.resize(n);

    for (int i = 0; i < m; ++i)
    {
      int x, y;
      cin>>x>>y;
      --x, --y;
      adj[x].pb(y);
      adj[y].pb(x);
    }

    // bipartite();

    return 0;
}