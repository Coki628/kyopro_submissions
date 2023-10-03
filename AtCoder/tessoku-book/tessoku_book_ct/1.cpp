/*
・自力AC！ちょっと考えるやつ出てきた。
・2乗の区間DP、回文
・左右端からそれぞれ使う/使わないを決めていく。
　遷移はLCSのDPみたいな感じにする。
　どっかのこどふぉで類題を解いたことがあると思う。
　(その時は確か木上でやるとかそんな感じでもう一段階難しかった。)
・ちなみに公式解確認したら、逆に真ん中から広げる方針で解いてた。
　確かにそれでも問題なさそうだね。
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
    ll N;
    cin >> N;
    string S;
    cin >> S;

    auto memo = listnd(N, N + 1, -1LL);
    auto rec = [&](auto &&f, ll l, ll r) -> ll {
        if (l >= r) {
            return 0;
        }
        if (l + 1 == r) {
            return 1;
        }
        if (memo[l][r] != -1) {
            return memo[l][r];
        }
        ll res = 0;
        // lを使わない
        chmax(res, f(f, l + 1, r));
        // r-1を使わない
        chmax(res, f(f, l, r - 1));
        // lとr-1を使う
        if (S[l] == S[r - 1]) {
            chmax(res, f(f, l + 1, r - 1) + 2);
        }
        return memo[l][r] = res;
    };
    ll ans = rec(rec, 0, N);
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
