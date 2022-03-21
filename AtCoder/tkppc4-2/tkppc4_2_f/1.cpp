/*
・なんとか自力AC。
・ずっと考えてたやつ、通した。
・とりあえず端から考えると、そこが例えば2残っていたら、
　そこを端とした山なりの区間操作みたいのを2回やらないといけない。
　同様に次の位置でも残ってる値に応じて操作回数は一意に。
　愚直に操作をするとN^2だが、ある値が大きかったり、区間長が長かったりすると、
　早々に無理な場所が確定してくるっぽいと信じると、枝刈りで通る。。
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
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    ll len = K*2-1;
    rep(i, N-len+1) {
        ll need = A[i];
        if (need == 0) continue;
        ll l = i, r = i+K*2-2;
        rep(j, K-1) {
            A[l+j] -= pow(j+1, 2)*need;
            A[r-j] -= pow(j+1, 2)*need;
            if (A[l+j] < 0 or A[r-j] < 0) {
                No();
                return;
            }
        }
        A[l+K-1] -= pow(K, 2)*need;
        if (A[l+K-1] < 0) {
            No();
            return;
        }
    }
    if (sum(A) == 0) {
        Yes();
    } else {
        No();
    }
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
