/*
参考：https://yukicoder.me/problems/no/1068/editorial
　　　https://yukicoder.me/problems/no/1066/editorial
　　　https://blog.hamayanhamayan.com/entry/2020/09/27/013201
・FPS演習、分割統治FFT
・名前は聞いてたけど理解できてなかったやつ、初めてやった！
　これはまた分かったら目からウロコだったなー。
・まずは普通のDPからFPS的な多項式のやつに変換しないといけない。
　1066の方のDPも見てみると、今回これは色1を取るかそれ以外かだけが重要で、
　各回の遷移は、
　色1を取らない遷移*(A[i]-1)回 + 色1を取る遷移*1回
　のようになる。これを多項式に置き換えると、
　(A[i]-1)*x^0 + 1*x^1 => (A[i]-1+x)
　となり、公式解の式と同じ形が出てくる。
　で、このN=20万回くらいの多項式乗算を高速に行いたい訳だが、
　全て2項ではあるものの、同じ式のN乗(yukico802)でもないし、
　(1-x^a)のような定数項が1の形(部分和DPや累積和遷移の高速化)でもないので、
　これまでやってきた方針が使えない。ここで分割統治FFTの出番になる。
　今回は元が全て(定数項+x^1)の形のため、適切に最大次数の小さい物からマージすると、
　最後の方まで次数がそこまで大きくならない。均等にみんな最初は小さいので、
　二分木みたいに隣同士と順番にマージするといいと思うと、
　分割統治法の再帰がぴたりとハマるのが分かる。
・仕組みが分かってしまえば、半分にしていくこの再帰は区間DPのやつとかより全然簡単で
　結構すんなり書くことができた。ライブラリ化してる人も多いみたいだけど、
　これはその場で書いてもいいんじゃないかと思う感じだ。
・ちなみに戻ってきた時一応shrinkしてるけど、やらなくても速度変わらなかった。
　やっぱり次数が大きくならない仕組みになってるんだな。
　20万のNでlog2つ乗ってる訳だけどAC0.69秒。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

#include "math/FormalPowerSeries.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);
    auto B = LIST(Q);

    vector<FPS<mint>> F(N, {0, 0});
    rep(i, N) {
        // 色1を取らない遷移*(A[i]-1)回 + 色1を取る遷移*1回
        // (A[i]-1)*x^0 + 1*x^1
        F[i][0] = A[i] - 1;
        F[i][1] = 1;
    }

    auto rec = [&](auto&& f, ll l, ll r) -> FPS<mint> {
        ll len = r - l;
        if (len == 0) {
            return FPS<mint>{1};
        } elif (len == 1) {
            return F[l];
        } elif (len == 2) {
            return F[l] * F[l+1];
        } else {
            ll m = (l+r) / 2;
            auto res = f(f, l, m) * f(f, m, r);
            res.shrink();
            return res;
        }
    };
    auto res = rec(rec, 0, N);
    rep(i, Q) {
        if (B[i] < res.size()) {
            print(res[B[i]]);
        } else {
            print(0);
        }
    }
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
