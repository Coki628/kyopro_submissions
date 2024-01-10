/*
・きっちり自力AC！
・拡張ダイクストラ
・2乗効く制約なので、今持ってる自転車を状態に持てる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        nodes[u].eb(v, c);
        nodes[v].eb(u, c);
    }
    vector<ll> A(N);
    cin >> A;
    ll L = max(A);

    auto dijkstra = [&](const vvpil &nodes, const vector<int> &src) {
        int N = nodes.size();
        auto res = listnd(N, L + 1, INF);
        priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<array<ll, 3>>> que;
        for (auto s : src) {
            res[s][A[s]] = 0;
            que.push({0, s, A[s]});
        }
        while (que.size()) {
            auto [dist, u, a] = que.top();
            que.pop();
            if (res[u][a] < dist) continue;
            for (auto [v, c] : nodes[u]) {
                ll nxa = min(a, A[v]);
                ll cost = c * a;
                if (chmin(res[v][nxa], dist + cost)) {
                    que.push({dist + cost, v, nxa});
                }
            }
        }
        return res;
    };
    auto res = dijkstra(nodes, {0});
    ll ans = min(res[N - 1]);
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
