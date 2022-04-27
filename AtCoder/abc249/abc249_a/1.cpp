/*
・周期で見て頑張る。ループ回せるからまだいいけど、
　それでもこのレベル感をAに置くのは酷なのではって感じも。
・6問ABC以降最難のAになったそう。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    ll a, b, c, d, e, f, x;
    cin >> a >> b >> c >> d >> e >> f >> x;

    ll taka = 0, aoki = 0;
    ll ac = a + c;
    ll df = d + f;
    rep(i, x) {
        ll aci = i % ac;
        if (aci < a) {
            taka += b;
        }
        ll dfi = i % df;
        if (dfi < d) {
            aoki += e;
        }
    }
    if (taka > aoki) {
        print("Takahashi");
    } elif (taka < aoki) {
        print("Aoki");
    } else {
        print("Draw");
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
