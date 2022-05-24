/*
・きっちり自力AC。時間なくて、終了3分後くらいに…。
・整数BFS
・状態数は多くないと信じて整数BFS。memo[x] = 0 の初期化を忘れてブザービートを逃す…。
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
    ll N, x;
    cin >> N >> x;

    map<ll, ll> memo;
    queue<ll> que;
    memo[x] = 0;
    que.push(x);
    while (que.size()) {
        ll cur = que.front(); que.pop();
        string s = tostr(cur);
        ll n = s.size();
        if (n == N) {
            print(memo[cur]);
            return;
        }
        rep(i, n) {
            ll y = toint(s[i]);
            if (mul_overflow(cur, y)) continue;
            ll nxt = cur * y;
            if (not memo.count(nxt)) {
                memo[nxt] = memo[cur] + 1;
                que.push(nxt);
            }
        }
    }
    print(-1);
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
