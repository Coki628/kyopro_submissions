/*
・自力ならず。。
・連続部分列、区切る、最大化、区間和、suffix
・自分ではまず区切るDPの方針になって、どうやっても今の個数の情報が必要だよね、
　となり詰まってしまった。後は思いつきでいい加減な貪欲試したくらい。
・実はsuffixで正になるものを貪欲に取ればそれが正解。
　言われると確かに、suffixをたくさん取れば配列の後ろの方ほど重みが増すので、
　今回の区切る度に区間和の係数が+1される条件にも合うように思える。
　がしかし思いつくだろうか。普通に考えると多分自分じゃ思いつかない。
　どう考えれば少しはマシに気付きやすくなるか少し考えた。
　区間を横と区切った回数を縦みたいな2次元を考える。
　すると、この問題は素直に考えるとこれに縦に切れ目を入れる問題。
　でもここで主客転倒っぽく、横(水平方向)に切れ目を入れて同じことをしようとすると、
　これはsuffix区間和を集める問題になる。
　とまあ、これが今の所一番マシにしっくり来たので今はこう考えておく。
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
    vector<ll> A(N);
    cin >> A;

    Accumulate<ll> acc(A);
    ll ans = acc.query(0, N);
    rep(i, 1, N) {
        if (acc.query(i, N) > 0) {
            ans += acc.query(i, N);
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
    while (T--) solve();

    return 0;
}
