/*
・自力AC！
・ペア数え上げ、乗算、式変形、左端を覚えて右端で貰うテク、0の場合分け
・a*b=P => a=P/b と式変形すれば、ペアの一方から他方が求まる。
　あとは左端をmapに詰めて右端で条件に合う左端がいくつあるか数えるいつもの。
　なんだけど、乗算除算なので0のケースを場合分ける必要がある。
　基本的には0が絡めば何やっても0なので、0の個数から2つ選ぶのと、
　0側とその他側から1個ずつ選ぶのを両方数えれば0のケースはOK。
　関連させる必要もないので、実装上は最初から配列を完全に分けて処理した。
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
    mint P;
    cin >> N >> P;
    vector<mint> A(N);
    cin >> A;

    vector<mint> A2;
    ll zero = 0;
    rep(i, N) {
        if (A[i] == 0) {
            zero++;
        } else {
            A2.eb(A[i]);
        }
    }
    ll N2 = A2.size();

    if (P == 0) {
        ll ans = nC2(zero) + zero * N2;
        print(ans);
    } else {
        ll ans = 0;
        map<mint, ll> mp;
        rep(i, N2) {
            mint b = A2[i];
            mint a = P / b;
            if (mp.count(a)) {
                ans += mp[a];
            }
            mp[b]++;
        }
        print(ans);
    }
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
