/*
・E8さん本より
・きっちり自力AC！
・高速約数列挙
・GCDとなりうるためには、その数の約数であることは必須で、
　ペアを作るので、約数を値毎に集計して、2回以上出現した値があれば、
　それはペアにできることになる。
　これを確認するために、区間[a,b]全ての値で約数列挙をする必要があって、
　この全列挙はエラトステネスで前計算すると√じゃなくてlogでできるようになって速い。
　今回の最大値が20万で、速度比較してみたけど、√かかる方だと0.51秒、
　前計算する方だと0.06秒になってやっぱり全然違った。
・でもこれ絶対想定解じゃなさそう。灰diffで高速約数列挙なんてやる訳ない。。
　(ちなみにこれ参戦時自力ACできなかったらしくて、悲しい。)
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

#include "numbers/Eratosthenes.hpp"

Eratosthenes era(200000);

void solve() {
    ll a, b;
    cin >> a >> b;

    vector<ll> C(b+1);
    rep(i, a, b+1) {
        for (auto div : era.divisors(i)) {
            C[div]++;
        }
    }
    ll ans = 1;
    rep(i, b+1) {
        if (C[i] >= 2) {
            chmax(ans, i);
        }
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
