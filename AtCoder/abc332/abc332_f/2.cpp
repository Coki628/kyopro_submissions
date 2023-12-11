/*
参考：https://twitter.com/kude_coder/status/1733845938949751131
・こっちの方針も通しておく。
・期待値、遅延セグ木、行列セグ木
・x <- ax + b は dp[i + 1] = dp[i] * a + b みたいなものなので、
　DP遷移と同じように行列に乗る。行列は(作用素にでも)セグ木に乗るので、
　2*2行列を適切に定義して適用していけばこれでも答えが求まる。
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

#include "datastructure/LazySegmentTree.hpp"
#include "matrix/mat_dot.hpp"

// 区間行列積更新・1点取得
using Matrix = array<array<mint, 2>, 2>;
auto f = [](mint a, mint b) -> mint { return a; };
auto g = [](mint a, const Matrix &b) -> mint {
    return a * b[0][0] + b[0][1];
};
auto h = [](const Matrix &a, const Matrix &b) -> Matrix {
    // マージ方向をb,aにする
    return mat_dot(b, a);
};
const mint T = 0;
// 2次元arrayの初期化は{}をひとつ多く括る
const Matrix E = {{
    {1, 0},
    {0, 1},
}};

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<mint> A(N);
    cin >> A;

    auto seg = get_lazy_segment_tree(N, f, g, h, T, E);
    rep(i, N) {
        seg.set(i, A[i]);
    }
    seg.build();
    rep(i, M) {
        ll l, r;
        mint x;
        cin >> l >> r >> x;
        l--;
        mint len = r - l;
        Matrix cur = {{
            // x <- ax + b
            {(len - 1) / len, x * ((mint)1 / len)},
            {0, 1},
        }};
        seg.update(l, r, cur);
        // rep(j, l, r) {
        //     A[j] = A[j] * ((len - 1) / len) + x * ((mint)1 / len);
        // }
    }
    print(seg);
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
