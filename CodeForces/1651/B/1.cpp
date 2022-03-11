/*
・きっちり自力AC！
・先頭に1入れて、以降は (aj-ai)*2 >= ai+aj が成り立つような最小のajをにぶたんして突っ込んだ。
　うまい規則がありそうだったけど、考えるよりにぶたん書いた。
　→ちゃんと式変形すると、3冪でOKみたいな話みたい。やっぱり。。
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
    ll N;
    cin >> N;

    const ll MX = 1e9;
    vector<ll> ans = {1};
    while (ans.size() < N) {
        ll prv = ans.back();
        ll nxt = bisearch_min(prv+1, MX+1, [&](ll m) {
            return (m-prv)*2 >= m+prv;
        });
        if (nxt > MX) {
            NO();
            return;
        }
        ans.eb(nxt);
    }
    YES();
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
