/*
・なんとか自力AC！
・LISに帰着
・操作を考えると、明らかにLISっぽい。けど素直にLISをやるとWA。
　Pに関する条件を考慮しないといけない。
・本当の得点として同値がダメなので、A[i]が嘘をついていない場合、
　A[i+1]は最低でもA[i]-1以下にする必要がある。同様に、
　一般化すると、A[i+x]は最低でもA[i]-x以下という条件にできる。
　これは予めA[i]+iとしておけば位置による違いを無くせて、
　A[i] <= A[i+1] という条件に落とせる。
　これの最大化であれば、同値OKのLISになるので、これが正直者の最大値。
　必要な答えは嘘つきの最小値なので上記値をNから引けばいい。
・もう1点ある。これだけだと、始まりがP超だったり途中が0未満になる列を許してしまう。
　A[i] > P-i や A[i] < N-1-i はどうやってもOKに含めないので、
　これらに当てはまるものは最初からLISの候補から除外しておく。
　特に、P超は気付いたんだけど、0未満になる条件でN-1-iはなかなか気付けなくて、
　ランダムテスト回したりでやっと気付けたので、ちゃんと粘って良かった。
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

#include "common/LIS.hpp"

void solve() {
    ll N, P;
    cin >> N >> P;
    auto A = LIST(N);

    vector<ll> B;
    rep(i, N) {
        A[i] += i;
        if (N-1 <= A[i] and A[i] <= P) {
            B.eb(A[i]);
        }
    }
    auto res = LIS(reversed(B), true);
    ll ans = N-res.size();
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
