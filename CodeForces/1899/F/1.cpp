/*
・自力AC！
・グラフ、構築
・最初に一直線グラフを作っておいて、クエリで欲しい深さに合わせて、
　先っぽを外して付け替えてみたいにやるとうまくいく。
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
    ll N, Q;
    cin >> N >> Q;
    vector<pii> edges;
    rep(i, N - 1) {
        edges.eb(i + 1, i + 2);
    }
    print(edges, '\n');

    ll cur = N - 1;
    rep(i, Q) {
        ll d;
        cin >> d;
        if (d == cur) {
            print(array<ll, 3>{-1, -1, -1});
        } else {
            ll u = N - 1;
            ll v1 = cur - 1;
            ll v2 = d - 1;
            print(array<ll, 3>{u + 1, v1 + 1, v2 + 1});
            cur = d;
        }
    }
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
