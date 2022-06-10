/*
・ABC残埋め
・きっちり自力AC！黄diff自力は嬉しい。
・構築、DFS
・とりあえず連結成分内でソートしてソート済にならないなら無理。
　構築やりながら無理かどうか判定入れても良さそうだけど、
　そっちやってる時余計な思考リソースを割きたくないので先にチェックして潰しておく。
　で、OKなら連結成分内で依存性のない所から適当に確定させていけばいけるはずで、
　一般グラフなんだけど、木で言う葉みたいな場所から確定させていけば良さそう。
　これは適当にDFSやった時末端になった場所からやる感じにする。
　具体的には、その時点での末端を見つけるDFSの中で、末端に着いたら、
　その頂点を確定させるために目当ての番号を探しに行く別のDFSを飛ばす感じ。
　訪問済とか確定済は再度踏まないように適宜管理する。
　目当ての番号を見つけたら、戻りで作るパスに沿って辺を答えに追加していけばOK。
・公式解説見たら、先に辺減らして全域木(森)にしてから処理してた。
　確かにその方が末端かどうか見えやすくて見通し立ちやすいかも。
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

#include "common/HashMap.hpp"

void solve() {
    ll N;
    cin >> N;
    auto P = LIST(N);
    rep(i, N) P[i]--;
    ll M;
    cin >> M;
    vvi nodes(N);
    UnionFind uf(N);
    HashMap<pll, ll> etoi;
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
        uf.merge(u, v);
        etoi[{u, v}] = i + 1;
        etoi[{v, u}] = i + 1;
    }

    vvl adj(N);
    rep(i, N) {
        adj[uf.find(i)].eb(P[i]);
    }
    rep(i, N) {
        sort(adj[i].rbegin(), adj[i].rend());
    }
    vector<ll> A;
    rep(i, N) {
        A.eb(adj[uf.find(i)].back()); adj[uf.find(i)].pop_back();
    }
    if (A != sorted(A)) {
        print(-1);
        return;
    }

    vector<bool> done(N), visited2(N);
    vector<ll> ans;
    auto dfs2 = [&](auto&& f, ll u, ll x) -> bool {
        visited2[u] = true;
        if (P[u] == x) {
            return true;
        }
        for (auto v : nodes[u]) {
            if (not done[v] and not visited2[v]) {
                if (f(f, v, x)) {
                    swap(P[u], P[v]);
                    ans.eb(etoi[{u, v}]);
                    return true;
                }
            }
        }
        return false;
    };
    vector<bool> visited(N);
    auto dfs1 = [&](auto&& f, ll u) -> void {
        visited[u] = true;
        for (auto v : nodes[u]) {
            if (not visited[v]) {
                f(f, v);
            }
        }
        visited2.assign(N, false);
        assert(dfs2(dfs2, u, u));
        done[u] = true;
    };
    rep(i, N) {
        if (not visited[i]) {
            dfs1(dfs1, i);
        }
    }
    assert(P == sorted(P));
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
