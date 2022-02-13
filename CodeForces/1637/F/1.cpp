/*
参考：https://twitter.com/tatyam_prime/status/1492553249227825152
　　　https://twitter.com/fuppy_kyopro/status/1492546197076152320
・自力ならず。
・木DP
・ちょい難しめの木DPではあるけど、このくらいを解いていく気持ちでいきたい。
・まず、Hが最大の頂点を根として見て行くと、親側のことをほぼ考えなくてよくなるのでやりやすい。
・で、コストと部分木の最大Hの高さを持って木DPする。
　部分木で最大の所より今見ている頂点のHが小さければカバーしてもらえるので何もしないでよくて、
　H[u]のが大きければ、その部分木最大の所の葉に設置した塔を自分の高さのものに置き換えると考える。
・根だけちょっと別の場合分けが必要。そこも葉なのかそうじゃないのかで変わってくる。
　葉であればシンプルにそこにH[u]の高さの塔を置くことになり、
　そうでないなら自身の所に新規に置く必要はなく、
　部分木から2番目に大きい所と置き換えることで目的を達成できる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define MINT_TO_LL_CAST
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
    auto H = LIST(N);
    vvi nodes(N);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    ll root = max_element(ALL(H))-H.begin();
    vector<ll> cost(N), mxh(N);
    auto dfs = [&](auto&& f, ll u, ll prv) -> void {
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            cost[u] += cost[v];
            chmax(mxh[u], mxh[v]);
        }
        if (mxh[u] < H[u]) {
            cost[u] += H[u]-mxh[u];
            mxh[u] = H[u];
        }
        if (u == root) {
            if (nodes[u].size() == 1) {
                cost[u] += H[u];
            } else {
                vector<ll> tmp;
                for (auto v : nodes[u]) {
                    tmp.eb(mxh[v]);
                }
                sort(tmp.rbegin(), tmp.rend());
                assert(tmp.size() >= 2);
                cost[u] += H[u]-tmp[1];
            }
        }
    };
    dfs(dfs, root, -1);
    print(cost[root]);
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
