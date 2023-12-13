/*
ライブラリ整備：差分列管理
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

#include "datastructure/DifferenceManager.hpp"

void solve() {
    ll N, D;
    cin >> N >> D;
    auto A = LIST(N);

    A.insert(A.begin(), 0);
    auto dm = get_difference_manager(A, [](ll a, ll b) { return a - b; });
    ll ans = 0;
    rep(i, 1, N + 1) {
        dm.erase(A[i]);
        // 1個抜いた状態で一番狭い場所(末尾要素の後ろ以外)
        ll mn1 = dm.min_diff() - 1;
        // 位置Dか今一番広い場所の中央どちらかにこの1個を詰めるとする
        ll mn2 = max(D - dm.max_val() - 1, ceil(dm.max_diff() - 1, 2LL) - 1);
        chmax(ans, min(mn1, mn2));
        dm.insert(A[i]);
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
