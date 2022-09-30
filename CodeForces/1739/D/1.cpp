/*
・終了後5分くらいで自力AC。悔しい～。
・二分探索、木DP
・深さを決め打ってにぶたん内で木DP。
　(戻りで)そこまでの深さがxに達したらそこから下をぶった切る感じ。
　最初、HLD*遅延セグ木に乗せて部分木を更新しようとしたり、正解の方針に気付いた後も、
　戻りじゃなくて行きがけの深さで決めようとしたりで時間をかけてしまった…。
　(部分木を切る感じなので、行きがけより帰りがけで見た方が得しそうなのは
　落ち着いて考えると結構すぐ分かることだった…。)
・Cの数え上げは苦手系なのでしょうがないとして、
　こっちはもっと手早く解けるべきだったなぁ…。
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
    ll N, K;
    cin >> N >> K;
    vvi nodes(N);
    rep(i, 1, N) {
        ll p;
        cin >> p;
        p--;
        nodes[p].eb(i);
        nodes[i].eb(p);
    }

    ll res = bisearch_min(0, N, [&](ll x) {
        ll cnt = 0;
        vector<ll> dp(N);
        auto dfs = [&](auto&& f, ll u, ll prv) -> void {
            for (auto v : nodes[u]) {
                if (v == prv) continue;
                f(f, v, u);
                if (prv != -1 and dp[v]+1 == x) {
                    cnt++;
                } else {
                    chmax(dp[u], dp[v]+1);
                }
            }
        };
        dfs(dfs, 0, -1);
        return cnt <= K;
    });
    print(res);
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
