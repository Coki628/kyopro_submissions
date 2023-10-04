/*
・ゲームDP
・原則通り、その先から負けが1つでも返るなら自身は勝ち。
　結果をひっくり返すような形になるので、慣れないと混乱しがち。
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
    ll N, a, b;
    cin >> N >> a >> b;

    vector<ll> memo(N + 1, -1LL);
    auto rec = [&](auto &&f, ll i) -> ll {
        if (memo[i] != -1) {
            return memo[i];
        }
        ll res = 1;
        if (i - a >= 0) {
            res &= f(f, i - a);
        }
        if (i - b >= 0) {
            res &= f(f, i - b);
        }
        return memo[i] = 1 - res;
    };
    if (rec(rec, N)) {
        print("First");
    } else {
        print("Second");
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
