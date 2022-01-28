/*
参考：https://twitter.com/recuraki/status/1486743437982703618
・自力ならず。。これはやばかった。
・とりあえず自分より後ろしか変更できないので、最終的に末尾要素に全部合わせることになる。
　見やすさのためにリバースはしといた方が良さそう。それで何か
　dp[i] := i番目まで最後(最初)の値と合わせた時の最小操作回数
　みたいなDPを目指したら破滅した…。
・多分、考えてたよりずっと単純で良くて、1つ変更が必要な要素が見つかったら、
　それより手前を全部使ってなるべく長い区間を変更した方が得。
　一番長い区間でやるより短くすることに得はない(んだと思う)ので、
　特に状態は持たずに前に突き進んでいけばいい。
・まあ答え聞いた後なら何とでも言えるんだけどね。。
　自力で貪欲でいいって判断を自信持って下すのは難しい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

    reverse(ALL(A));
    ll ans = 0;
    ll i = 0;
    while (i < N) {
        if (A[i] == A[0]) {
            i++;
        } else {
            ans++;
            i += i;
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
