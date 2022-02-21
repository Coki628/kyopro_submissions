/*
・きっちり自力AC！
・0,1,Nが'0'はNGとしてそれ以外は、[0,要らない,1,要る]って並べる。
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
    string S;
    cin >> S;

    if (S[0] == '0' or S[1] == '0' or S[N] == '0') {
        No();
        return;
    }

    vector<ll> need, noneed;
    rep(i, 2, N) {
        if (S[i] == '1') {
            need.eb(i);
        } else {
            noneed.eb(i);
        }
    }

    vector<ll> ans;
    ans.eb(0);
    for (auto a : noneed) {
        ans.eb(a);
    }
    ans.eb(1);
    for (auto a : need) {
        ans.eb(a);
    }
    Yes();
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
