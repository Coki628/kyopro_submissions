/*
・自力AC！
・全色で「色cを全部抜いてチェックして戻して」みたいなことした。
　でも一番大きいやつ常に使って他方を全探索でいいらしい。
　それだと最大が複数ある時どれ使うか問題が起きそうな気がして直感に反するんだけどな。
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
    ll N;
    cin >> N;
    vector<ll> F(N), S(N);
    rep(i, N) {
        cin >> F[i] >> S[i];
    }
    F--;

    vvl adj(N);
    rep(i, N) {
        adj[F[i]].eb(S[i]);
    }
    multiset<ll> se;
    rep(i, N) {
        se.insert(S[i]);
    }
    ll ans = -INF;
    rep(i, N) {
        sort(adj[i].rbegin(), adj[i].rend());
        if (adj[i].size() >= 2) {
            chmax(ans, adj[i][0] + adj[i][1] / 2);
        }
        for (auto s : adj[i]) {
            se.erase(se.find(s));
        }
        if (adj[i].size() >= 1 and se.size()) {
            chmax(ans, adj[i][0] + (*--se.end()));
        }
        for (auto s : adj[i]) {
            se.insert(s);
        }
    }
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
