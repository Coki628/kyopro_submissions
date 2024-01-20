/*
・きっちり自力AC！
・各文字列の文字数は最大8と少ない。
　区切り位置全探索でa,bに分けて、そういう文字列があるかチェックすればOK。
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
    vector<string> S(N);
    cin >> S;

    set<string> se;
    rep(i, N) {
        se.insert(S[i]);
    }
    string ans(N, '0');
    rep(i, N) {
        rep(j, 1, S[i].size()) {
            auto a = S[i].substr(0, j);
            auto b = S[i].substr(j);
            if (se.count(a) and se.count(b)) {
                ans[i] = '1';
            }
        }
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
