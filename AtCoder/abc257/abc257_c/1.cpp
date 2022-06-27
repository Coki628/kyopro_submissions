/*
・きっちり自力AC！
・2つに分けてソートしてにぶたん。どこを境目にするか全部見る。
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

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;
    auto A = LIST(N);

    if (count(ALL(S), '0') == N or count(ALL(S), '1') == N) {
        print(N);
        return;
    }

    vector<ll> B1, B2;
    rep(i, N) {
        if (S[i] == '0') {
            B1.eb(A[i]);
        } else {
            B2.eb(A[i]);
        }
    }
    sort(ALL(B1));
    sort(ALL(B2));
    ll M1 = B1.size();
    ll M2 = B2.size();
    ll ans = -INF;
    rep(i, M2) {
        ll cnt = M1 - bisect_left(B1, B2[i]);
        chmax(ans, N-i-cnt);
    }
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
