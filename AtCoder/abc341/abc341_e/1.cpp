/*
・きっちり自力AC！
・01列、区間フリップ、差分列
・「隣接が異なるかどうか」の差分列で状態を持てば、
　2点更新と区間和取得で、題意のものを取得できる。
　この手の差分列とか累積和列をセグ木に乗せる系は、
　添字がズレるのを調整するのに今までもたつきがちだったけど、
　今回は結構落ち着いて処理できたと思う。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;

    BIT<ll> bit(N - 1);
    rep(i, N - 1) {
        if (S[i] == S[i + 1]) {
            bit.add(i, 1);
        }
    }
    rep(_, Q) {
        ll op, l, r;
        cin >> op >> l >> r;
        l--;
        if (op == 1) {
            if (l > 0) {
                bit.update(l - 1, 1 - bit[l - 1]);
            }
            if (r < N) {
                bit.update(r - 1, 1 - bit[r - 1]);
            }
        } else {
            YesNo(bit.query(l, r - 1) == 0);
        }
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
