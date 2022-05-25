/*
参考：https://nyaannyaan.github.io/library/data-structure/binary-trie.hpp
・ライブラリ整備：Binary Trie
・中央値、Binrary Trie
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

#include "segment/BinaryTrie.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    vvi nodes(N);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    BinaryTrie<ll, 30, 200000*32> bt;
    auto get_median = [&]() -> ll {
        ll cnt = bt.size();
        if (cnt%2 == 1) {
            return bt.get_kth(ceil(cnt, 2LL)).first;
        } else {
            ll a = bt.get_kth(cnt/2).first;
            ll b = bt.get_kth(cnt/2+1).first;
            return (a+b) / 2;
        }
    };

    auto dfs = [&](auto&& f, ll u, ll prv, ll depth) -> ll {
        bt.add(A[u]);
        ll res;
        if (prv != -1 and nodes[u].size() == 1) {
            res = get_median(); 
        } else {
            if (depth%2 == 0) {
                res = -INF;
                for (ll v : nodes[u]) {
                    if (v == prv) continue;
                    chmax(res, f(f, v, u, depth+1));
                }
            } else {
                res = INF;
                for (ll v : nodes[u]) {
                    if (v == prv) continue;
                    chmin(res, f(f, v, u, depth+1));
                }
            }
        }
        bt.del(A[u]);
        return res;
    };
    ll ans = dfs(dfs, 0, -1, 0);
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
