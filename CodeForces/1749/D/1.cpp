/*
参考：https://twitter.com/4yAobz/status/1583137082716717060
・自力ならず。やっぱ整数論数え上げ苦手だな…。
・素数判定、互いに素、余事象、数え上げ
・まず、題意のambiguousな通り数よりもambiguousではない通り数のが数えやすそう。(これは思った。)
　で、ambiguousではない列がどういったものかというと、列Bが[1,1,1..]となるような列Aになる。
　確かに[1,1,1..]は任意の列で通用するし、それ以外のパターンができてしまった時点でambiguousなんだけど、
　やってる時はそういう確証が持てなくて前に進めなかった。
　で、この列Bとなるような列Aはどういったものがあるかというと、
　どんな順序で抜かれるにしろ、どの値も先頭に来るまで抜かれないようにする必要があって、
　このためにはi番目の要素は[2,i]の整数全てと互いに素ではない必要がある。
　で、これはそこまでに出てきた素因数が全部含まれるといい。
　(LCMっぽいけど、LCMって言うと、素因数の個数も含めて全部カバーしてるから少し違う。
　今回は素因数の種類だけ網羅してればいい。)
　よってやることは1～Nで素数判定しながら新たな素因数を追加していって、
　それを元にその位置に置ける通り数を求めて、それをありうる列全体から引く。
　列の長さ1～Nまで全部見ての総和なので、各iで長さiの列の通り数を求めて答えに足し込んでいく。
　素因数をたくさん掛けていくと値が大きくなるので、そこは適宜枝刈り。以降引く数は0になる。
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

#include "numbers/Eratosthenes.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;

    Eratosthenes era(N);
    mint ans = 0, sub = 1, total = 1;
    // p := [2,i]の整数全てと、互いに素でない最小の値
    ll p = 1;
    rep(i, 1, N+1) {
        if (p <= M and era.is_prime(i)) {
            p *= i;
        }
        // M以下のpの倍数の個数
        ll cnt = M / p;
        // 長さiの列でambiguousではない通り数
        sub *= cnt;
        // 長さiの列全体の通り数
        total *= M;
        ans += total - sub;
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
