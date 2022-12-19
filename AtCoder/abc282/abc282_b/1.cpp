/*
・制約小さいのでどうにでもなりそうだが、
　ビットにエンコードしてOR演算してpopcountした。
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
    ll N , M;
    cin >> N >> M;
    vector<string> mat(N);
    cin >> mat;

    vector<ll> A(N);
    rep(i, N) {
        rep(j, M) {
            if (mat[i][j] == 'o') {
                A[i] |= 1LL << j;
            }
        }
    }
    ll ans = 0;
    rep(i, N) {
        rep(j, i+1, N) {
            ll res = A[i] | A[j];
            if (popcount(res) == M) {
                ans++;
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
