/*
・フロー、最大流、燃やす埋める
・前にメモにしっかりまとめていたのが役に立った。
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

#include "acl/maxflow.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> P(N);
    cin >> P;
    atcoder::mf_graph<ll> mf(N + 2);
    ll s = N, t = N + 1;
    ll ans = 0;
    rep(i, N) {
        ll a = 0;
        ll b = P[i];
        ll mx = max(a, b);
        // この駅を選ばない
        mf.add_edge(s, i, mx - a);
        // この駅を選ぶ
        mf.add_edge(i, t, mx - b);
        ans += mx;
    }
    rep(i, M) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        // 駅aを選ぶなら駅bも選ぶ
        // (駅aを選んで駅bを選ばなかった時のコストがINFになる)
        mf.add_edge(a, b, INF);
    }
    ans -= mf.flow(s, t);
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
