/*
・終了後5分弱で自力AC！惜しかった…。
・Functional Graph、SCC
・各頂点、自分の指している(怖がっている)頂点がまだ残っていれば利得*2が条件。
　Functional Graphなのでサイクルとサイクルへ向かう枝みたいなグラフになる。
　で、サイクルでない部分は適切な順序で取れば良くて、
　サイクル内では1つだけ利得を*2できない頂点が出てくる。
　これを一番利得の小さい頂点になるようにやる。
　Functional GraphはSCCに突っ込めばサイクルとそれ以外を分けれるので
　(強連結成分の頂点が2つ以上ならサイクル、自己ループがあるとこの限りじゃないが、
　今回は制約より自己ループなし)、
　各サイクルでソートして適切に*2にならない頂点を選ぶ。
・Cで詰まってなければ間に合ったよなー。。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

#include "acl/scc.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> P(N), C(N);
    cin >> P >> C;
    P--;

    atcoder::scc_graph scc(N);
    rep(i, N) {
        scc.add_edge(i, P[i]);
    }
    ll sm = 0;
    vector<ll> ans;
    for (auto group : scc.scc()) {
        if (group.size() >= 2) {
            vector<pll> vec;
            for (auto u : group) {
                vec.eb(C[u], u);
            }
            sort(ALL(vec));
            // 一番安いやつ(vec[0].second)が怖がってるやつ(P[vec[0].second])から始める
            ll s = P[vec[0].second];
            ll cur = s;
            while (P[cur] != s) {
                sm += C[cur] * 2;
                ans.eb(cur);
                cur = P[cur];
            }
            // こいつだけ怖がってるやつを先に消してしまっているので2倍にならない
            sm += C[cur];
            ans.eb(cur);
        } else {
            sm += C[group[0]] * 2;
            ans.eb(group[0]);
        }
    }
    // print(sm);
    ans++;
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
    while (T--) solve();

    return 0;
}
