/*
・きっちり自力AC！
・素因数分解、LCM、素数冪
・これはほぼ迷わず正解の方針を引けた。当時解けなかったらしいので嬉しい。
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

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    map<ll, int> mp;
    rep(i, N) {
        for (auto [k, v] : factorize(A[i])) {
            chmax(mp[k], v);
        }
    }
    mint total = 1;
    for (auto [k, v] : mp) {
        total *= pow(k, v, MOD);
    }
    mint ans = 0;
    rep(i, N) {
        mint cur = 1;
        for (auto [k, v] : factorize(A[i])) {
            cur *= pow(k, v, MOD);
        }
        ans += total / cur;
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
