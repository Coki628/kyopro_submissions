/*
・きっちり自力AC！本番中の既出パンチじゃない青diffは久々に通せた気がする。
・LIS、遷移が複雑なDP
・LISが最大3、値が10までだと10*10*10で状態1000くらいしかなさそうと信じると、
　LISの状態を持ってDPできる。実装上は添字でやるとめちゃ面倒そうで、
　mapのキーにvector持たせて陽に管理しちゃうと、とっても楽になる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    ll N, M;
    cin >> N >> M;

    vector<map<vector<ll>, mint>> dp(N+1);
    dp[0][{}] = 1;
    rep(i, N) {
        for (auto& [cur, c] : dp[i]) {
            rep(a, 1, M+1) {
                auto nxt = cur;
                if (nxt.empty()) {
                    nxt.eb(a);
                } elif (a > nxt.back()) {
                    nxt.eb(a);
                } else {
                    nxt[bisect_left(nxt, a)] = a;
                }
                if (nxt.size() <= 3) {
                    dp[i+1][nxt] += c;
                }
            }
        }
    }
    mint ans = 0;
    for (auto& [v, c] : dp[N]) {
        if (v.size() == 3) ans += c;
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
