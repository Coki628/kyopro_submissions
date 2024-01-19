/*
・きっちり自力AC！
・書いてある通りに集計する。
　indexのリスト入れとけば、誰にスコアあげるかやりやすい。
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
    ll L = 3;
    ll N;
    cin >> N;
    auto S = listnd(L, N, string());
    rep(i, L) {
        cin >> S[i];
    }

    map<string, vector<ll>> C;
    rep(i, L) {
        rep(j, N) {
            C[S[i][j]].eb(i);
        }
    }
    vector<ll> ans(L);
    for (auto& [s, vec] : C) {
        if (vec.size() == 1) {
            ans[vec[0]] += 3;
        } else if (vec.size() == 2) {
            ans[vec[0]]++;
            ans[vec[1]]++;
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
