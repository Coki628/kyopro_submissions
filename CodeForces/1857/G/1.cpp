/*
・Div.3残埋め
・なんとか自力AC！やったね。
・木グラフ無向重み付き、辺の数え上げ、MST、パスの最大値、UF
・MSTに辺追加というテーマ。MSTに影響を与えないような辺を追加するので、
　各辺で独立に考えられるとする。ある辺がMSTに影響しないためには、
　コストが、張った辺間を繋ぐパス上の最大値超である必要がある。
　最大値以下だった場合、その既存の辺を切って違うMSTが作れてしまう。
　(この話はMSTの別の問題で見たことある。)
　これで、全ての辺でパスのmaxが取れれば、
　その辺について何パターン追加できるか分かるようになった。
　このままだと辺の数は2乗なので無理。どうまとめるか考える。
　気持ち的に、最大値が同じ辺をまとめて処理したい。
　どうにかまとめられないか考えると、コストが大きい/小さい方から見て行って、
　少しずつ候補になる場所を減らして/増やしていけないか、と思う。
　例えば一番小さい辺から見ると、その次の辺を見る時には、その辺は自由に通れる、
　といった状況になる。これはUFで1本ずつ辺追加していくとできる。
　ある辺に注目すると、その辺を通るパス数は両側の連結成分数で掛け算すると求まる。
　ここまで来れば後は冪乗の数え上げをやればOK。
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

void solve() {
    ll N, S;
    cin >> N >> S;
    vvpil nodes(N);
    vector<array<ll, 3>> edges;
    rep(i, N - 1) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        nodes[u].eb(v, c);
        nodes[v].eb(u, c);
        edges.pb({c, u, v});
    }

    sort(ALL(edges));
    UnionFind uf(N);
    mint ans = 1;
    for (auto [c, u, v] : edges) {
        // コストが取りうる値の数^そういう辺の数
        ans *= mint(max(S - c, 0LL) + 1).pow(uf.size(u) * uf.size(v) - 1);
        uf.merge(u, v);
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
    while (T--) solve();

    return 0;
}
