/*
参考：https://bakamono1357.hatenablog.com/entry/2024/02/11/133121
・木グラフ、頂点属性、数え上げ、誘導部分グラフ
・Auxiliary Tree、木DP
・色固定できれば木DPできそう、までは辿り着いたのに、木DPがうまく作れず。。
　実際むずくて、siroさんの記事よく読んでようやく何やればいいか分かった。
　まず、Auxiliary Treeとは言っても、含まれる頂点は欲しい頂点だけではなく、
　それらのLCAも含まれるんだった。(それはそう…)
　なので単純に数えてはダメで、色がcではない頂点が来た時の対応を工夫する必要があった。
　本番中とかはそもそもこの辺に気付けてなかったので問題外だったね…。
　色cだけだったら、部分木の切り方の通り数みたいになって、これは多分
　dp[u] *= dp[v] + 1 ってやるだけだと思う。多分ね。。
　で、色cじゃないのが来た時にどうすれば良かったか。
　今回の題意は「次数1の頂点(つまり葉)が全て色c」というもの。
　つまり色cじゃない所は次数がどうなるかを気にする必要がある。
　元の次数ならもちろん分かるが、そのうち「使ってる次数」は状態を分けるなりしないと分からない。
　今回は(親側を除いて)頂点uの次数が1になるようなものは不可、としたい。
　この場合、色cではない頂点uが葉になってしまうので。
　それとは別に色cでなかったら孤立点も引かないといけないが、
　これはまあ-1するだけなのでさほど考えることはない。
　この次数1というのは、ある部分木vだけ使う、といったものなので、
　実は単純に各部分木vが持つ通り数を総和したものがそれになる。
　この部分が分かれば、後は適切にダメなパターンを引いたものを答えに足していけばOK。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "graph/AuxiliaryTree.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;
    A--;
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    vvi adj(N);
    rep(u, N) {
        adj[A[u]].eb(u);
    }
    AuxiliaryTree aux(nodes);
    mint ans = 0;
    rep(c, N) {
        if (adj[c].empty()) continue;
        auto [nodes2, r] = aux.build(adj[c]);
        // dp1[u] := 頂点uを根とする部分木の中で、次数1の頂点の色が全てcであるものの通り数
        // dp2[u] := 上記 + 色cでないものも許容(孤立点は除く)
        map<int, mint> dp1, dp2;
        auto dfs = [&](auto &&f, ll u, ll prv) -> void {
            dp1[u] = 1;
            dp2[u] = 1;
            mint sub = 0;
            for (auto [v, _] : nodes2[u]) {
                if (v == prv) continue;
                f(f, v, u);
                dp1[u] *= dp2[v] + 1;
                dp2[u] *= dp2[v] + 1;
                // この部分木vだけ使う(親側を切った時、次数1になってしまう)通り数
                sub += dp2[v];
            }
            if (A[u] != c) {
                dp1[u] -= sub;
                dp1[u]--;
                dp2[u]--;
            }
            // ここの親側で切る場合の通り数を答えに足す
            ans += dp1[u];
        };
        dfs(dfs, r, -1);
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
