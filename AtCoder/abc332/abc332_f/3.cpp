/*
ライブラリ整備：双対セグ木
・合成関数。非可換の演算を乗せる場合。双対セグ木はこの時に結構内部実装が変わる。
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

#include "datastructure/DualSegmentTree.hpp"

// 区間乗算・区間加算・1点取得
struct Func {
    mint mul, add;
    bool operator==(const Func &f) const {
        return mul == f.mul and add == f.add;
    }
};
auto g = [](mint a, Func b) -> mint {
    return a * b.mul + b.add;
};
// ax + b の合成関数
// h2(h1(x))
// c * h1(x) + d
// c * (ax + b) + d
// c * ax + c * b + d
// {c * a, c * b + d}
auto h = [](Func a, Func b) -> Func {
    return {b.mul * a.mul, b.mul * a.add + b.add};
};
const mint T = 0;
const Func E = {1, 0};

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<mint> A(N);
    cin >> A;

    // 関数の合成は非可換
    auto seg = get_dual_segment_tree(A, g, h, T, E, false);
    rep(i, M) {
        ll l, r;
        mint x;
        cin >> l >> r >> x;
        l--;
        mint len = r - l;
        seg.update(l, r, {(len - 1) / len, x * ((mint)1 / len)});
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
