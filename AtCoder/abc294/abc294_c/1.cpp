/*
・きっちり自力AC！
・イベントソート
・indexと一緒にABどっちだったかも持たせて1つの配列にしてソート。
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
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N), B(M);
    cin >> A >> B;

    vector<array<ll, 3>> events;
    rep(i, N) {
        events.pb({A[i], 0, i});
    }
    rep(i, M) {
        events.pb({B[i], 1, i});
    }
    sort(ALL(events));

    vvi ans(2);
    ans[0].resize(N);
    ans[1].resize(M);
    ll k = 1;
    for (auto [_, i, j] : events) {
        ans[i][j] = k;
        k++;
    }
    print(ans, '\n');
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
