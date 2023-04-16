/*
・きっちり自力AC！
・文字列をdequeとかで持ちつつ、その時の桁数(dequeサイズ)に応じた10冪を掛けて計算。
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

    deque<ll> que = {1};
    mint ans = 1;
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x;
            cin >> x;
            que.pb(x);
            ans = ans * 10 + x;
        } else if (op == 2) {
            mint d = que.front();
            que.pop_front();
            mint sub = d * mint(10).pow(que.size());
            ans -= sub;
        } else if (op == 3) {
            print(ans);
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
