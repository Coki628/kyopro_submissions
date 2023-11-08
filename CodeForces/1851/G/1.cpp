/*
・終了後自力AC！
・辺の追加順序を考えたUF、クエリ先読み
・色々整理すると、各クエリの際に始点+eの高さまでは自由に移動できると分かる。
　それより上の頂点までは行けない。行けない頂点と関わる辺だけを外した状態で
　UFで判定がしたいが、たくさんの辺を削除する場合もあるはずなので、
　辺削除ができるUFがあっても対応できなそう。
　そこで、低い所にある頂点から辺を張っていくようにすれば、
　削除なしで対応できそうだとなる。
　ここまで分かれば、後は必要な頂点まで追加し終わった所でクエリを確認できるように、
　隣接リストで必要な時系列に合った位置にクエリの情報を差し込んでおけばOK。
・あと30分くらいあればワンチャンこれ本番間に合ったかなぁ。
　いずれにせよここまでをもっと速く解けるようにならなきゃここまでは来れない。
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

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> H(N);
    cin >> H;
    map<ll, vector<array<ll, 3>>> events;
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        events[max(H[u], H[v])].pb({-1, u, v});
    }

    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll a, b, e;
        cin >> a >> b >> e;
        a--, b--;
        events[H[a] + e].pb({i, a, b});
    }

    UnionFind uf(N);
    vector<string> ans(Q);
    for (auto& [h, vec] : events) {
        for (auto [op, u, v] : vec) {
            if (op < 0) {
                uf.merge(u, v);
            } else {
                if (uf.same(u, v)) {
                    ans[op] = "YES";
                } else {
                    ans[op] = "NO";
                }
            }
        }
    }
    print(ans, '\n');
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
