/*
・みんなやってた方針。それはそうよね、、なぜ気付かなかった…。
・2次元累積和
・なんかね、2次元累積和想定の問題いっつも気付かなくて非想定で殴るよね。
　なんか存在忘れてて平面走査とかそっち方面に行っちゃうんだよな…。
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

#include "datastructure/Accumulate2D.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    ll M = 1000;
    Accumulate2D<ll> acc(M + 1, M + 1);
    rep(i, N) {
        ll h, w;
        cin >> h >> w;
        acc.add(h, w, h * w);
    }
    acc.build();

    rep(i, Q) {
        ll hs, ws, hb, wb;
        cin >> hs >> ws >> hb >> wb;
        ll res = acc.query(hs + 1, ws + 1, hb, wb);
        print(res);
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
