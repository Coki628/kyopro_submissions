/*
参考：https://www.ioi-jp.org/joi/2021/2022-yo2/2022-yo2-t5-review.html
・自力ならず。これはまあ使ったことないデータ構造だししょうがないか…。
・undo可能UF
・とりあえずうし先生のところから使えそうなものを借りてきた。
　undoできればできると聞いたら、その先の満点解法は自分で導けた。
　(S[u], S[v])ペアでまとめておけば、そこが連結した状態を作るための
　各辺の追加と状態戻しは辺の本数分くらいで抑えられているはず。
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

#include "graph/UnionFindUndo.hpp"

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

    UnionFindUndo uf(N);
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
        auto tmp = adj[{sa, sb}];
        ll m = tmp.size();
        for (auto [u, v] : tmp) {
            uf.merge(u, v);
        }
        for (auto [a, b, i] : li) {
            ans[i] = uf.same(a, b);
        }
        uf.undo(m);
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
