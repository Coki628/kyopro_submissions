/*
・きっちり自力AC！
・mapとかで個数管理しながら、別変数で1個以上あるか管理するやつ。
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
    ll N, T;
    cin >> N >> T;

    vector<ll> A(N);
    map<ll, ll> C;
    C[0] = N;
    ll cnt = 1;
    rep(i, T) {
        ll a, b;
        cin >> a >> b;
        a--;
        C[A[a]]--;
        if (C[A[a]] == 0) cnt--;
        A[a] += b;
        C[A[a]]++;
        if (C[A[a]] == 1) cnt++;
        print(cnt);
    }
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
