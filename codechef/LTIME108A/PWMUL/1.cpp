/*
・部分点1
・mod pの世界では多くてもp乗すれば絶対周期になるみたいな話があった気がしたので、
　p乗まで試して、埋まった値の中で最小、としたらうまくいった。
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

bool used[10000007];

void solve() {
    ll P, a, b;
    cin >> P >> a >> b;

    assert(P <= 10000000);

    ll cur = b;
    used[cur] = true;
    rep(i, P) {
        cur *= a;
        cur %= P;
        used[cur] = true;
    }

    rep(i, P) {
        if (used[i]) {
            print(i);
            break;
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
