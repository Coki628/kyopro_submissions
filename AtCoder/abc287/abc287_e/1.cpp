/*
・終了約15分後にAC。。時間内に解きたかった…。
・ソートすると前後見ればOK、に気付いたのが終了直後くらいで。
　それが分かれば、1回のLCP判定ロリハとかで高速にやれば問題ない。
・後からTLとか見てたけど、ロリハ要らないぽい。
　総文字列長が50万だから、全体でも確かにそれの線形で済むね、多分…。
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

#include "string/RollingHash.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<pair<string, int>> S(N);
    RollingHash rh;
    vector<vector<uint64_t>> table(N);
    rep(i, N) {
        cin >> S[i].first;
        S[i].second = i;
        table[i] = rh.build(S[i].first);
    }
    sort(ALL(S));

    vector<int> ans(N);
    rep(i, N) {
        auto [s1, j1] = S[i];
        if (i > 0) {
            auto [s2, j2] = S[i - 1];
            chmax(ans[j1], rh.lcp(table[j1], 0, s1.size(), table[j2], 0, s2.size()));
        }
        if (i < N - 1) {
            auto [s2, j2] = S[i + 1];
            chmax(ans[j1], rh.lcp(table[j1], 0, s1.size(), table[j2], 0, s2.size()));
        }
    }
    print(ans, '\n');
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
