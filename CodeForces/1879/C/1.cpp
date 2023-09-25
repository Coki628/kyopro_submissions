/*
・きっちり自力AC！
・ランレングス、組み合わせ
・操作は各0か1の塊から1個だけ残すのが最善。
　ランレングスしてnCr(cnt,cnt-1)、最後に順序付けのため操作回数の階乗。
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
    string S;
    cin >> S;
    ll N = S.size();

    ModTools<mint> mt(N);
    ll ans1 = 0;
    mint ans2 = 1;
    for (auto [c, cnt] : RLE(S)) {
        ans1 += cnt - 1;
        ans2 *= mt.nCr(cnt, cnt - 1);
    }
    ans2 *= mt.fact(ans1);
    print(mkp(ans1, ans2));
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
