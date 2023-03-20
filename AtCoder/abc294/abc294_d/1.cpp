/*
・自力AC！
・キューとかsetで持ってシミュる。
　呼ばれた順序も合わせて持っちゃったけど、
　最初に呼ばれるのは番号順なのでそこが前後することってなくて、
　持つ意味なかったね…。
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
    ll N, Q;
    cin >> N >> Q;

    deque<ll> que;
    rep(i, N) {
        que.pb(i);
    }
    ll cur = 0;
    vector<ll> order(N, -1);
    set<pll> se;
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            assert(que.size());
            ll i = que.front();
            que.pop_front();
            se.insert({cur, i});
            order[i] = cur;
            cur++;
        } else if (op == 2) {
            ll x;
            cin >> x;
            x--;
            se.erase({order[x], x});
        } else {
            ll i = se.begin()->second;
            print(i + 1);
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
