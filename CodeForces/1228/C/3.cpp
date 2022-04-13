/*
・自力AC！
・2年半前くらいに分かんなくて放置したやつ、
　今見たら解けそうかもってなったからやってみた。解けて嬉しい。
・素因数分解、主客転倒、オーバーフロー
・とりあえず問題設定がややこしい。定義された関数3つくらい出てくる。
　簡単に言うと、1~N回の関数fの中で、xの各素因数について関数gをやってね、みたいな感じ。
　で、これで関数f,gともに出た答えを総積してるので、順番を入れ替えていいのかな、となる。
　入れ替えていいなら、各素因数にやるを外側にした方が、1~Nより数が明らかに少ないので
　状態をまとめやすそうだよね、となる。これで、各素因数について、
　1~Nまでの数に含まれるその素因数の個数の総和みたいのを求めればよくなったので、
　だいぶ見通しがよくなった。単体のある数についてのある素因数の個数は割り算一発だけど、
　1~Nまでなのでどうしようかとなるが、ちょっと手元で試すと、
　割る数に使う素因数を冪乗していくと都合が良さそうな形が見える。
　ここまで整えば、後は実装に落とし込むだけ。
・冪乗していく件でオーバーフローがあるので対策する。
　サンプルにあって優しかったけど、なかったら分かんなくて死んでたかも…。
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
    ll x, N;
    cin >> x >> N;

    mint ans = 1;
    for (auto [k, _] : factorize(x)) {
        ll cur = k, cnt = 0;
        while (N/cur > 0) {
            cnt += N / cur;
            if (mul_overflow(cur, k)) break;
            cur *= k;
        }
        ans *= pow(k, cnt, MOD);
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
