#include "../macros.hpp"
#include "../common/chmin.hpp"

// 01BFS(コストが0or1なら使える)
vector<ll> bfs01(const vvpll &nodes, const vector<ll> &src) {

    ll N = nodes.size();
    vector<ll> res(N, INF);
    deque<ll> que;
    for (ll s : src) {
        res[s] = 0;
        que.push_back(s);
    }

    while (!que.empty()) {
        ll u = que.front(); que.pop_front();
        for (auto [v, c] : nodes[u]) {
            if (c == 0 and res[u] < res[v]) {
                res[v] = res[u];
                que.push_front(v);
            } elif (c == 1 and res[u]+1 < res[v]) {
                res[v] = res[u]+1;
                que.push_back(v);
            } else {
                assert(0);
            }
        }
    }
    return res;
}
