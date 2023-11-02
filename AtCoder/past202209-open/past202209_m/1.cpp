/*
・きっちり自力AC！
・貰うDPをセグ木で遷移高速化
・これは後半の割に易しく思えたやつ。(事実、人々もかなり解いていた。)
　遷移が区間になるDPなので、セグ木で取得を高速化するといい。
　配るDPだと区間chminだけど貰うDPなら区間min取得なので普通のセグ木でOK。
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
    vector<ll> A(N);
    cin >> A;
    vvpll adj(N);
    rep(i, M) {
        ll b, l, r;
        cin >> b >> l >> r;
        l--, r--;
        adj[r].eb(l, b);
    }

    auto dp = get_segment_tree(N + 1, [](ll a, ll b) { return min(a, b); }, INF);
    dp.update(0, 0);
    rep(i, N) {
        dp.update(i + 1, min(dp[i + 1], dp[i] + A[i]));
        for (auto [l, b] : adj[i]) {
            dp.update(i + 1, min(dp[i + 1], dp.query(l, i + 1) + b));
        }
    }
    ll ans = dp[N];
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
