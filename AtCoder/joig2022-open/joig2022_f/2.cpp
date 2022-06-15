/*
・これは盛大にTLE。
・並列二分探索(の出来損ない)
・いける気がしたけど全然いけてなかった。。
　一応珍しいもの使おうとしたので取っておこう…。
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
    ll N, M, Q, L;
    cin >> N >> M >> Q >> L;
    vvpll nodes(N);
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        nodes[u].eb(v, c);
        nodes[v].eb(u, c);
    }

    vector<ll> OK(N, L+1), NG(N, 0);
    while (1) {
        // 各クエリiを、現在のOK,NG位置に応じたmに配置していく
        map<ll, vector<ll>> mid;
        rep(i, N) {
            if (NG[i]+1 < OK[i]) {
                ll m = (OK[i]+NG[i]) / 2;
                mid[m].eb(i);
            }
        }
        if (mid.empty()) break;

        vector<defaultdict<ll, ll>> res(N, {-INF});
        priority_queue<array<ll, 3>, vector<array<ll, 3>>> que;
        for (auto& [m, li] : mid) {
            res[0][m] = m;
            que.push({m, 0, m});
        }
        while (que.size()) {
            auto [dist, u, m] = que.top(); que.pop();
            if (res[u][m] > dist) continue;
            for (auto [v, t] : nodes[u]) {
                ll nxdist = t == 1 ? dist - 1 : dist / 2;
                if (nxdist <= 0) continue;
                if (chmax(res[v][m], nxdist)) {
                    que.push({nxdist, v, m});
                }
            }
        }
        for (auto& [m, li] : mid) {
            for (auto i : li) {
                if (res[i][m] > 0) {
                    OK[i] = m;
                } else {
                    NG[i] = m;
                }
            }
        }
    }

    rep(i, Q) {
        ll t;
        cin >> t;
        t--;
        if (OK[t] > L) {
            print("Large");
        } else {
            print(OK[t]);
        }
    }
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
