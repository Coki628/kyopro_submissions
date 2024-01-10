/*
・きっちり自力AC！
・後ろから見ると、やりやすくなる。
　1文字目以外で子音が出てきたら区切る。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N;
    cin >> N;
    string S;
    cin >> S;

    string vow = "ae", con = "bcd";
    vector<string> vec;
    string cur;
    rep(i, N - 1, -1, -1) {
        if (cur.size() > 0 and count(ALL(con), S[i])) {
            cur += S[i];
            reverse(ALL(cur));
            vec.pb(cur);
            cur = "";
        } else {
            cur += S[i];
        }
    }
    if (cur.size()) vec.eb(cur);
    reverse(ALL(vec));
    auto ans = join(vec, ".");
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
