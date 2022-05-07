/*
参考：https://twitter.com/shobonvip/status/1522623193877417984
　　　https://oeis.org/search?q=2%2C6%2C10%2C16%2C24&sort=&language=english&go=Search
・自力ならず。
・OEIS
・なんかきれいな漸化式になるんじゃないかなぁとか思ってこねくり回すも詰め切れず。
　TLで何人かOEISで通してるのを見たので、それで通した人結構多かったぽい…。
　最初5項{2,6,10,16,24}で調べるとそれっぽいのが出る。これのFORMULAの最初のをそのままDPにして、
　問題設定と合わせるために1項ずらす。これににぶたんすればOK。
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

vector<ll> dp(40000);
void prep() {
    rep(i, 1, 40000) {
        // https://oeis.org/A030511
        if (i%3 == 1) {
            dp[i] = 2 * (i-1)*(i-1) / 3;
        } else {
            dp[i] = 2 * i * (i-2) / 3;
        }
    }
    dp.erase(dp.begin());
    // print(dp.back());
}

void solve() {
    ll N;
    cin >> N;

    ll ans = bisect_left(dp, N);
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    prep();

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
