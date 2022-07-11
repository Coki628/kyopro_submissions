/*
・ライブラリ整備：幾何、2円の交差判定
・C++版、ちゃんと作った。2乗のまま整数で判定できるようにしてある。
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

#include "geometry/Circle.hpp"
#include "geometry/intersectCC.hpp"

void solve() {
    ll N;
    cin >> N;
    ll sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;

    auto check = [&](Circle<ll> c1, Circle<ll> c2) {
        auto res = intersectCC(c1, c2);
        // 内包か離れていたらダメ(接していない)
        if (res == 1 or res == 5) {
            return false;
        } else {
            return true;
        }
    };

    vector<Circle<ll>> C(N);
    rep(i, N) {
        ll x, y, r;
        cin >> x >> y >> r;
        C[i] = {{x, y}, r};
    }
    UnionFind uf(N+2);
    rep(i, N) {
        rep(j, i+1, N) {
            if (check(C[i], C[j])) {
                uf.merge(i, j);
            }
        }
    }
    rep(i, N) {
        if (check(C[i], Circle<ll>{{sx, sy}, 0})) {
            uf.merge(i, N);
        }
        if (check(C[i], Circle<ll>{{tx, ty}, 0})) {
            uf.merge(i, N+1);
        }
    }
    if (uf.same(N, N+1)) {
        Yes();
    } else {
        No();
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
