/*
・きっちり自力AC！
・どちらにせよ最大値は使いたいので、最大値を単体で使うか、
　絶対値を稼ぐ方に使うかを両方試す。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    sort(ALL(A));
    ll ans = max((A[N-1]-A[0])*A[N-2], (A[N-2]-A[0])*A[N-1]);
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
