/*
・自力ならず。。
・2冪とかフィボナッチとか考えたけど、たった3要素で網羅とか無理じゃね？ってなってた。
　あと乱択でうまいこと当たんないかなとか考えたり。決してそんなことなかった。。
・結局、6桁を2桁ずつ担当させて100進数、みたいな感じにすると良かったんだって。
・いやぁ、これはまじでARCでいいでしょって感じだよね…。
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

void solve() {
    ll W;
    cin >> W;

    vector<ll> ans;
    rep(i, 1, 100) {
        ans.eb(i);
    }
    rep(i, 100, 10000, 100) {
        ans.eb(i);
    }
    rep(i, 10000, 1000000, 10000) {
        ans.eb(i);
    }
    print(ans.size());
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
