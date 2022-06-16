/*
・自力AC。
・実験エスパー
・やってみると、Nが素数だとやたら少ないし、合成数っぽいと多い。
　値も見ると、なんかNの約数っぽいのがたくさん使われてる。
　で、約数列挙と照らし合わせると、a,bどちらかがNの約数なら良さそう。
　Nはダメみたいなので約数の個数から-1して、a,b逆もあるので*2して、
　Nが偶数だとa=bがあるのでさらに-1。これで通った。
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

void solve() {
    ll N;
    cin >> N;

    // debug(divisors(N));
    // rep(a, 1, N) {
    //     ll b = N - a;
    //     bool res = gcd(a, b) + lcm(a, b) == N;
    //     if (res) {
    //         debug(mkp(a, b));
    //     }
    // }
    // →(約数の個数-1)*2 if N%2 == 0 then --

    ll ans = (divisors(N).size()-1)*2;
    if (N%2 == 0) ans--;
    print(ans);
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
