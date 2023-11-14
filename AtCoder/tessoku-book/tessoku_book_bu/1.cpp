/*
・きっちり自力AC！
・ダイクストラ
・2番目の情報も持って、やる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vvpil nodes(N);
    vector<ll> C(M), D(M);
    rep(i, M) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        a--, b--;
        nodes[a].eb(b, i);
        nodes[b].eb(a, i);
        C[i] = c;
        D[i] = d;
    }

    auto dijkstra = [&](const vvpil &nodes, const vector<int> &src, int goal = -1) {
        int N = nodes.size();
        vector<array<ll, 2>> res(N, {numeric_limits<ll>::max() / 2, 0});
        priority_queue<pair<array<ll, 2>, int>, vector<pair<array<ll, 2>, int>>, greater<pair<array<ll, 2>, int>>> que;
        for (auto s : src) {
            res[s] = {0, 0};
            que.push({{0, 0}, s});
        }

        while (que.size()) {
            auto [dist, u] = que.top();
            auto [c, d] = dist;
            que.pop();
            if (u == goal) return res;
            if (res[u] < dist) continue;
            for (auto [v, e] : nodes[u]) {
                ll nxc = C[e];
                ll nxd = D[e];
                if (chmin(res[v], {c + nxc, d - nxd})) {
                    que.push({{c + nxc, d - nxd}, v});
                }
            }
        }
        return res;
    };
    auto res = dijkstra(nodes, {0});
    auto [c, d] = res[N - 1];
    print(mkp(c, -d));
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
