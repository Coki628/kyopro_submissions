/*
・しばらく考えて方針は立つも間に合わず、終了後20分くらいで自力AC。
・等差数列
・差分に注目すると2とM*2なので、これを使って縦横それぞれで等差数列の和。
　市松も2つに分けたので計4回やる。添字がとてもつらい。
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

#include "numbers/arithmetic_sequence_sum.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;

    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;

        ll hlen = b - a + 1;
        ll wlen = d - c + 1;
        if ((a+c)%2 == 0) {
            ll base1 = (a-1)*M + c;
            mint sm11 = arithmetic_sequence_sum<mint>(base1, M*2, ceil(hlen, 2LL))*ceil(wlen, 2LL);
            mint sm12 = arithmetic_sequence_sum<mint>(0, 2, ceil(wlen, 2LL))*ceil(hlen, 2LL);
            ll base2 = (a-1+1)*M + c+1;
            mint sm21 = arithmetic_sequence_sum<mint>(base2, M*2, ceil(hlen-1, 2LL))*ceil(wlen-1, 2LL);
            mint sm22 = arithmetic_sequence_sum<mint>(0, 2, ceil(wlen-1, 2LL))*ceil(hlen-1, 2LL);
            mint res = sm11 + sm12 + sm21 + sm22;
            print(res);
        } else {
            ll base1 = (a-1+1)*M + c;
            mint sm11 = arithmetic_sequence_sum<mint>(base1, M*2, ceil(hlen-1, 2LL))*ceil(wlen, 2LL);
            mint sm12 = arithmetic_sequence_sum<mint>(0, 2, ceil(wlen, 2LL))*ceil(hlen-1, 2LL);
            ll base2 = (a-1)*M + c+1;
            mint sm21 = arithmetic_sequence_sum<mint>(base2, M*2, ceil(hlen, 2LL))*ceil(wlen-1, 2LL);
            mint sm22 = arithmetic_sequence_sum<mint>(0, 2, ceil(wlen-1, 2LL))*ceil(hlen, 2LL);
            mint res = sm11 + sm12 + sm21 + sm22;
            print(res);
        }
    }
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
