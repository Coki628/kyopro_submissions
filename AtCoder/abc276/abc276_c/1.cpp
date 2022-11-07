/*
・なんとか自力AC！
・むずくない？後ろから見て最初に隣接が降順になる場所(A[i],A[i+1]とする)を起点として、
　そこより後ろでA[i]より小さい最大の数を見つけて、それをA[i]とswapして、
　A[i+1]以降は降順ソートで並べる。ほぼサンプルエスパーなので祈るように投げた。
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
    vector<ll> A(N);
    cin >> A;

    rep(i, N-2, -1, -1) {
        if (A[i] > A[i+1]) {
            ll x = -1, k = -1;
            rep(j, i+1, N) {
                if (A[j] < A[i]) {
                    if (chmax(x, A[j])) {
                        k = j;
                    }
                }
            }
            assert(x != -1);
            swap(A[k], A[i]);
            sort(A.begin()+i+1, A.end());
            reverse(A.begin()+i+1, A.end());
            break;
        }
    }
    print(A);
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
