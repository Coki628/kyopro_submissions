/*
・ランダムテスト用愚直解
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
#include "template.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;

    ll cnt = 0;
    rep(a, 1, N+1) {
        rep(b, 1, N+1) {
            ll cur = 0;
            rep(c, 1, N+1) {
                if (abs(a-b) < K and abs(b-c) < K and abs(c-a) < K) {
                    cur++;
                }
            }
            cnt += cur;
            debug(a);
            debug(b);
            debug(cur);
        }
    }
    // debug(cnt);
    ll ans = pow(N, 3) - cnt;
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
