/*
参考：https://twitter.com/kude_coder/status/1510441807553110018
・自力ならず。これは解きたかったな。悔しい。
・DAGのDP、メモ化再帰
・逆辺張ってDAPのDP。その方針で考えてたのに詰め切れなかった。
　複数合流する箇所では、堰き止められて1つ以外は確定すると思っていい。
　DPの値としてはmaxを取っていくので、ここで残すのは最小が最善となる。
・最大値を求めるのに、残す値としては最小を選んでいくって辺りが
　直感に反してて難しかったな。でもこのくらいは解けるべきだった。
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    auto P = LIST(N);
    rep(i, N) P[i]--;

    vvi nodes(N);
    vector<ll> src;
    rep(i, N) {
        if (P[i] >= 0) {
            // 逆辺
            nodes[P[i]].eb(i);
        } else {
            src.eb(i);
        }
    }

    vector<ll> dp(N, -INF);
    ll ans = 0;
    auto dfs = [&](auto&& f, ll u) -> void {
        if (dp[u] > -INF) {
            return;
        }
        dp[u] = A[u];
        vector<ll> mxs;
        for (auto v : nodes[u]) {
            f(f, v);
            mxs.eb(dp[v]);
        }
        if (mxs.size()) {
            sort(ALL(mxs));
            // 最小だけ残す
            chmax(dp[u], mxs[0]);
            // それ以外はここで確定させる
            ans += accumulate(mxs.begin()+1, mxs.end(), 0LL);
        }
    };
    for (ll i : src) {
        dfs(dfs, i);
        ans += dp[i];
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
