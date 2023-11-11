/*
・自力AC！
・愚直にシミュして前計算で全部列挙しておけばOK。
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

ll M = 1000000;
vector<ll> exists(M + 1);
void prep() {
    rep(k, 2, M + 1) {
        ll cur = 1, kk = 1, i = 0;
        while (cur + kk * k <= M) {
            kk *= k;
            cur += kk;
            if (i >= 1) {
                exists[cur] = true;
            }
            i++;
        }
    }
}

void solve() {
    ll N;
    cin >> N;

    print(exists[N] ? "YES" : "NO");
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    prep();

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
