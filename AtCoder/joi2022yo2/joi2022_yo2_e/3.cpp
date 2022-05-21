/*
・永続配列、永続UnionFind
・こっちのがundo可能UFより直近で保守されてそうなので使ってみた。
　噂だけ聞いたことあった永続配列と、それを用いたUnionFind。
・使い方としては、戻したい状態をコピーするなり適当に残しておいて、
　更新後のUFに雑に代入で上書き、みたいにしていいみたい。
　普通に考えたら毎回O(N)かかってTLE不可避のはずなんだけど、なんか通っちゃう。まじで魔法…。
・ちなみに速度的には今回制約がN,M,Q40万(TL4秒)で、undo可能UFが1.37秒、永続UFが1.68秒だった。
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
using mint = ModInt<MOD>;
#include "template.hpp"

#include "graph/PersistentUnionFind.hpp"

void solve() {
    ll N, M, K;
    cin >> N >> M >> K;
    vector<pii> edges;
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        edges.eb(u, v);
    }
    auto S = LIST(N);
    rep(i, N) S[i]--;

    PersistentUnionFind uf(N);
    map<pii, vector<pii>> adj;
    for (auto [u, v] : edges) {
        if (S[u] == S[v]) {
            uf.merge(u, v);
        } else {
            if (S[u] > S[v]) swap(u, v);
            adj[{S[u], S[v]}].eb(u, v);
        }
    }

    ll Q;
    cin >> Q;
    map<pii, vector<tuple<int, int, int>>> qs;
    vector<ll> ans(Q);
    rep(i, Q) {
        ll a, b;
        cin >> a >> b;
        a--; b--;

        if (S[a] == S[b]) {
            ans[i] = uf.same(a, b);
        } else {
            if (S[a] > S[b]) swap(a, b);
            qs[{S[a], S[b]}].eb(a, b, i);
        }
    }

    for (auto& [k, li] : qs) {
        auto [sa, sb] = k;
        auto tmp = uf;
        for (auto [u, v] : adj[{sa, sb}]) {
            uf.merge(u, v);
        }
        for (auto [a, b, i] : li) {
            ans[i] = uf.same(a, b);
        }
        uf = tmp;
    }
    print(ans, '\n');
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
