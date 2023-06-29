/*
参考：https://atcoder.jp/contests/abc289/editorial/5700
・upsolveした。
・式変形、CHT
・まずBを降順ソートしておくと、Biが小さい方からある商品を買う人が1,2,..N人とできる。
　で、商品の売上をy、商品価値Cjをxと置くと、各Biを直線の式y=i*x+i*Biと表せる。
　ここまで作れれば、後は各BiについてのN本の直線をCHTに入れて、
　各Cjをxとしてxの位置をM回取れば全ての答えを得られる。
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

#include "datastructure/DynamicLiChaoTree.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> B(N), C(M);
    cin >> B >> C;

    sort(B.rbegin(), B.rend());
    DynamicLiChaoTree<ll> lt(0, max(C), INF, false);
    rep(i, N) {
        lt.add_line(i + 1, (i + 1) * B[i]);
    }
    vector<ll> ans(M);
    rep(i, M) {
        ans[i] = lt.query(C[i]);
    }
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
