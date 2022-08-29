/*
・自力ならず。。
・期待値DP
・いやー、誤読がつらい。継続する場合はスコアが累積するのかと思ったら、
　継続しても前回以前の出目関係ないのね…。
　そうと分かれば解けたかもしれないけど、まあそんなこと言ってもしょうがない。
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

    vector<ld> memo(N, -1);
    auto rec = [&](auto&& f, ll i) -> ld {
        if (i == N) {
            return 0;
        }
        if (memo[i] != -1) {
            return memo[i];
        }
        ld res = 0;
        rep(x, 1, 7) {
            // max(このまま続ける, 今回のxで終了する) * そうなる確率
            res += max(f(f, i+1), (ld)x) / 6;
        }
        memo[i] = res;
        return res;
    };
    ld res = rec(rec, 0);
    print(res);
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
