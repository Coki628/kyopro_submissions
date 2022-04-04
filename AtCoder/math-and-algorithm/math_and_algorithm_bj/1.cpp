/*
・きっちり自力AC！
・XY独立、絶対値ペアはソート、累積和
・マンハッタン距離で、XYは独立に考えていい。
　絶対値で順序が変わっても答えに影響しないので、ソートする。
　これである左端に対する右端を、累積和でまとめて計算できる。
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
    ll N;
    cin >> N;
    vector<ll> X(N), Y(N);
    rep(i, N) {
        cin >> X[i] >> Y[i];
    }

    sort(ALL(X));
    sort(ALL(Y));
    Accumulate<ll> accx(X), accy(Y);
    ll ans = 0;
    rep(i, N) {
        ans += accx.query(i+1, N) - X[i]*(N-i-1);
        ans += accy.query(i+1, N) - Y[i]*(N-i-1);
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
