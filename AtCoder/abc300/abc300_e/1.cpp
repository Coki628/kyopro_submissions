/*
・自力AC！
・自己ループのある確率DP、メモ化再帰
・自己ループあり期待値DPの確率DP版みたいの。やり方同じでいいか自信なかったけど合ってた…。
　期待値DPと同じ感じで「1回の遷移の総数/自己ループにならずに遷移する数」を掛けるとOK。
・通ったからいいけど、これそもそも自己ループの遷移分無視するだけでよかったらしい。。
　確かに最後に掛けるやつ約分して整理するとそうなるね。。
・あとメモ化忘れてTLE食らったのは反省。。分かってても先に書いとくべきだった。
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

    map<ll, mint> memo;
    auto rec = [&](auto &&f, ll a) -> mint {
        if (memo.count(a)) {
            return memo[a];
        }
        if (a == N) {
            return 1;
        } else if (a > N) {
            return 0;
        }
        mint prob = 0;
        rep(x, 2, 7) {
            prob += f(f, a * x) / 6;
        }
        prob *= (mint)6 / 5;
        memo[a] = prob;
        return prob;
    };
    mint ans = rec(rec, 1);
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
