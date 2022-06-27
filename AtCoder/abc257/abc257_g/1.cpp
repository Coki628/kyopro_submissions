/*
・ほとんどキーワード聞いただけでAC。
・ロリハ、区間chmin
・E,F,Gでこれが一番目があったんじゃないかな。ちゃんとここまで見ればよかった…。
・「Tのi文字目までやった最小コスト」みたいなDPで考える。
　遷移を伸ばせる長さはロリハのLCPで分かる。配るDPで区間chminする感じにできればいいので、
　これは1点取得なのでBeatsじゃなくても普通の遅延セグ木に乗る。(これ最近知った知見)
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

#include "string/RollingHash.hpp"
#include "segment/LazySegmentTree.hpp"

// 区間chmin・1点取得
auto f = [](ll a, ll b) -> ll { return min(a, b); };
auto g = [](ll a, ll b) -> ll { return min(a, b); };
auto h = [](ll a, ll b) -> ll { return min(a, b); };
const ll T = INF;
const ll E = INF;

void solve() {
    string S, U;
    cin >> S >> U;
    ll N = S.size();
    ll M = U.size();

    RollingHash rh;
    auto stable = rh.build(S);
    auto utable = rh.build(U);

    auto dp = get_lazy_segment_tree(M+1, f, g, h, T, E);
    dp.set(0, 0);
    dp.build();
    rep(i, M) {
        ll len = rh.lcp(stable, 0, N, utable, i, M);
        dp.update(i, i+len+1, dp[i]+1);
        // dp.print(M+1);
    }
    ll ans = dp[M];
    if (ans >= INF) ans = -1;
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
