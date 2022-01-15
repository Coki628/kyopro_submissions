/*
・きっちり自力AC！
・それぞれのマスから四隅の一番遠い所を持っておく。
　この値が小さいマスから優先して潰していくと考える。
　なのでこれをソートすれば答え。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;

    vector<ll> V;
    rep(i, H) {
        rep(j, W) {
            ll d = max({i+j, i+W-j-1, H-i-1+j, H-i-1+W-j-1});
            V.eb(d);
        }
    }
    sort(ALL(V));
    print(V);
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
