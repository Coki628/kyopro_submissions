/*
・きっちり自力AC。
・Xがある程度大きくなるまでやる。
　部分列チェックは愚直に試してOK。
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

void solve() {
    ll N, M;
    cin >> N >> M;
    string X, S;
    cin >> X >> S;

    ll cnt = 0;
    while (X.size() <= 100) {
        if (X.size() >= S.size()) {
            rep(i, X.size() - M + 1) {
                ll j = i + M;
                if (X.substr(i, j - i) == S) {
                    print(cnt);
                    return;
                }
            }
        }
        X += X;
        cnt++;
    }
    print(-1);
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
