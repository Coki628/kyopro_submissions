/*
参考：https://twitter.com/AllDirections4/status/1581690113482194944
・自力ならず…。
・約数列挙
・aの約数*bの約数=abの約数、の形でabの約数が全列挙できるようだ。
　言われると確かにそんな気もするけど、自分じゃ考えつかなかったな。。
　まあそれができても、a以下で最大のbの倍数みたいなやつ、
　割り算で求めるのも出なかったんだけどね…。(この割って掛ける形はすごく見覚えあるのに)
・これだとTLギリギリで、AC3.70秒。(制約4秒)
　でもなんか結構枝刈りできそうな気がするから、それで速くなるのかも。
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
    ll a, b, c, d;
    cin >> a >> b >> c >> d;

    ll ab = a * b;
    for (auto diva : divisors(a)) {
        for (auto divb : divisors(b)) {
            ll divab = diva * divb;
            assert(ab%divab == 0);
            ll revab = ab / divab;
            // c以下で最大のdivabの倍数
            ll x = c / divab * divab;
            // d以下で最大のrevabの倍数
            ll y = d / revab * revab;
            if (a < x and x <= c and b < y and y <= d) {
                print(mkp(x, y));
                return;
            }
        }
    }
    print(mkp(-1, -1));
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
