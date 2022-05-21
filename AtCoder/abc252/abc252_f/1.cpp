/*
・きっちり自力AC！
・逆操作、貪欲、優先度付きキュー
・前から見るとどこ切っていいか分からないけど、逆操作なら小さいやつから貪欲にマージでいい。
　PQでやる。Lがでかい時は先にその分もキューに詰めとく。(1ペナ)
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
    ll N, L;
    cin >> N >> L;
    auto A = LIST(N);

    priority_queue<ll, vector<ll>, greater<ll>> que;
    rep(i, N) que.push(A[i]);
    ll rest = L - sum(A);
    if (rest) {
        que.push(rest);
    }
    ll ans = 0;
    while (que.size() >= 2) {
        ll a = que.top(); que.pop();
        ll b = que.top(); que.pop();
        ll nxt = a + b;
        ans += nxt;
        que.push(nxt);
    }
    print(ans);
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
