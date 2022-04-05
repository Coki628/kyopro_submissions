/*
参考：https://rikeilabo.com/formula-and-transformation-of-logarithm#33
・なんとか自力AC。大変だった。
・誤差、オーバーフロー
・PythonのDecimalで叩こうと思ったら通らず…。大人しく式変形を検討。
　色々探し回ってやっとお目当ての式変形を見つける。
　がしかしでかい。c^b = (10^18)^(10^18)とか無理。でもよく見ると、
　c = 1の時はbc = 1で確定なので常にNoだし、c >= 2は値が早々にでかくなるのが分かる。
　比較するaの最大値は10^18なので、これよりでかくなりそうならYesとする。
　ここからオーバーフローでさらに1ペナ…。こういうのほんと疲れるわ。
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
    ll a, b, c;
    cin >> a >> b >> c;

    // blogc = log(c^b)

    // ll bc = pow(c, b);
    // if (a < bc) {
    //     Yes();
    // } else {
    //     No();
    // }

    if (c == 1) {
        // bc = 1, a >= bc
        No();
        return;
    }
    ll bc = 1;
    rep(_, b) {
        if (mul_overflow(bc, c)) {
            Yes();
            return;
        }
        bc *= c;
        if (a < bc) {
            Yes();
            return;
        }
    }
    No();
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
