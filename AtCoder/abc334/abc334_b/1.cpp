/*
・ループ回せない制約でびびった。こどふぉDiv.2かと思った。
　負数に下駄履かせてaずらせば、区間のmの倍数を数えるよく見るあれに帰着できる。
　なんだけど、制約10^18が結構C++泣かせで雑に足してオーバーフローやだなぁみたいな気持ちに。
　で1WA食らってちゃんと考えて、2*10^18足して最大3*10^18になっても、
　llは9*10^18くらいまで耐えるはずだからOKだろうとして、無事AC。
・これをループ回せない制約でABCのBに置くのはちょっと酷なんじゃないかと思った。
　まあ算数強ければ秒殺なんだろうけどさ。
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
    ll a, m, l, r;
    cin >> a >> m >> l >> r;

    l += INF * 2, r += INF * 2, a += INF * 2;
    a %= m;
    l -= a;
    r -= a;
    ll ans = r / m - (l - 1) / m;
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
