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
    ll N, Q;
    cin >> N >> Q;
    vector<ll> P(N);
    cin >> P;

    auto dm = get_difference_manager(P, [](ll a, ll b) { return a - b; });
    ll ans = dm.size() >= 2 ? (dm.max_val() - dm.min_val()) - dm.max_diff() : 0;
    print(ans);
    rep(i, Q) {
        ll op, x;
        cin >> op >> x;
        if (op == 0) {
            dm.erase(x);
        } else {
            dm.insert(x);
        }
        ans = dm.size() >= 2 ? (dm.max_val() - dm.min_val()) - dm.max_diff() : 0;
        print(ans);
    }
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
