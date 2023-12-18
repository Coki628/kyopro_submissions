/*
・自力ならず。これは見えなかった。。
・3つ組、桁和、桁毎に独立
・実は繰り上がりが1つでもあると、dsm(a)+dsm(b)+dsm(c)>dsm(n)となってしまうとのこと。
　言われてみると確かに、だけど。。それで繰り上がらないケースのみを考えると、
　じゃあ桁毎に独立でOKだね、となる。繰り上がらないのであれば、
　和と桁和は常に等しいはずなので、桁毎に足して全桁掛けるだけ。
　途中でもう、こんなん無理だろ、ってなっちゃったけど、
　そこをもう一歩考えてちゃんと解けるようにしたいねー。。
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

    ll ans = 1;
    for (auto s : S) {
        ll d = toint(s);
        ll cnt = 0;
        rep(a, d + 1) {
            rep(b, d + 1) {
                ll c = d - a - b;
                if (c >= 0) cnt++;
            }
        }
        ans *= cnt;
    }
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
