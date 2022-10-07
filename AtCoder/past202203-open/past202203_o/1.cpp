/*
・終了後自力AC！
・二部グラフ判定、部分和DP
・色々やる。時間かかったけど結構好き。
　とりあえずmod 3にする。で辺1箇所考えると、1-2か0-0の形にしかできないのが分かるので、
　連結成分毎に二部グラフ判定して、二部グラフになればいいけどならなければ0-0の形でそこは確定。
　この時点で0が多すぎたらNG。残りはどちらにもできるので、
　0にする or 1,2半分ずつで1が多い or 1,2半分ずつで2が多い、
　の3通り遷移みたいな部分和DPをやる。
　i番目まで見て1がj個2がk個みたいな3乗DPでも、j,kの最大が3/1000くらいなので間に合う。
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
    UnionFind uf(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
        uf.merge(u, v);
    }

    vector<ll> need(3);
    rep(i, 1, N+1) {
        need[i%3]++;
    }
    vector<ll> C(N, -1);
    auto dfs = [&](auto&& f, ll u, ll c) -> bool {
        if (C[u] != -1) {
            return c == C[u];
        }
        C[u] = c;
        for (auto v : nodes[u]) {
            if (!f(f, v, 1-c)) {
                return false;
            }
        }
        return true;
    };
    ll must0 = 0;
    vector<ll> comp, done(N);
    rep(i, N) {
        ll ri = uf.find(i);
        if (not done[ri]) {
            done[ri] = 1;
            // 二部グラフか？
            if (dfs(dfs, i, 0)) {
                comp.eb(uf.size(i));
            } else {
                must0 += uf.size(i);
            }
        }
    }
    assert(sum(comp)+must0 == N);
    if (must0 > need[0]) {
        No();
        return;
    }

    ll L = comp.size();
    ll S1 = need[1];
    ll S2 = need[2];
    auto dp = listnd(L+1, S1+1, S2+1, 0);
    dp[0][0][0] = 1;
    rep(i, L) {
        rep(j, S1+1) {
            rep(k, S2+1) {
                if (!dp[i][j][k]) continue;
                // 全0にする
                dp[i+1][j][k] = 1;
                // 1,2半分ずつで1に多く割り振る
                if (j+ceil(comp[i], 2LL) <= S1 and k+comp[i]/2 <= S2) {
                    dp[i+1][j+ceil(comp[i], 2LL)][k+comp[i]/2] = 1;
                }
                // 1,2半分ずつで2に多く割り振る
                if (j+comp[i]/2 <= S1 and k+ceil(comp[i], 2LL) <= S2) {
                    dp[i+1][j+comp[i]/2][k+ceil(comp[i], 2LL)] = 1;
                }
            }
        }
    }
    if (dp[L][S1][S2]) {
        Yes();
    } else {
        No();
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
