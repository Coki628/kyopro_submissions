/*
・自力AC
・とりあえず、or演算した時にaがbの部分集合になっていればそこで終わる。
　要素の最大値は100万なので1ずつ増やしていっても全部見れる。
　できそうなのは、aを増やしてorするか、bを増やしてorするか。
　それぞれを中途半端に増やすのが最善のがあったら破綻するんだけど、
　後はこんなん、間に合うのはこうするくらいしか思いつかん、の気持ちでやった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    ll a, b;
    cin >> a >> b;

    ll cnta = 0, cntb = 0;
    auto cur = a;
    while ((cur|b) != b) {
        cur++;
        cnta++;
    }
    if (cur != b) cnta++;
    cur = b;
    while ((a|cur) != cur) {
        cur++;
        cntb++;
    }
    if (a != cur) cntb++;
    ll ans = min(cnta, cntb);
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
