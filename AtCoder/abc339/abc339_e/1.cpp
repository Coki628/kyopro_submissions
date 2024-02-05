/*
・きっちり自力AC！
・in-place DP
・直前に使った場所を覚えておくDPをin-placeにするやつ。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N, D;
    cin >> N >> D;
    vector<ll> A(N);
    cin >> A;

    ll M = max(A);
    auto seg = get_segment_tree(vector<ll>(M + 1), [](ll a, ll b) { return max(a, b); }, -INF);
    rep(i, N) {
        ll l = max(A[i] - D, 0LL);
        ll r = min(A[i] + D, M) + 1;
        seg.update(A[i], seg.query(l, r) + 1);
    }
    ll ans = seg.all();
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
