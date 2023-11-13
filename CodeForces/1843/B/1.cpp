/*
・きっちり自力AC！
・符号が切り替わるところをうまく数える。
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

    vector<ll> B;
    rep(i, N) {
        if (A[i] != 0) {
            B.eb(A[i]);
        }
    }
    if (B.empty()) {
        print(mkp(0, 0));
        return;
    }
    ll M = B.size();
    bool plus = B[0] > 0;
    ll cnt = !plus;
    ll sm = abs(B[0]);
    rep(i, 1, M) {
        sm += abs(B[i]);
        if (plus and B[i] < 0) {
            cnt++;
            plus = false;
        } else if (not plus and B[i] > 0) {
            plus = true;
        }
    }
    print(mkp(sm, cnt));
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
