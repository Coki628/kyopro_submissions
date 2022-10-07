/*
・きっちり自力AC！
・UF、マージテク
・UFで連結しながらマージテクで連結リストの中身移動してく。
　いわゆるマージテク的はswap操作はしてないけど、
　UFマージ時の親選択が勝手にそれに近いことをしてるはずなのでOK。
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
    ll N, Q;
    cin >> N >> Q;

    UnionFind uf(N);
    vvl adj(N);
    rep(i, N) {
        adj[i].eb(i+1);
    }
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll u, v;
            cin >> u >> v;
            u--; v--;
            if (not uf.same(u, v)) {
                ll ru = uf.find(u);
                ll rv = uf.find(v);
                ll r = uf.merge(u, v);
                if (r == ru) {
                    for (auto w : adj[rv]) {
                        adj[ru].eb(w);
                    }
                } else {
                    for (auto w : adj[ru]) {
                        adj[rv].eb(w);
                    }
                }
            }
        } else {
            ll u;
            cin >> u;
            u--;
            ll ru = uf.find(u);
            sort(ALL(adj[ru]));
            print(adj[ru]);
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
