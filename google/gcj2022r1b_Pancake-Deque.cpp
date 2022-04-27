/*
・きっちり自力AC！
・前後小さい方から貪欲に取っていく。
　反例がありそうで怖くなるけど、無事AC。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

    deque<ll> que(ALL(A));
    ll cur = 0, ans = 0;
    while (que.size()) {
        if (que.front() <= que.back()) {
            ll nxt = que.front(); que.pop_front();
            if (nxt >= cur) {
                ans++;
                chmax(cur, nxt);
            }
        } else {
            ll nxt = que.back(); que.pop_back();
            if (nxt >= cur) {
                ans++;
                chmax(cur, nxt);
            }
        }
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
    rep(i, 1, T+1) {
        cout << "Case #" + tostr(i) + ": ";
        solve();
    }
    return 0;
}
