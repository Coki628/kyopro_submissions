/*
・自力AC。でもこれ時間かかった。。
・どうやったらもっと手早く片付いたか考えると、
　多分尺取りっぽくしてしまった所をにぶたんっぽくして、
　比較のことは同時に考えずに、最後まで行ってから
　全体が一致したかチェック、とかしたら少しは思考リソース減らせたかなぁ。
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

    if (A[0] != N) {
        NO();
        return;
    }

    auto B = reversed(A);
    ll j = 0;
     rep(i, 1, N) {
        while (j < N and B[j] <= i) {
            j++;
        }
        ll blen = N - j;
        if (blen != A[i]) {
            NO();
            return;
        }
    }
    YES();
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
