/*
・きっちり自力AC！
・Functional Graph、サイクル
・実際は無向辺2本ずつのサイクルだったものが、各人片方だけ覚えている、
　という設定で1本の有向辺として手掛かりになっているというもの。
・ペアでお互いに覚えている部分だけは、2人サイクルなのか、
　他と繋がっていたのか判別がつかない。ここを数える。
　そうすればこれらが全て分かれていた場合と繋がっていた場合で、
　連結成分数の最大最小が取れる。
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
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;
    A--;

    UnionFind uf(N);
    ll pcnt = 0;
    set<pll> se;
    rep(i, N) {
        ll u = i;
        ll v = A[i];
        if (u > v) swap(u, v);
        if (se.count({u, v})) {
            pcnt++;
        } else {
            se.insert({u, v});
            uf.merge(u, v);
        }
    }
    ll mx = uf.size();
    ll mn = mx - max(pcnt - 1, 0LL);
    print(mkp(mn, mx));
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
