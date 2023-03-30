/*
・DFS、UF、パスの取得、グラフの縮約
・今回のグラフは逆辺だけ張れば頂点0に向かう根付き木で、
　辺の方向は小さい方へのみと分かっているので、
　HLDでLCAとか探さなくても普通に遡る処理だけ書けばよかったので、一応それも書いた。
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

void solve() {
    ll N;
    cin >> N;
    vector<ll> P(N - 1);
    cin >> P;
    P--;
    vvi nodes(N), nodesrev(N);
    rep(i, N - 1) {
        nodes[P[i]].eb(i + 1);
        nodesrev[i + 1].eb(P[i]);
    }

    vector<ll> mni(N, INF);
    auto dfs = [&](auto &&f, ll u) {
        if (mni[u] < INF) return;
        mni[u] = u;
        for (auto v : nodes[u]) {
            f(f, v);
            chmin(mni[u], mni[v]);
        }
    };
    rep(i, N) {
        dfs(dfs, i);
    }

    UnionFind uf(N);
    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll u, v;
            cin >> u >> v;
            u--, v--;
            if (not uf.same(u, v)) {
                vector<ll> paths;
                ll a = u, b = v;
                if (a > b) {
                    swap(a, b);
                }
                ll ra = uf.find(a);
                ll rb = uf.find(b);
                while (ra != rb) {
                    paths.eb(rb);
                    assert(nodesrev[b].size() == 1);
                    b = nodesrev[b][0];
                    rb = uf.find(b);
                }

                for (auto ru : paths) {
                    ru = uf.find(ru);
                    ll rv = uf.find(v);
                    ll r = uf.merge(ru, rv);
                    if (r != -1) {
                        mni[r] = min(mni[ru], mni[rv]);
                    }
                }
            }
        } else {
            ll x;
            cin >> x;
            x--;
            ll rx = uf.find(x);
            print(mni[rx] + 1);
        }
    }
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
