/*
・きっちり自力AC！
・文字列の状態を頂点にBFS。
・なんか想定は転倒数数えるだったぽいけど、まあこの文字数なら全状態持てるので。。
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
    string T = "atcoder";
    ll N = T.size();
    string S;
    cin >> S;

    HashMap<string, int> memo;
    queue<string> que;
    memo[S] = 0;
    que.push(S);
    while (que.size()) {
        auto cur = que.front(); que.pop();
        auto nxt = cur;
        rep(i, N-1) {
            swap(nxt[i], nxt[i+1]);
            if (not memo.count(nxt)) {
                memo[nxt] = memo[cur] + 1;
                que.push(nxt);
            }
            swap(nxt[i], nxt[i+1]);
        }
    }
    int ans = memo[T];
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
