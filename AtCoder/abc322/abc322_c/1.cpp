/*
・きっちり自力AC！
・後ろから累積和っぽくする。
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
    vector<ll> A(M);
    cin >> A;
    A--;

    vector<ll> B(N);
    rep(i, M) {
        B[A[i]] = 1;
    }
    vector<ll> nxt(N);
    ll cur = INF;
    rep(i, N - 1, -1, -1) {
        if (B[i]) {
            cur = i;
        }
        nxt[i] = cur;
    }
    rep(i, N) {
        print(nxt[i] - i);
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
