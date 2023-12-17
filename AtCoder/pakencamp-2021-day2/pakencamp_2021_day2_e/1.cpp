/*
・気まぐれ埋め
・きっちり自力AC！
・回文、連続部分列、入力定数個数え上げ
・連続部分列が回文になるかどうかは両端を見ればいいのは、
　割と最近こどふぉでやったから覚えてた。(cf1881G)
　直前と2つ前と同じ要素を取らないようにすればいいので、3つ目以降は冪乗1発で済む。
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
    ll N, M;
    cin >> N >> M;

    mint ans = (mint)M * (M - 1) * pow(M - 2, N - 2, MOD);
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
