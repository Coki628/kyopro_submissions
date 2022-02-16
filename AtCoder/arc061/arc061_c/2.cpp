/*
・これはTLE。
・01BFS
・01BFSでやってた方にもAC解と同じような処置を施してみたんだけど、
　こっちはなんかTLEする…。絶対ダイクストラより速いはずなんだけど。。
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

// 01BFS(コストが0or1なら使える)
vector<unordered_map<ll, ll>> bfs01(vvpll &nodes, int src, int goal=-1) {

    int N = nodes.size();
    rep(i, N) {
        // 路線毎に探せるように路線cを前にしてソートしておく
        sort(ALL(nodes[i]));
    }
    vector<unordered_map<ll, ll>> res(N);
    deque<tuple<ll, ll, ll>> que;
    res[src][-1] = 0;
    que.pb({0, src, -1});

    while (!que.empty()) {
        auto [d, u, c] = que.front(); que.pop_front();
        if (u == goal and c == -1) return res;
        if (res[u][c] < d) continue;
        if (c != -1) {
            // 改札の外
            ll nxc = -1;
            ll nxd = res[u].count(nxc) ? res[u][nxc] : INF;
            if (nxd > d) {
                res[u][nxc] = d;
                que.push_front({d, u, nxc});
            }
            // 同じ路線
            ll i = bisect_left(nodes[u], {c, -MOD});
            while (i < nodes[u].size() and nodes[u][i].first == c) {
                auto [nxc, v] = nodes[u][i];
                ll nxd = res[v].count(nxc) ? res[v][nxc] : INF;
                if (nxd > d) {
                    res[v][nxc] = d;
                    que.push_front({d, v, nxc});
                }
                i++;
            }
        } else {
            // 違う路線
            for (auto [nxc, v] : nodes[u]) {
                if (c == nxc) continue;
                ll nxd = res[v].count(nxc) ? res[v][nxc] : INF;
                if (nxd > d) {
                    res[v][nxc] = d+1;
                    que.push_back({d+1, v, nxc});
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

    auto res = bfs01(nodes, 0, N-1);
    ll ans = res[N-1].count(-1) ? res[N-1][-1] : -1;
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
