/*
・きっちり自力AC！
・1つ先と比較して小さければ2つに、同値なら自分より先の結果と合わせる。
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
    string S;
    cin >> S;
    ll N = S.size();

    vector<bool> doubled(N);
    rep(i, N-2, -1, -1) {
        if (S[i] < S[i+1]) {
            doubled[i] = true;
        } elif (S[i] == S[i+1]) {
            doubled[i] = doubled[i+1];
        }
    }
    string ans;
    rep(i, N) {
        if (doubled[i]) {
            ans += string(2, S[i]);
        } else {
            ans += S[i];
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
    rep(i, 1, T+1) {
        cout << "Case #" + tostr(i) + ": ";
        solve();
    }
    return 0;
}
