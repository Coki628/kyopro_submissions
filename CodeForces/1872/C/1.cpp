/*
・なんとか自力AC。本日のボトルネック…。
・実験エスパー、素数、約数列挙
・2とかなるべく小さい数をうまく使えばだいたいうまくいきそう。
　と、しばらくガチャガチャやってたけどどん詰まり。
　気持ちを切り替えて実験すると、a+bが素数だと無理そうということ、
　素数じゃなければ片側を(自身と1以外の)約数にするといけそうということが見えた。
・結局、なんとか考えて解けないかって粘るのがだいたい悪手なんだよな。
　割り切ってさっさと実験コード書けば結構見えてくることはある。
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
    ll l, r;
    cin >> l >> r;

    // rep(ab, l, r + 1) {
    //     if (ab <= 1) continue;
    //     debug(ab);
    //     rep(a, 1, ab) {
    //         ll b = ab - a;
    //         if (a > b) break;
    //         if (gcd(a, b) != 1) {
    //             print(mkp(a, b));
    //         }
    //     }
    // }
    // - a+bが素数だと無理そう
    // - 素数じゃなければ、片側を約数にするといけそう？

    // 素数じゃないのが当たるまでにまあ10もあれば十分なはず
    rep(ab, l, min(l + 10, r + 1)) {
        for (auto a : divisors(ab)) {
            if (a != 1 and a != ab) {
                ll b = ab - a;
                print(mkp(a, b));
                return;
            }
        }
    }
    print(-1);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
