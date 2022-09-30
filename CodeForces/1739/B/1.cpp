/*
・きっちり自力AC！
・前から決めていき該当する値が2通りある時、小さい方も非負なら一意にならないので-1、
　そうでなければ最後までシミュすれば答えが出る。
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
    ll N;
    cin >> N;
    auto A = LIST(N);

    ll cur = A[0];
    vector<ll> ans(N);
    ans[0] = cur;
    rep(i, 1, N) {
        ll nxt1 = cur - A[i];
        ll nxt2 = cur + A[i];
        if (nxt1 != nxt2 and nxt1 >= 0) {
            print(-1);
            return;
        }
        cur = nxt2;
        ans[i] = cur;
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
