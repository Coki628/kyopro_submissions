/*
・自力AC！
・制約2乗OKなので、BFSをK回を2回。
　全クエリについてd-1まで白塗りしてから、距離dに黒があるかチェック。
・最初、同時にやってしまって、後から白塗りされるのを考慮できてなかったので1WA。。
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
    ll N, M;
    cin >> N >> M;
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    ll K;
    cin >> K;
    vector<pll> qs;
    rep(i, K) {
        ll p, d;
        cin >> p >> d;
        p--;
        qs.eb(p, d);
    }

    string ans(N, '1');
    for (auto [p, d] : qs) {
        vector<ll> dist(N, INF);
        deque<ll> que;
        que.pb(p);
        dist[p] = 0;
        while (que.size()) {
            auto u = que.front();
            que.pop_front();
            if (dist[u] < d) {
                ans[u] = '0';
                for (auto v : nodes[u]) {
                    if (dist[v] == INF) {
                        que.pb(v);
                        dist[v] = dist[u] + 1;
                    }
                }
            }
        }
    }

    for (auto [p, d] : qs) {
        vector<ll> dist(N, INF);
        deque<ll> que;
        que.pb(p);
        dist[p] = 0;
        bool ok = false;
        while (que.size()) {
            auto u = que.front();
            que.pop_front();
            if (dist[u] == d) {
                if (ans[u] == '1') {
                    ok = true;
                }
            } else if (dist[u] < d) {
                for (auto v : nodes[u]) {
                    if (dist[v] == INF) {
                        que.pb(v);
                        dist[v] = dist[u] + 1;
                    }
                }
            }
        }
        if (not ok) {
            No();
            return;
        }
    }
    Yes();
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
