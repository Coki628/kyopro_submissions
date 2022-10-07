/*
・BinaryTrieをNyaanさん版じゃなくてうしさん版にした。
　これだとメモリは何とかなる。(それでも600MBくらい食ってる…)
・普通にやったら6.20秒で、count_lessっていう便利な関数があったので
　にぶたんやめてそれ使ったら2.16秒。(制約8秒)
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

    HashMap<ll, ll> ptoi;
    rep(i, N) {
        ptoi[P[i]] = i;
    }
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
            bt.erase(P[a]);
            P[a] = x;
            ptoi[P[a]] = a;
            bt.add(P[a]);
        } elif (op == 2) {
            ll a;
            cin >> a;
            a--;
            ll res = N - bt.count_less(P[a]);
            print(res);
            // ll r = bisearch_min(-1, N-1, [&](ll x) {
            //     auto [px, _] = bt.kth_element(x);
            //     return P[a] <= px;
            // });
            // print(N-r);
        } else {
            ll r;
            cin >> r;
            auto [p, _] = bt.kth_element(N-r);
            print(ptoi[p]+1);
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
