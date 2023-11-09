/*
・きっちり自力AC！
・連続部分列、区間(l,r)、約数、区間和、UF、にぶたん
・1つ目の約数の条件は、途切れる時はぷっつりそこで区間が区切られる感じで、
　2つ目の区間和の条件は、よく見るやつで累積和にぶたんとかすればいい。
　組み合わせるに当たってどうするか少し考えた。
　結局1つ目の条件はUFで連結を作っておいて、まだ同じ連結成分か？を
　にぶたんに乗せることにした。これで累積和にぶたんと組み合わせて使えるので、
　後は左端固定、にぶたんで最大の右端を求めて前に突き進むのみ。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N), H(N);
    cin >> A >> H;

    UnionFind uf(N);
    rep(i, N - 1) {
        if (H[i] % H[i + 1] == 0) {
            uf.merge(i, i + 1);
        }
    }
    Accumulate<ll> acc(A);
    ll ans = 0;
    rep(i, N) {
        ll j = bisearch_max(i - 1, N, [&](ll x) {
            return uf.same(i, x) and acc.query(i, x + 1) <= K;
        });
        chmax(ans, j - i + 1);
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
