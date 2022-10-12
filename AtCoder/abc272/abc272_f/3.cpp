/*
・Suffix Array、LCP、セグ木にぶたん、Wavelet Matrix、辞書順
・自分で途中まで考えてた方針。これでも通せた。
　考察としては、あるS[i]についてsa上で自身より右にあるT[j]については
　確実に辞書順で大きいと考えてよくて、つまり右端はsaの末尾を取っていい、
　で、同値については自身とのlcpがN以上続く部分となるので、
　自身の位置から左に向かってlcpがN以上である限り伸ばす。
　これはセグ木にぶたんでできる。ここを左端とする。
　この範囲内にあるT[i]のindexの個数が欲しいので、予めsa配列をWMに乗せておいて、
　range_freqで[N*2,N*3)の範囲にある値の個数を数える。
・速度について、WMのlogは意外とボトルネックになっていないようで、
　セグ木を普通ににぶたんしても0.47秒で遅くならなかった。
　この形だとこのにぶたんはlog1個のセグ木にぶたんに乗せれるので、
　そうしてみると0.26秒でちゃんと速くなった。
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

#include "string/SuffixArray.hpp"
#include "segment/WaveletMatrix.hpp"

void solve() {
    ll N;
    cin >> N;
    string S, T;
    cin >> S >> T;

    auto U = S + S + T + T;
    SuffixArray sa(U);
    WaveletMatrix<int> wm(sa.sa);
    ll ans = 0;
    rep(i, N) {
        ll r = sa.rsa[i];
        ll l = sa.seg.find_last(r, [&](ll m) { return m < N; }) + 1;
        // ll l = bisearch_min(-1, r, [&](ll m) {
        //     return sa.seg.query(m, r) >= N;
        // });
        ans += wm.range_freq(l, N*4, N*2, N*3);
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
