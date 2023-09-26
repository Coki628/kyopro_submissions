/*
・半分全列挙(制約が小さくなくて全ペアから作るやつ)
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N), B(N), C(N), D(N);
    cin >> A >> B >> C >> D;

    vector<ll> AB, CD;
    rep(i, N) {
        rep(j, N) {
            AB.eb(A[i] + B[j]);
            CD.eb(C[i] + D[j]);
        }
    }
    sort(ALL(CD));
    ll M = N * N;
    rep(i, M) {
        ll j = bisect_left(CD, K - AB[i]);
        if (j < M and AB[i] + CD[j] == K) {
            Yes();
            return;
        }
    }
    No();
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
