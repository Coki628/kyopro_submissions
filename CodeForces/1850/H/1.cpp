/*
・きっちり自力AC！
・重み付きUF
・正当性の確認どうやるかちょっと忘れてたけど、
　重み付きUFにほぼお任せで大丈夫。
　次回悩みたくないのでライブラリに正当性チェックのメソッド追加しておいた。
・Div.4とはいえ、時間内全完は初の気がする。嬉しいー。むしろ1時間くらい余ったしな。
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

#include "graph/WeightedUnionFind.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    WeightedUnionFind<ll> uf(N);
    bool ok = true;
    rep(i, M) {
        ll a, b, d;
        cin >> a >> b >> d;
        a--, b--;
        if (uf.same(a, b)) {
            if (uf.diff(a, b) != d) {
                ok = false;
            }
        } else {
            uf.merge(a, b, d);
        }
    }
    if (ok) YES();
    else NO();
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
