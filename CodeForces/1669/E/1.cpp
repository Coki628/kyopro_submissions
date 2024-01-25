/*
・きっちり自力AC！
・ペア数え上げ、重複を引く
・1文字目、2文字目、全体で同じものをそれぞれ集計しておいて、
　片方合うやつ足して全体合うやつ引くみたいにする。
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

    map<char, ll> C1, C2;
    map<string, ll> C3;
    for (auto &s : S) {
        C1[s[0]]++;
        C2[s[1]]++;
        C3[s]++;
    }

    ll ans = 0;
    for (auto &s : S) {
        ans += C1[s[0]] + C2[s[1]] - C3[s] * 2;
    }
    ans /= 2;
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
