/*
・迷走した末に最初にAC取ったやつ、一応残しておくか。。
・難しいソートしてDP、式変形
・edpc_xとかpast202104_nみたいに、2要素に注目して式作って、
　逆順にした場合と比較するみたいなソートをする。
　cur+Ti<=Di and cur+Ti+Tj<=Dj とその逆を作る。
　cur<=min(Di-Ti, Dj-Ti-Tj) となって、これの降順にすると通る。
　降順なのがいまいちピンと来ないんだけど、
　多分現在時刻curが多めに残る方を優先しようねみたいな気持ちだと思っておく。
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
    ll N;
    cin >> N;
    vector<pll> DT;
    rep(i, N) {
        ll t, d;
        cin >> t >> d;
        DT.eb(d, t);
    }

    sort(ALL(DT), [](pll a, pll b) {
        return min(a.first - a.second, b.first - a.second - b.second) > min(b.first - b.second, a.first - b.second - a.second);
    });
    ll M = 1440 * 2;
    auto dp = listnd(N + 1, M + 1, -INF);
    dp[0][0] = 0;
    rep(i, N) {
        auto [d, t] = DT[i];
        rep(j, M + 1) {
            chmax(dp[i + 1][j], dp[i][j]);
            if (j + t <= d) {
                chmax(dp[i + 1][j + t], dp[i][j] + 1);
            }
        }
    }
    ll ans = 0;
    rep(j, M + 1) {
        chmax(ans, dp[N][j]);
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
