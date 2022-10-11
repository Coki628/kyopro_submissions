/*
参考：https://twitter.com/kude_coder/status/1578745450173460486
・自力ならず。でも結構惜しい所まで行ってた。時間あればな…。
・差分、約数列挙、過半数、乱択
・まずmodを合わせるためには、値そのものではなく差分に注目する。
　差分が同じ所があれば、その差分がmodだった時同じ値になるし、
　もう少し見ると、その約数でも同じになることが分かってくる。
　で、これを全ペアとか見ると、いくら2乗が間に合う制約でも、
　その内側で約数列挙毎回やってたらさすがにTLEは不可避。(ここまでやってた)
　ここで過半数が条件であることに注目する。過半数で条件を満たさなければいけないので、
　適当に2つ選んだ時にもかなりの確率で条件を満たす必要がある。(実際1/4らしい)
　これをうまく利用して、適当に2つ選んだペアについてチェックするのを時間いっぱい繰り返すと、
　条件を満たす値があればほぼ確実に見つけられるし、なければないと判断できる。
・過半数ってキーワードを見た時、乱択を少し考えたので、
　もう少し色々考える時間があれば正解の方針に辿り着いた可能性はある。残念。
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

#include "common/Timer.hpp"
#include "common/randrange.hpp"

void solve() {
    Timer timer;
    ll N;
    cin >> N;
    auto A = LIST(N);

    const int TL = 1800;
    while (timer.get_elapse() < TL) {
        ll i = randrange(0, N);
        ll j = i;
        while (j == i) {
            j = randrange(0, N);
        }
        ll d = abs(A[i]-A[j]);
        for (auto mod : divisors(d)) {
            if (mod <= 2) continue;
            vector<ll> B(N);
            rep(i, N) {
                B[i] = A[i] % mod;
            }
            if (most_common(Counter(B))[0].first > N/2) {
                print(mod);
                return;
            }
        }
    }
    print(-1);
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
