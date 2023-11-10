/*
・一般グラフ、クエリ先読み、逆操作、UF
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
    vector<pii> edges;
    rep(i, M) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        edges.eb(a, b);
    }
    ll Q;
    cin >> Q;
    vector<array<ll, 3>> qs;
    vector<ll> removed(M);
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x;
            cin >> x;
            x--;
            qs.pb({op, x, -1});
            removed[x] = true;
        } else {
            ll a, b;
            cin >> a >> b;
            a--, b--;
            qs.pb({op, a, b});
        }
    }

    UnionFind uf(N);
    rep(i, M) {
        if (removed[i]) continue;
        auto [a, b] = edges[i];
        uf.merge(a, b);
    }
    vector<string> ans;
    rep(i, Q - 1, -1, -1) {
        auto [op, a, b] = qs[i];
        if (op == 1) {
            auto [x, y] = edges[a];
            uf.merge(x, y);
        } else {
            ans.pb(uf.same(a, b) ? "Yes" : "No");
        }
    }
    reverse(ALL(ans));
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
