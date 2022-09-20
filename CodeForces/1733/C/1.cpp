/*
参考：https://twitter.com/kude_coder/status/1571903314698313728
・自力ならず。。
・こういうの見抜けない時はほんとに見抜けないよなぁ。
・全部同じ値にする方針でいける。まずA[0]と偶奇が等しい末尾要素を見つけておけば、
　そこより左でA[0]と偶奇が等しいものは(A[0]を含め)全てその末尾要素と同じ値にできる。(ここがむずい)
　で、次にA[0]を軸にして残りの偶奇が異なるものをA[0]と同じ値にしていく。(こっちは簡単)
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
    ll N;
    cin >> N;
    auto A = LIST(N);

    vector<pll> ans;
    ll j = -1;
    rep(i, N-1, -1, -1) {
        if (A[i]%2 == A[0]%2) {
            if (j == -1) {
                j = i;
            } else {
                // A[0]と偶奇が等しい末尾要素に合わせる
                ans.eb(i+1, j+1);
                A[i] = A[j];
            }
        }
    }
    rep(i, 1, N) {
        if (A[i]%2 != A[0]%2) {
            // A[0]に合わせる
            ans.eb(1, i+1);
            A[i] = A[0];
        }
    }
    UNIQUE(A);
    assert(A.size() == 1);
    print(ans.size());
    print(ans, '\n');
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
