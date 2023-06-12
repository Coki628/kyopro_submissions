/*
・自力AC！
・ダイクストラの逆みたいな感じで、利得の大きい遷移から優先して進める。
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
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, M, K;
    cin >> N >> M >> K;
    vvi nodes(N);
    rep(i, M) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        nodes[a].eb(b);
        nodes[b].eb(a);
    }

    vector<ll> res(N, -INF);
    priority_queue<pair<ll, int>> que;
    rep(i, K) {
        ll p, h;
        cin >> p >> h;
        p--;
        res[p] = h;
        que.push({h, p});
    }
    while (que.size()) {
        auto [dist, u] = que.top();
        que.pop();
        if (res[u] > dist) continue;
        for (auto v : nodes[u]) {
            if (chmax(res[v], dist - 1)) {
                que.push({dist - 1, v});
            }
        }
    }
    vector<ll> ans;
    rep(i, N) {
        if (res[i] >= 0) {
            ans.eb(i);
        }
    }
    ans++;
    print(ans.size());
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
