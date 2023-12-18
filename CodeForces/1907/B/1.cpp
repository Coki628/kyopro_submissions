/*
・きっちり自力AC！
・大文字小文字別々のスタックで管理して、最後にくっつけて操作のindexでソート。
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
    ll N = S.size();

    vector<pair<int, char>> st1, st2;
    rep(i, N) {
        if (S[i] == 'b') {
            if (st1.size()) {
                st1.pop_back();
            }
        } else if (S[i] == 'B') {
            if (st2.size()) {
                st2.pop_back();
            }
        } else if (islower(S[i])) {
            st1.eb(i, S[i]);
        } else {
            st2.eb(i, S[i]);
        }
    }

    vector<pair<int, char>> vec;
    for (auto a : st1) vec.eb(a);
    for (auto a : st2) vec.eb(a);
    sort(ALL(vec));
    string ans;
    for (auto a : vec) {
        ans += a.second;
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
