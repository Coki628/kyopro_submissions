/*
ライブラリ整備：抽象化BIT
・更新ありロリハの絡みで作ったので、一応単体でXORのverifyもしておく。
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

#include "datastructure/AbstractBIT.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    cin >> A;

    auto f = [](ll a, ll b) { return a ^ b; };
    AbstractBIT<ll, decltype(f), decltype(f)> bit(A, f, f);
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x, y;
            cin >> x >> y;
            x--;
            bit.add(x, y);
        } else {
            ll x, y;
            cin >> x >> y;
            x--;
            ll res = bit.query(x, y);
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
