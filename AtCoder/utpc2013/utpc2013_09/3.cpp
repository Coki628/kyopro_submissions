/*
・ライブラリ整備：HL分解
・任意の根を設定できるように改修したのでverifyに。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

#include "graph/HeavyLightDecomposition.hpp"
#include "segment/WaveletMatrix.hpp"

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll N;
    cin >> N;
    vector<ll> A(N);
    rep(i, N) cin >> A[i];
    vvi nodes(N);
    set<ll> se;
    rep(i, N-1) {
        ll s, t;
        cin >> s >> t;
        nodes[s].pb(t);
        nodes[t].pb(s);
        se.insert(t);
    }
    // 根が頂点0とは限らないので確認する
    ll root = -1;
    rep(i, N) {
        if (!se.count(i)) {
            root = i;
            break;
        }
    }

    // HLDとWavelet Matrixを構築
    HeavyLightDecomposition hld(nodes, root);
    vector<ll> B(N);
    rep(i, N) B[hld.in[i]] = A[i];
    WaveletMatrix<ll, 32> wm(B);

    vector<ll> ans(N);
    rep(u, N) {
        // segs := 頂点iの部分木と根へのパスに含まれる区間を列挙
        vector<pll> segs;
        // 頂点iの部分木に対応する区間
        segs.pb({hld.in[u], hld.out[u]});
        // 根へのパスに対応する区間
        if (u != root) {
            hld.add(root, hld.la(u, 1), [&](ll a, ll b) {
                segs.pb({a, b});
            });
        }
        sort(ALL(segs));
        ll M = segs.size();
        // segs2 := 頂点iの部分木と根へのパスに含まれない区間を列挙
        vector<pll> segs2;
        segs2.pb({0, segs[0].first});
        rep(i, 0, M-1) {
            segs2.pb({segs[i].second, segs[i+1].first});
        }
        segs2.pb({segs[M-1].second, N});

        ll lo = -INF, hi = INF;
        for (auto [l, r] : segs2) {
            if (l < r) {
                // 区間[l,r)でA[i]に最も近くてA[u]未満の値
                auto res = wm.prev_value(l, r, A[u]);
                if (res != -1) {
                    chmax(lo, res);
                }
                // 区間[l,r)でA[i]に最も近くてA[u]以上の値
                res = wm.next_value(l, r, A[u]);
                if (res != -1) {
                    chmin(hi, res);
                }
            }
        }
        if (lo == -INF and hi == INF) {
            ans[u] = -1;
        } else {
            if (A[u]-lo <= hi-A[u]) {
                ans[u] = lo;
            } else {
                ans[u] = hi;
            }
        }
    }
    for (ll a : ans) {
        print(a);
    }
    return 0;
}
