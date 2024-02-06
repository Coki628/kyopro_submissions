/*
・Div.3残埋め
・自力AC！やったね。
・ソート、indexを足す、にぶたん
・弱い方から優先的に取りたいのでソートはするとして、
　1つ進める毎に自分は+1なので、これは数列側に予めindexを足しておけば、
　自身の変化の分をないものとみなせる。
　そのままやるとマイナスとかになりうるので適当に累積maxはしておく。
　これさえ準備できれば、後は現状どこまで勝てるかでその数列をにぶたんして、
　次のやつに勝てる直前か、目標値yに到達できる直前までのどちらかまで、
　現状の繰り返しを何回やるかのにぶたんでまとめて進めればいい。
　最後にループを出たら端数を足せばOK。
・ちょっと細部詰めには苦労したけど、ちゃんと通せて良かった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N, x, y;
    cin >> N >> x >> y;
    auto A = LIST(N);

    sort(ALL(A));
    auto B = A;
    rep(i, N) {
        B[i] -= i;
    }
    rep(i, 1, N) {
        chmax(B[i], B[i - 1]);
    }
    A.eb(INF);
    ll ans = 0, cur = x;
    while (1) {
        ll okcnt = bisect_right(B, cur);
        ll ngcnt = N - okcnt;
        if (cur + okcnt >= y) break;
        // これ以上進めない
        if (ngcnt >= okcnt) {
            print(-1);
            return;
        }
        ll add = okcnt - ngcnt;
        // 次の値に行くまでかyの直前までやる
        ll nxneed = A[okcnt];
        ll i = bisearch_min(-1, INF, [&](ll m) {
            if (mul_overflow(add, m)) {
                return true;
            }
            ll nxval = cur + add * m + okcnt;
            if (nxval >= nxneed) {
                return true;
            } else if (nxval >= y) {
                return true;
            } else {
                return false;
            }
        });
        cur += add * i;
        ans += N * i;
    }
    ans += (y - cur);
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
