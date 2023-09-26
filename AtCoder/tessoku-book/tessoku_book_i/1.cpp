/*
・2次元いもす
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

#include "datastructure/Imos2D.hpp"

void solve() {
    ll H, W, N;
    cin >> H >> W >> N;
    Imos2D<ll> imos(H, W);
    rep(i, N) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        a--, b--;
        imos.add(a, b, c, d, 1);
    }
    imos.build();

    rep(h, H) {
        rep(w, W) {
            cout << imos.get(h, w);
            if (w == W - 1) {
                cout << '\n';
            } else {
                cout << ' ';
            }
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
