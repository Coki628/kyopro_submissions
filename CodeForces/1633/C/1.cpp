/*
・きっちり自力AC！
・Kが丁度いい大きさ。攻撃防御どっちに割り振るか全探索。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    ll hc, dc, hm, dm;
    cin >> hc >> dc;
    cin >> hm >> dm;
    ll K, w, a;
    cin >> K >> w >> a;

    rep(i, K+1) {
        ll j = K-i;
        ll hcur = hc+a*i;
        ll dcur = dc+w*j;
        ll needc = ceil(hm, dcur);
        ll needm = ceil(hcur, dm);
        if (needc <= needm) {
            YES();
            return;
        }
    }
    NO();
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
