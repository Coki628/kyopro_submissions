/*
・先にやろうとしてたBinaryTrieの方針。整えた。
　だがしかしデフォルトだとNODESが足りず、増やすとMLEなのでACできない…。
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

#include "segment/BinaryTrie.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    auto P = LIST(N);

    BinaryTrie<int, 30> bt;
    rep(i, N) {
        bt.add(P[i], i);
    }
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll a, x;
            cin >> a >> x;
            a--;
            bt.del(P[a], a);
            P[a] = x;
            bt.add(P[a], a);
        } elif (op == 2) {
            ll a;
            cin >> a;
            a--;
            ll r = bisearch_min(0, N, [&](ll x) {
                auto [px, _] = bt.get_kth(x);
                return P[a] <= px;
            });
            print(N-r+1);
        } else {
            ll r;
            cin >> r;
            auto [p, ids] = bt.get_kth(N-r+1);
            print(ids[0]+1);
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
