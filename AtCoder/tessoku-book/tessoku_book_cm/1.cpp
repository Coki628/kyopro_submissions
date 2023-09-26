/*
・半分全列挙(制約が小さくて全列挙から作るやつ)
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
    vector<ll> A(N);
    cin >> A;

    vector<ll> A1, A2;
    rep(i, N / 2) {
        A1.eb(A[i]);
    }
    rep(i, N / 2, N) {
        A2.eb(A[i]);
    }
    ll N1 = A1.size(), N2 = A2.size();
    vector<ll> B1, B2;
    rep(bit, 1 << N1) {
        ll sm = 0;
        rep(i, N) {
            if (bit >> i & 1) {
                sm += A1[i];
            }
        }
        B1.eb(sm);
    }
    rep(bit, 1 << N2) {
        ll sm = 0;
        rep(i, N) {
            if (bit >> i & 1) {
                sm += A2[i];
            }
        }
        B2.eb(sm);
    }

    sort(ALL(B2));
    ll M1 = B1.size(), M2 = B2.size();
    rep(i, M1) {
        ll j = bisect_left(B2, K - B1[i]);
        if (j < M2 and B1[i] + B2[j] == K) {
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
