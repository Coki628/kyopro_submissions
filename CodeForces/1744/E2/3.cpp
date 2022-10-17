/*
参考：https://twitter.com/kude_coder/status/1581694225783353344
・高速素因数分解、約数列挙
・くでさんのやり方より、素因数分解から任意に効率よく約数列挙できそうな方法をやっていたので、
　高速素因数分解ライブラリに組み込んだ。やり方は結構単純で、今ある約数に、
　次に追加する素因数を、個数分全通り追加するもの。
　なんかすごく爆発しそうな感じがするのに、これで10^18でも大丈夫っぽい。
　素因数の種類数が思った以上に少ないのは知ってたけど、
　素因数の個数にしてもそこまで多くはならないのかな。
・まあどっちみちこれを持っていたとしても、a以下で最大のbの倍数みたいなやつ、の所が
　できなかったんだから解けてないんだけどね…。
・ちなみに速度はめちゃ速くて、0.08秒くらい。
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

#include "numbers/FastPrimeFactorization.hpp"

void solve() {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;

    ll ab = a * b;
    for (auto divab : FastPrimeFactorization::divisors(ab)) {
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
