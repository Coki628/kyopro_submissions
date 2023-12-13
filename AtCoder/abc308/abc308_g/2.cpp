/*
ライブラリ整備：差分列管理
・抽象化してXORでも試してみる。問題なくAC。しかも実装が超簡潔。
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
    auto dm = get_difference_manager(vector<ll>{}, [](ll a, ll b) { return a ^ b; });
    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x;
            cin >> x;
            dm.insert(x);
        } else if (op == 2) {
            ll x;
            cin >> x;
            dm.erase(x);
        } else if (op == 3) {
            ll res = dm.min_diff();
            print(res);
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
