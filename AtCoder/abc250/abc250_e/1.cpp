/*
参考：https://twitter.com/norikame_d/status/1523307590553272322
・自力ならず…。
・Mo's algorithm
・想定は尺取りだったみたい。それも考えたけど、実装つらそうで辞めてしまった…。
・Moで何とかしようとしたんだけど、詰め切れず。
　そもそも左端が右端より右に行く可能性のあるクエリでMoが適用可なのか確証が持てず、
　無理なのかと思ったけど、のりかめさんがMoで通したのを観測したので、やる。
・座圧でmapをvectorにしないとTL無理なのは想定内だけど、
　OKな数じゃなくてNGな数を数えておけばやりやすいってことを見抜けず。
　abc238_gでMo使った時もそれ見えなくて同じこと思ったのに、やっちまったなー…。
　あと気を付けるのが、左端が伸びた時じゃなく、縮んだ時に値が追加なので間違えないようにするのと、
　その関係もあって左端も右端みたいな扱いになるので、
　半開区間の右端みたいに1つ後ろにする。(つまり1引かなくていい)
・その辺りを諸々考慮して無事AC。TL4秒で1.06秒。
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

#include "segment/Mo.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    auto B = LIST(N);

    Compress<ll> cp(concat(A, B));
    ll M = cp.size();
    A = cp.zip(A);
    B = cp.zip(B);

    ll Q;
    cin >> Q;
    Mo mo(N);
    rep(i, Q) {
        ll x, y;
        cin >> x >> y;
        // x--;
        mo.add(x, y);
    }
    ll ngcnt = 0;
    vector<ll> C1(M), C2(M);
    vector<string> ans(Q);
    auto add_left = [&](int i) -> void {
        if ((C1[A[i]] > 0) == (C2[A[i]] > 0)) ngcnt++;
        C1[A[i]]--;
        if ((C1[A[i]] > 0) == (C2[A[i]] > 0)) ngcnt--;
    };
    auto erase_left = [&](int i) -> void {
        if ((C1[A[i]] > 0) == (C2[A[i]] > 0)) ngcnt++;
        C1[A[i]]++;
        if ((C1[A[i]] > 0) == (C2[A[i]] > 0)) ngcnt--;
    };
    auto add_right = [&](int i) -> void {
        if ((C1[B[i]] > 0) == (C2[B[i]] > 0)) ngcnt++;
        C2[B[i]]++;
        if ((C1[B[i]] > 0) == (C2[B[i]] > 0)) ngcnt--;
    };
    auto erase_right = [&](int i) -> void {
        if ((C1[B[i]] > 0) == (C2[B[i]] > 0)) ngcnt++;
        C2[B[i]]--;
        if ((C1[B[i]] > 0) == (C2[B[i]] > 0)) ngcnt--;
    };
    auto out = [&](int i) -> void {
        if (ngcnt == 0) {
            ans[i] = "Yes";
        } else {
            ans[i] = "No";
        }
    };
    mo.build(add_left, add_right, erase_left, erase_right, out);
    print(ans, '\n');
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
