/*
・きっちり自力AC！
・最初の0より前と最後の1より後は大丈夫。それらを除いた数を数える。
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
    string S;
    cin >> S;
    ll N = S.size();

    vector<ll> ok(N);
    ll i = S.find('0');
    if (i != -1) {
        rep(j, i+1, N) {
            ok[j] = 1;
        }
    }
    i = S.rfind('1');
    if (i != -1) {
        rep(j, i) {
            ok[j] = 1;
        }
    }
    ll ans = count(ALL(ok), 0);
    print(ans);
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
