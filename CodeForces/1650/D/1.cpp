/*
・自力AC。
・サイクルシフト
・後から貪欲に。前半切って後半くっつけてみたいのvectorだとやりづらくてpython使いたくなった。
　vectorにサイクルシフトの関数あったのは思い出したけど、名前出てこなかったのと、
　それなりに扱いにくかったような覚えがあったので、分解と連結で済ませてしまった。
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
    auto A = LIST(N);
    rep(i, N) A[i]--;

    vector<ll> ans(N);
    rep(i, N-1, -1, -1) {
        rep(j, i-1, -1, -1) {
            if (A[j] == i) {
                ans[i] = j+1;
                auto v1 = vector<ll>{A.begin()+j+1, A.begin()+i+1};
                auto v2 = vector<ll>{A.begin(), A.begin()+j+1};
                auto v3 = vector<ll>{A.begin()+i+1, A.end()};
                A.clear();
                for (auto a : v1) A.eb(a);
                for (auto a : v2) A.eb(a);
                for (auto a : v3) A.eb(a);
                break;
            }
        }
    }
    vector<ll> expected(N);
    iota(ALL(expected), 0);
    assert(A == expected);
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
