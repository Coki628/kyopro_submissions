/*
・区間最大値取得、セグ木
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
    ll N, Q;
    cin >> N >> Q;

    auto seg = get_segment_tree(vector<ll>(N), [](ll a, ll b) { return max(a, b); }, -INF);
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll j, x;
            cin >> j >>  x;
            j--;
            seg.update(j, x);
        } else {
            ll l, r;
            cin >> l >> r;
            l--, r--;
            print(seg.query(l, r));
        }
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
