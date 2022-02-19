/*
参考：https://www.slideshare.net/shindannin/project-selection-problem
・自力ならず。。いいとこまで行ってたのに、悔しい。
・最大流、最小カット、復元
・頂点コストなので、入りと出の頂点作って、最大フロー流して最小カット。
　ここまで分かったのに、最小カットの復元方法で詰まった。
　ググったら情報はでてきて、残余グラフにBFSして行き詰まった所、
　ってのは分かったんだけど実装できず。(診断人さんスライドの6.6)
・実はACL最大流にmin_cutっていうのがそもそもあって、
　これ使えばいい？って存在に気付いたのが終了後だったし、
　それ使ってもどうやるか分からなくて結局人の見た。
　残余グラフでの到達可否が返されるので、見たい辺の繋ぐ頂点ペアについて、
　頂点u,vで到達可否が異なれば、この間でカットしたことになる。ってな具合だった。
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

#include "acl/maxflow.hpp"
using namespace atcoder;

void solve() {
    ll N, M;
    cin >> N >> M;

    ll s = 0+N;
    ll t = N-1;
    mf_graph<ll> mf(N*2);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        mf.add_edge(u+N, v, INF);
        mf.add_edge(v+N, u, INF);
    }
    auto cost = LIST(N);
    rep(i, N) {
        mf.add_edge(i, i+N, cost[i]);
    }

    auto mx = mf.flow(s, t);
    print(mx);
    auto cut = mf.min_cut(s);
    vector<ll> ans;
    rep(u, 1, N-1) {
        ll v = u+N;
        // 頂点u,vで到達可否が異なれば、この間でカットしたことになる
        if (cut[u] != cut[v]) {
            ans.eb(u+1);
        }
    }
    print(ans.size());
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
