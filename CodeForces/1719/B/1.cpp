/*
・なんとか自力AC…。本日のボトルネック。
・状況を整理すると、各ペアについて
　・a+kが4の倍数
　・bが4の倍数
　・a+kが偶数でbも偶数
　のいずれかを満たす必要がある。
　mod 4で考えると、4つの要素のうち0がある方のペアは相方が何でもよく、
　そうでない方はKの値に合わせて、a,bにちょうどいいものを与える必要がある。
　これはKが0だと無理で、そうでなければいける。(ソース内コメントも参照)
　あとNがmod 4で2だったら最後に2つ余るので、そこは場合分けして調整。
・こういうの、自分的にはすごく考察頑張って解くんだけど、
　まじでみんな速いんだよね…。今日も通した時もう7000人とか通しててまじかよってなった。
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
    ll N, K;
    cin >> N >> K;

    vector<pll> ans;
    if (K%4 == 0) {
        NO();
    } else {
        YES();
        // K=2
        if (K%4 == 2) {
            rep(a1, 1, N-1, 4) {
                ll a2 = a1 + 1;
                ll a3 = a1 + 2;
                ll a0 = a1 + 3;
                // (2, any), (any, 0)
                ans.eb(a2, a1);
                ans.eb(a3, a0);
            }
            if (N%4 == 2) {
                // (2, any)
                ans.eb(N, N-1);
            }
        // K=1,3
        } else {
            rep(a1, 1, N-1, 4) {
                ll a2 = a1 + 1;
                ll a3 = a1 + 2;
                ll a0 = a1 + 3;
                // (1, 2), (any, 0)
                ans.eb(a1, a2);
                ans.eb(a3, a0);
            }
            if (N%4 == 2) {
                // (1, 2)
                ans.eb(N-1, N);
            }
        }
        print(ans, '\n');
    }
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
