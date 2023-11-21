/*
・自力AC！
・隣接ペア、乗算、ペアの最大値
・正負ゼロで場合分けする、掛け算ペア定番のめんどいやつって感じ。
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
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    vector<ll> A1, A2;
    bool zero = false;
    rep(i, N) {
        if (A[i] > 0) {
            A1.eb(A[i]);
        } else if (A[i] < 0) {
            A2.eb(A[i]);
        } else {
            zero = true;
        }
    }
    sort(ALL(A1));
    sort(ALL(A2));
    ll ans = -INF;
    if (A1.size() >= 2) {
        chmax(ans, A1.back() * A1[A1.size() - 2]);
    }
    if (A2.size() >= 2) {
        chmax(ans, A2[0] * A2[1]);
    }
    if (zero) {
        chmax(ans, 0LL);
    }
    if (A1.size() >= 1 and A2.size() >= 1) {
        chmax(ans, A1[0] * A2.back());
    }
    print(ans);
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
