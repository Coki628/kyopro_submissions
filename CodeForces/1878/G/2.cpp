/*
・Div.3残埋め
・時間かかったけど自力AC！こういう木クエリ問は好き。
・木グラフ、パスクエリ、HLD*区間OR、ビット毎に見る、にぶたん、座圧いもす
・ビット毎に見ると、(x,z),(z,y)両方でビットが立つ範囲は区間になる。
　この左右端をにぶたんで求めて、一番重複が多かった場所を使えば最適になる。
　区間ORをセグ木でやると実質log4つ(ビット毎、にぶたん、HLD、セグ木)みたいになって、
　制約5秒でもこれはTLEした。セグ木をSparse Tableに持ち替えてlog1個削ったら無事AC。(2.68秒)
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

#include "common/trisearch.hpp"
#include "graph/HeavyLightDecomposition.hpp"
#include "datastructure/Imos.hpp"
#include "datastructure/SparseTable.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    HeavyLightDecomposition hld(nodes);
    vector<ll> vec(N);
    rep(u, N) {
        vec[hld[u]] = A[u];
    }
    auto st = get_sparse_table(vec, [](ll a, ll b) { return a | b; }, 0LL);

    ll Q;
    cin >> Q;
    vector<ll> ans(Q);
    rep(i, Q) {
        ll x, y;
        cin >> x >> y;
        x--, y--;

        ll len = hld.dist(x, y);
        ll lca = hld.lca(x, y);
        ll d1 = hld.dist(x, lca);
        ll d2 = len - d1;
        vector<pll> LR;
        rep(b, 30) {
            ll res1 = bisearch_min(-1, len + 1, [&](ll m) {
                ll z = m <= d1 ? hld.la(x, m) : hld.next(lca, y, m - d1);
                ll resa = hld.query(x, z, 0LL, [&](ll a, ll b) { return st.query(a, b); }, [](ll a, ll b) { return a | b; });
                return resa >> b & 1;
            });
            if (res1 == len + 1) continue;
            ll res2 = bisearch_min(-1, len + 1, [&](ll m) {
                ll z = m <= d2 ? hld.la(y, m) : hld.next(lca, x, m - d2);
                ll resb = hld.query(y, z, 0LL, [&](ll a, ll b) { return st.query(a, b); }, [](ll a, ll b) { return a | b; });
                return resb >> b & 1;
            });
            assert(res2 != len + 1);
            // [l,r)
            LR.eb(res1, len - res2 + 1);
        }
        // 一番区間の重複が多い場所を探す
        Compress<ll> cp;
        for (auto [l, r] : LR) {
            cp.add(l);
            cp.add(r);
        }
        cp.build();
        ll M = cp.size();
        Imos<ll> imos(M);
        for (auto [l, r] : LR) {
            imos.add(cp[l], cp[r], 1);
        }
        imos.build();
        ans[i] = LR.size() + max(imos.dat);
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
