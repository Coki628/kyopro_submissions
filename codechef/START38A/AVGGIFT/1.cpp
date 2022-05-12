/*
参考：https://twitter.com/kude_coder/status/1524449269700194304
・自力ならず。Div.1とはいえまさかの0完太陽…。
・平均は引いて総和0、はよかったと思うんだけど、
　正負両方あれば任意に0に到達できるのが見えなかった。
　GCDとかゴニョゴニョやってしまったんだけど、何でもいいんだね…。
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

void solve() {
    ll N, X;;
    cin >> N >> X;
    auto A = LIST(N);

    rep(i, N) {
        A[i] -= X;
    }
    if (count(ALL(A), 0)) {
        YES();
        return;
    }

    vector<ll> A1, A2;
    rep(i, N) {
        if (A[i] < 0) {
            A1.eb(-A[i]);
        } elif (A[i] > 0) {
            A2.eb(A[i]);
        }
    }
    if (A1.empty() or A2.empty()) {
        NO();
    } else {
        YES();
    }
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
