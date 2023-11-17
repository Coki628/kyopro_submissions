/*
・きっちり自力AC！
・両方ソートすれば差分は最小限に抑えられるはずなので大丈夫(だと信じる)。
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
    vector<ll> A(N), B(N);
    cin >> A >> B;

    vector<pll> AI;
    rep(i, N) {
        AI.eb(A[i], i);
    }
    sort(ALL(AI));
    sort(ALL(B));

    vector<array<ll, 3>> vec;
    rep(i, N) {
        vec.pb({AI[i].second, AI[i].first, B[i]});
    }
    sort(ALL(vec));
    vector<ll> ans(N);
    rep(i, N) {
        ans[i] = vec[i][2];
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
