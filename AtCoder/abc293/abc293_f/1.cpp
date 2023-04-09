/*
・実験用。これでNとN-1が必須なのは分かったけど、
　約数なのは見えなかったなー。見えるべきだった。
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

#include "numbers/dton.hpp"

void solve() {
    rep(N, 2, 100) {
        // ll N;
        // cin >> N;
        debug(N);
        ll ans = 0;
        rep(b, 2, N + 1) {
            auto res = dton(N, b);
            auto tmp = res;
            UNIQUE(tmp);
            if (tmp == "01" or tmp == "0" or tmp == "1") {
                // debug(b);
                cout << "b: " << b << " res: " << res << endl;
                ans++;
            }
        }
        cout << "N: " << N << " ans: " << ans << endl;
        cout << endl;
        // print(ans);
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
