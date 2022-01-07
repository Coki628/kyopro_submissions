/*
・これもTLE。
・ダイクストラで、mapで持ってた状態をvectorにして、遷移先のindexも前計算したもの。
　本来なら絶対こっちのが速くなるはずなんだけどこれも何故かTLE。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/base.hpp"

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

// ダイクストラ
vvl dijkstra(vvpll &nodes, int src, int goal=-1) {

    int N = nodes.size();

    vvl res(N);
    vvl comp(N);
    rep(i, N) {
        // 路線毎に探せるように路線cを前にしてソートしておく
        sort(ALL(nodes[i]));
        res[i].assign(nodes[i].size()+1, INF);
    }
    rep(u, N) {
        for (auto [c, v] : nodes[u]) {
            comp[u].eb(bisect_left(nodes[v], {c, u}));
        }
    }

    priority_queue<tuple<ll, ll, ll, ll>, vector<tuple<ll, ll, ll, ll>>, greater<tuple<ll, ll, ll, ll>>> que;
    res[src][nodes[src].size()] = 0;
    que.push({0, -1, nodes[src].size(), src});

    while (!que.empty()) {
        auto [dist, c, ci, u] = que.top(); que.pop();
        if (u == goal and c == -1) return res;
        if (res[u][ci] < dist) continue;
        if (c != -1) {
            // 改札の外
            ll nxci = nodes[u].size();
            if (chmin(res[u][nxci], dist)) {
                que.push({dist, -1, nxci, u});
            }
            // 同じ路線
            ll cj = ci-1;
            while (cj >= 0 and nodes[u][cj].first == c) {
                auto [nxc, v] = nodes[u][cj];
                nxci = comp[u][cj];
                if (chmin(res[v][nxci], dist)) {
                    que.push({dist, nxc, nxci, v});
                }
                cj--;
            }
            cj = ci+1;
            while (cj < nodes[u].size() and nodes[u][cj].first == c) {
                auto [nxc, v] = nodes[u][cj];
                nxci = comp[u][cj];
                if (chmin(res[v][nxci], dist)) {
                    que.push({dist, nxc, nxci, v});
                }
                cj++;
            }
        } else {
            // 違う路線
            rep(i, nodes[u].size()) {
                auto [nxc, v] = nodes[u][i];
                ll nxci = comp[u][i];
                if (c == nxc) continue;
                if (chmin(res[v][nxci], dist+1)) {
                    que.push({dist+1, nxc, nxci, v});
                }
            }
        }
    }
    return res;
}

void solve() {
    ll N, M;
    cin >> N >> M;
    vvpll nodes(N);
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        nodes[u].eb(c, v);
        nodes[v].eb(c, u);
    }

    auto res = dijkstra(nodes, 0, N-1);
    ll ans = res[N-1][nodes[N-1].size()];
    if (ans >= INF) ans = -1;
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
