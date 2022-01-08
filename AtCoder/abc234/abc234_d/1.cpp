/*
・きっちり自力AC！
・平衡二分探索木
・この前PASTで履修したやつを早速また使ってしまった…。
　BITにぶたんとかで大丈夫なやつ。
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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
using namespace __gnu_pbds;

void solve() {
    ll N, K;
    cin >> N >> K;
    auto P = LIST(N);

    tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> tr;
    rep(i, K) {
        tr.insert(P[i]);
    }
    ll res = *tr.find_by_order(tr.size()-K);
    print(res);
    rep(i, K, N) {
        tr.insert(P[i]);
        res = *tr.find_by_order(tr.size()-K);
        print(res);
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
