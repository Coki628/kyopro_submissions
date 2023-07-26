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

void solve() {
    ll N, D;
    cin >> N >> D;
    vector<string> S(N);
    cin >> S;

    ll ans = 0;
    rep(l, D) {
        rep(r, l + 1, D + 1) {
            bool ok = true;
            rep(d, l, r) {
                rep(i, N) {
                    if (S[i][d] == 'x') {
                        ok = false;
                        break;
                    }
                }
                if (not ok) break;
            }
            if (ok) {
                chmax(ans, r - l);
            }
        }
    }
    print(ans);
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
