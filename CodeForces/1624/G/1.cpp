/*
参考：道場のbaitoさんのコメント
・自力ならず。これは気付きたかったな…。
・上位ビットから貪欲、全域木
・全体orの最小化なので、そのビットが立っている要素が1つでもあるかどうかが重要になる。
　そこで上位ビットから見て行って、そのビットを使わなくても全域木が構築できたら、
　以後そのビットが立っている要素は使わない、というのを全ビット見るといい。
　ここで構築できなくなるようなビットは必須なので、それを答えに足していく。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<tuple<ll, ll, ll>> edges;
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        edges.eb(u, v, c);
    }

    vector<bool> removed(M);
    const int K = 33;
    ll ans = 0;
    rep(k, K-1, -1, -1) {
        UnionFind uf(N);
        rep(i, M) {
            auto [u, v, c] = edges[i];
            if (removed[i] or c>>k & 1) continue;
            uf.merge(u, v);
        }
        if (uf.size() == 1) {
            rep(i, M) {
                auto [u, v, c] = edges[i];
                if (removed[i] or c>>k & 1) {
                    removed[i] = true;
                }
            }
        } else {
            ans += 1LL<<k;
        }
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
