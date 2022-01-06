#include "../base.hpp"

// 参考：https://lorent-kyopro.hatenablog.com/entry/2020/07/24/170656
// 区間に辺を張るテク
template<typename W>
struct RangeEdgeGraph {
    int n;
    struct edge { int to; W weight; };
    vector<vector<edge>> g;
    
    // RangeEdgeGraph(int n) : n(n) {
    //     g.resize(4*n);
    //     for (int i = 1; i < n; ++i) {
    //         int cl = i<<1|0, cr = i<<1|1;
    //         g[i].push_back({cl, 0});
    //         g[i].push_back({cr, 0});
    //         g[cl+2*n].push_back({i+2*n, 0});
    //         g[cr+2*n].push_back({i+2*n, 0});
    //     }
    //     for (int i = n; i < 2*n; ++i) g[i].push_back({i+2*n, 0});
    // }

    // // from [l1, r1) to [l2, r2)
    // void add_edge(int l1, int r1, int l2, int r2, W w) {
    //     int idx = g.size();
    //     for (l1 += n, r1 += n; l1 < r1; l1 >>= 1, r1 >>= 1) {
    //         if (l1 & 1) g[l1+2*n].push_back({idx, 0}), l1++;
    //         if (r1 & 1) --r1, g[r1+2*n].push_back({idx, 0});
    //     }
    //     vector<edge> node;
    //     for (l2 += n, r2 += n; l2 < r2; l2 >>= 1, r2 >>= 1) {
    //         if (l2 & 1) node.push_back({l2++, w});
    //         if (r2 & 1) node.push_back({--r2, w});
    //     }
    //     g.push_back(node);
    // }

    RangeEdgeGraph(int n) : n(n) {
        g.resize(3*n);
        for (int i = 1; i < n; ++i) {
            int cl = i<<1|0, cr = i<<1|1;
            _add_edge(i, cl, 0);
            _add_edge(i, cr, 0);
            _add_edge(cl+2*n, i+2*n, 0);
            _add_edge(cr+2*n, i+2*n, 0);
        }
    }

    // map [3n, 4n) -> [n, 2n)
    void _add_edge(int u, int v, W w) {
        if (3*n <= u) u -= 2*n;
        g[u].push_back({v, w});
    }

    // from [l1, r1) to [l2, r2)
    void add_edge(int l1, int r1, int l2, int r2, W w) {
        int idx = g.size();
        for (l1 += n, r1 += n; l1 < r1; l1 >>= 1, r1 >>= 1) {
            if (l1 & 1) _add_edge(l1+2*n, idx, 0), l1++;
            if (r1 & 1) --r1, _add_edge(r1+2*n, idx, 0);
        }
        vector<edge> node;
        for (l2 += n, r2 += n; l2 < r2; l2 >>= 1, r2 >>= 1) {
            if (l2 & 1) node.push_back({l2++, w});
            if (r2 & 1) node.push_back({--r2, w});
        }
        g.push_back(node);
    }

    // from u to v
    void add_edge(int u, int v, W w) {
        add_edge(u, u+1, v, v+1, w);
    }

    vector<W> dijkstra(int s) {
        s += n;
        vector<W> dist(g.size(), INF);
        dist[s] = 0;
        using P = pair<W, int>;
        priority_queue<P, vector<P>, greater<P>> que;
        que.emplace(0, s);
        while (!que.empty()) {
            P p = que.top();
            que.pop();
            int v = p.second;
            if (dist[v] < p.first) continue;
            for (edge& e : g[v]) {
                if (dist[e.to] > dist[v] + e.weight) {
                    dist[e.to] = dist[v] + e.weight;
                    que.emplace(dist[e.to], e.to);
                }
            }
        }
        vector<W> res(dist.begin() + n, dist.begin() + 2*n);
        return res;
    }
};
