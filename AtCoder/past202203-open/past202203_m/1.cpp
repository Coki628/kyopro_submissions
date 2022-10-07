/*
・きっちり自力AC！
・平衡二分探索木
・平衡二分探索木を召喚したけど、慣れない操作をやるよりは、
　クエリ先読み*座圧*BITにぶたんをさっさとやった方が速かったかもしれない。
　にぶたんが下からじゃなくて上からx番目求めるだから頭壊れた。
　結局下からやって求めてからひっくり返した。
・元々3.37秒かかっていたものをmapをHashMapにしたら、2.33秒に改善。
　ボトルネックはにぶたんやってる所だと思ったので、結構変わって意外。
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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
using namespace __gnu_pbds;

void solve() {
    ll N, Q;
    cin >> N >> Q;
    auto P = LIST(N);

    tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> tr;
    HashMap<ll, ll> ptoi;
    rep(i, N) {
        ptoi[P[i]] = i;
    }
    rep(i, N) {
        tr.insert(P[i]);
    }
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll a, x;
            cin >> a >> x;
            a--;
            tr.erase(P[a]);
            ptoi.erase(P[a]);
            P[a] = x;
            ptoi[P[a]] = a;
            tr.insert(P[a]);
        } elif (op == 2) {
            ll a;
            cin >> a;
            a--;
            ll r = bisearch_min(-1, N-1, [&](ll x) {
                ll px = *tr.find_by_order(x);
                return P[a] <= px;
            });
            print(N-r);
        } else {
            ll r;
            cin >> r;
            ll p = *tr.find_by_order(N-r);
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
