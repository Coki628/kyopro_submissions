/*
・自力AC
・とりあえず数が合わなければ何やっても無理だし、
　数が合ってて1つでも重複があれば、そこをスワップで偶奇合わせできるから
　何が来てもOK。これを除いて考えてみる。
・残りを検討すると、偶奇合わないやつはダメそうだねってなる。
　で、位置の違う所が2つあるやつは1回スワップ、つまり奇数回スワップでしか
　辿り着けなさそうだから無理だねってなる。
・それ以外はもうOKなんじゃん？とお気持ちでぶん投げて無事AC。。
・公式解説より。この偶奇は、転倒数の偶奇で表されるらしく、偶置換と奇置換と言うらしい。
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
    ll N = 3;
    auto S = LIST<char>(N);
    auto T = LIST<char>(N);

    if (sorted(S) != sorted(T)) {
        No();
        return;
    }
    auto tmp = S;
    UNIQUE(tmp);
    if (tmp.size() <= 2) {
        Yes();
        return;
    }

    ll diff = 0;
    rep(i, N) {
        if (S[i] != T[i]) {
            diff++;
        }
    }
    if (diff == 2) {
        No();
    } else {
        Yes();
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
