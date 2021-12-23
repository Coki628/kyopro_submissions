/*
・自力AC！
・なんか横*縦を4通りくらい試す。
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
    ll W, H;
    cin >> W >> H;
    vvl A(4);
    rep(i, 4) {
        ll k;
        cin >> k;
        A[i] = LIST(k);
        sort(ALL(A[i]));
    }

    ll ans = 0;
    chmax(ans, max(A[0].back()-A[0][0], A[1].back()-A[1][0])*H);
    chmax(ans, max(A[2].back()-A[2][0], A[3].back()-A[3][0])*W);
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
