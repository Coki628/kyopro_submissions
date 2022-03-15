/*
・dojo set_e_5_e
・きっちり自力AC！
・更新は逆操作
・逆操作で、できる所から順に埋めていく。埋めた所からなるべく前後に伸ばす。
　これだけだとサンプル落ちて、何かと思ったら両側から埋められたGが塗られず残ってた。
　サンプルにあったからすぐ対応したけど、なかったら結構悩んだかも…。
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

    vector<ll> ok(N);
    rep(i, N-2) {
        if (S.substr(i, 3) == "RGB") {
            ok[i] = ok[i+1] = ok[i+2] = 1;
            ll j = i-1;
            while (j >= 0) {
                if (j >= 0 and S[j] == 'R') {
                    ok[j] = 1;
                    j--;
                } elif (j >= 1 and S.substr(j-1, 2) == "RG") {
                    ok[j-1] = ok[j] = 1;
                    j -= 2;
                } else {
                    break;
                }
            }
            j = i+3;
            while (j < N) {
                if (j < N and S[j] == 'B') {
                    ok[j] = 1;
                    j++;
                } elif (j < N-1 and S.substr(j, 2) == "GB") {
                    ok[j+1] = ok[j] = 1;
                    j += 2;
                } else {
                    break;
                }
            }
        }
    }
    rep(i, 1, N-1) {
        if (S[i] == 'G' and not ok[i] and ok[i-1] and ok[i+1]) {
            ok[i] = 1;
        }
    }
    if (sum(ok) == N) {
        Yes();
    } else {
        No();
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
