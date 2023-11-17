/*
・きっちり自力AC！
・数え上げ、ソートしてランレングス、区間乗算
・ソートしてランレングスすると、Counterしたのとほぼ同じ集計になるけど、
　持ち方がmapじゃなくてvectorなので、
　今回のM個離れた場所チェックみたいなやつはとてもやりやすい。
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
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N);
    cin >> A;

    sort(ALL(A));
    auto rle = RLE(A);
    ll K = rle.size();
    auto seg = get_segment_tree(K, [](mint a, mint b) { return a * b; }, (mint)1);
    rep(i, K) {
        seg.update(i, rle[i].second);
    }
    mint ans = 0;
    rep(i, K - M + 1) {
        auto [k1, _] = rle[i];
        auto [k2, __] = rle[i + M - 1];
        if (abs(k1 - k2) < M) {
            ans += seg.query(i, i + M);
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
