/*
参考：https://img.atcoder.jp/agc008/editorial.pdf
・dojo set_f_2_2
・自力ならず。
・構築、前後から貪欲
・比較的近い方針を取っていたけど詰め切れず。
　前だけでなく、後ろからもで両方貪欲するって発想にはいかなかった。
・なんていうか、AGCだよな～って感じの問題よね。アルゴ力とかより発想力が試される。
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
    auto A = LIST(N);
    rep(i, N) A[i]--;

    ll NN = N * N;
    vector<ll> ans(NN, -1);
    vector<pll> AI;
    rep(i, N) {
        ans[A[i]] = i;
        AI.eb(A[i], i);
    }
    sort(ALL(AI));

    ll k = 0;
    rep(j, N) {
        auto [a, i] = AI[j];
        rep(_, i) {
            while (ans[k] != -1) k++;
            ans[k] = i;
        }
        if (k > a) {
            No();
            return;
        }
    }
    k = NN - 1;
    rep(j, N-1, -1, -1) {
        auto [a, i] = AI[j];
        rep(_, N-i-1) {
            while (ans[k] != -1) k--;
            ans[k] = i;
        }
        if (k < a) {
            No();
            return;
        }
    }

    rep(i, NN) ans[i]++;
    Yes();
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
