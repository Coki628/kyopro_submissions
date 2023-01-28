/*
・なんとか自力AC！
・XORの時に打ち消される部分、みたいなのがどのくらいか知りたくて、
　これはa,bに同じ値だけ入ってないといけなくて、
　結局Xを半分にしたやつが欲しい。これをYとする。
　Yは打ち消し合うとして、残るX部分は適当に2つに分けてそれぞれをa,bにする。
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
    ll x;
    cin >> x;

    if (x % 2 == 1) {
        print(-1);
        return;
    }
    // xの半分
    ll y = x / 2;
    // 被るビットがあったらダメ
    if (x + y != (x | y)) {
        print(-1);
        return;
    }
    rep(k, 40) {
        if (x >> k & 1) {
            // 適当に分ける
            ll a = 1LL << k;
            ll b = x ^ a;
            // 両方にyを追加(xor時には消える)
            a |= y;
            b |= y;
            print(mkp(a, b));
            return;
        }
    }
    assert(0);
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
