/*
・自力AC！
・前後からDP
・後ろからやる方の添字が合ってるか分からなくて困った。まあ通ったからいいけど。。
　多分、半開区間の逆？(l,r]みたいにするといいんだと思う。
・ちなみにこれ、公式解説だと前後から前計算するのは同じなんだけど、
　DPじゃなくて区間スケジューリングでやってた。
　つまりこのDPが通ったってことは、区間スケジューリングはDPでも解けるってことだな。
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
    ll N, K;
    cin >> N >> K;
    ll M = 86400 + K;
    vvl adj1(M + 1), adj2(M + 1);
    vector<pll> LR;
    rep(i, N) {
        ll l, r;
        cin >> l >> r;
        adj1[l].eb(r + K);
        adj2[r + K].eb(l);
        LR.eb(l, r + K);
    }

    vector<ll> dp1(M + 1, -INF), dp2(M + 1, -INF);
    dp1[0] = 0;
    rep(i, M) {
        chmax(dp1[i + 1], dp1[i]);
        for (auto r : adj1[i]) {
            chmax(dp1[r], dp1[i] + 1);
        }
    }
    dp2[M] = 0;
    rep(i, M, 0, -1) {
        chmax(dp2[i - 1], dp2[i]);
        for (auto l : adj2[i]) {
            chmax(dp2[l], dp2[i] + 1);
        }
    }

    vector<ll> ans(N);
    rep(i, N) {
        auto [l, r] = LR[i];
        ans[i] = dp1[l] + dp2[r] + 1;
    }
    print(ans, '\n');
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
