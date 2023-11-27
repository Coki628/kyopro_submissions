/*
・自力AC！
・にぶたん
・xを固定して、yをにぶたんした。
　lower_boundっぽくD以上になる最小値を求めた後、
　1つ手前があればそれもチェック、とした。
・これCでやらすの結構大変くない？って思いながら通したけど、
　後でTLとか見てたら、式変形してsqrtのが有力だったぽい。
　x固定した後、x^2+y^2=Dになるべく近づけるとして、
　式変形でy^2=D-x^2とすれば、y=sqrt(d)-xのsqrtにfloorとceil両方試すのが最善、
　のようにできる。
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
    ll D;
    cin >> D;

    ll M = 2000000;
    ll ans = INF;
    rep(x, M + 1) {
        ll y = bisearch_min(-1, MOD, [&](ll y) {
            return x * x + y * y >= D;
        });
        if (y > 0) {
            ll res = abs(x * x + (y - 1) * (y - 1) - D);
            chmin(ans, res);
        }
        ll res = abs(x * x + y * y - D);
        chmin(ans, res);
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
