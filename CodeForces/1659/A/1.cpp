/*
・なんとか自力AC…。
・なんか植木算？みたいなやつ。うまく割り算すれば一撃、なのは分かってても、
　中受未履修なのでこういうの全く染みついてなくてつらめ。
・辿り着いたお気持ちとしては、Bを区切りにしてB+1箇所に均等にRを分けると考えると、
　r/(b+1)で各区画にRを何個置けばいいか分かる、みたいになった。
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
    ll N, r, b;
    cin >> N >> r >> b;

    auto [di, mo] = divmod(r, b+1);
    string ans;
    rep(_, b) {
        ans += string(di, 'R');
        if (mo) {
            ans += 'R';
            mo--;
        }
        ans += 'B';
    }
    ans += string(di, 'R');
    if (mo) {
        ans += 'R';
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
