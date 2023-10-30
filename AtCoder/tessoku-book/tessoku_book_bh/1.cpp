/*
・きっちり自力AC！
・座圧してセグ木のindexに値、値にindexの最大値入れる。
・でもこれ持ち方変えないでセグ木にぶたんでも求まりそうね。
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

    Compress<ll> cp(A);
    A = cp.zip(A);
    ll M = cp.size();
    auto seg = get_segment_tree(M, [](ll a, ll b) { return max(a, b ); }, -INF);
    vector<ll> ans(N, -1);
    rep(i, N) {
        ll res = seg.query(A[i] + 1, M);
        if (res > -INF) {
            ans[i] = res;
        }
        seg.update(A[i], max(seg[A[i]], i + 1));
    }
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
