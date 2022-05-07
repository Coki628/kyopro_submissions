/*
・きっちり自力AC！今日ここまでいい流れだった。
・順列、グラフに帰着
・制約10万でお題が順列だとグラフにするの多いよね。
・グラフにする。A[i]とB[i]をUFで連結して、確定な部分がない連結成分の数だけ*2する。
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
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    auto B = LIST(N);
    auto D = LIST(N);
    rep(i, N) {
        A[i]--;
        B[i]--;
        D[i]--;
    }

    UnionFind uf(N);
    rep(i, N) {
        uf.merge(A[i], B[i]);
    }
    vector<ll> fixed(N);
    rep(i, N) {
        if (A[i] == B[i] or D[i] != -1) {
            fixed[uf.find(A[i])] = 1;
        }
    }
    // print(uf.get_info());

    mint ans = 1;
    for (auto r : uf.get_roots()) {
        if (not fixed[r]) {
            ans *= 2;
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
