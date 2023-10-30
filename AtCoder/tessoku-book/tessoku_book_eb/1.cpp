/*
・集合(setとlower_bound)
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
    ll Q;
    cin >> Q;
    Set<ll> se = {-INF, INF};
    rep(i, Q) {
        ll op, x;
        cin >> op >> x;
        if (op == 1) {
            se.insert(x);
        } else if (op == 2) {
            if (se.size() == 2) {
                print(-1);
            } else {
                auto itr = se.lower_bound(x);
                ll val1 = *itr;
                itr--;
                ll val2 = *itr;
                ll res = min(abs(val1 - x), abs(val2 - x));
                print(res);
            }
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
