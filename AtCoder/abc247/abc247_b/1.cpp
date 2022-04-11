/*
・まじで危なかった。本日B～Eで最難まである。
・まず誤読。他の人とあだ名が被ったらNGなのかと思った。問題よく読もう…。
・で、コーナー。全部Counterして重複チェックだと、姓=名がいた時刺される。
・しょうがないので愚直2乗を書く。それでも条件チェック2つ要るし、
　Bにしてはまあまあむずくない？ってなった。まあでも最近だとこれはBか…。
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
    vector<string> S(N), T(N);
    rep(i, N) {
        cin >> S[i] >> T[i];
    }

    rep(i, N) {
        bool ok1 = true, ok2 = true;
        rep(j, N) {
            if (i == j) continue;
            if (S[i] == S[j] or S[i] == T[j]) {
                ok1 = false;
            }
            if (T[i] == S[j] or T[i] == T[j]) {
                ok2 = false;
            }
        }
        if (not ok1 and not ok2) {
            No();
            return;
        }
    }
    Yes();
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
