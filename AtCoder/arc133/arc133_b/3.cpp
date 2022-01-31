/*
・自力AC！
・順列、inplace DP
・dp[i][j] := Aをi番目まで見て、Bで最後に使ったのがjの時の最大値 で貰うDPの気持ちになると、
　遷移先としてあるのはA[i]の倍数となるB[j]に限られるので、これは順列だから十分少なくて、
　毎回自分より手前の最大値+1を遷移させるとすると、iの次元を落としてセグ木でinplace DPできる。
　1次元でやるので、更新順に注意。各回の更新はそれぞれ後ろからやる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    auto B = LIST(N);

    vector<ll> btoi(N+1);
    rep(i, N) {
        btoi[B[i]] = i;
    }
    vvl adj(N);
    rep(i, N) {
        rep(b, A[i], N+1, A[i]) {
            adj[i].eb(btoi[b]);
        }
    }
    // 後ろから更新するようにソートしておく
    rep(i, N) {
        sort(adj[i].rbegin(), adj[i].rend());
    }
    auto dp = get_segment_tree(N+1, [](ll a, ll b) { return max(a, b); }, -INF);
    dp.update(0, 0);
    rep(i, N) {
        for (auto j : adj[i]) {
            dp.update(j+1, max(dp[j+1], dp.query(0, j+1)+1));
        }
        // dp.print(N+1);
    }
    ll ans = dp.all();
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
