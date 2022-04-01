/*
・なんとか自力AC。今回一番危なかった。。
・1が1つでもあればだいたい何でもできる。
　最初気付かなくてめっちゃ算数頑張ろうとしてた。
　後から戻ってきて、図とか書いてて何とか見えてよかった…。
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
#include "template.hpp"

void solve() {
    ll a, b;
    cin >> a >> b;

    if (a == 0) {
        print(1);
    } else {
        print(a+b*2+1);
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
