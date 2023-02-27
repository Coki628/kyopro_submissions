/*
・自力ならず。悔しい。
・FFT、OR、ビット毎に見る
・ABC196Fを見て畳み込みに思いを馳せたにも関わらず解けなかった。
　ビット毎に見るのと結びつかなかった。典型考察なのに…。
・とりあえずビット毎で見ればABC196Fとだいたい同じ感じ。
　OR演算は(1-a)(1-b)でやって集計した答えを再度フリップするとよくて、
　サイクルして前後を跨ぐペアはmod Nが同じ所でまとめればいい。
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

#include "acl/convolution.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N), B(N);
    cin >> A >> B;

    reverse(ALL(B));
    ll L = 5;
    auto sm = listnd(L, N, 0LL);
    vector<ll> ans(N);
    rep(b, L) {
        vector<ll> cura(N), curb(N), cnt(N);
        rep(i, N) {
            cura[i] = !(A[i] >> b & 1);
            curb[i] = !(B[i] >> b & 1);
        }
        auto res = atcoder::convolution_ll(cura, curb);
        rep(i, res.size()) {
            cnt[i % N] += res[i];
        }
        rep(i, N) {
            ans[i] += (1LL << b) * (N - cnt[i]);
        }
    }
    print(max(ans));
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
