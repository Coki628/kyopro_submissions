/*
参考：https://codeforces.com/blog/entry/119134
・自力ならず。これは無理なやつだった。
・式変形、数学、2次方程式の解
・唐突だけど、ai+aj=b,ai*aj=cとして、2次方程式x^2+bx+c=0に当てはめてみる。
　すると、x^2+(ai+aj)+ai*aj=0 => (x+ai)(x+aj)=0 と因数分解できるので、
　xの解は-ai,-ajとできる。今回はこのb,c部分がx,yとして与えられるので、
　これを使って解の公式なりに突っ込んで2つのxを求めれば、
　それがai,ajの候補となるので答えが分かる。
　にしてもこの、因数分解できる形に落とし込めるのは何回生まれ変わっても
　気付ける気がしないなー。。数学慣れしてると、
　ai+aj,ai*ajって2つを見た時にピンと来るのだろうか。　
・実装上はPython時代以来使ってなかった解の公式をC++に移植。
　C++標準で正確に整数判定とか厳しそうなので、とりあえず雑にroundと比較。
　一応お守り程度だけどEPSはつけとく。これで問題なく通った。
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

//  2次方程式の解の公式
pair<ld, ld> dim2formula(ld a, ld b, ld c) {
    ld d = sqrt(pow(b, 2) - 4 * a * c);
    // 解なし
    if (isnan(d)) {
        return {nan(""), nan("")};
    }
    return {(-b + d) / (2 * a), (-b - d) / (2 * a)};
}

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    auto C = Counter(A);
    ll Q;
    cin >> Q;
    vector<ll> ans(Q);
    rep(i, Q) {
        ll x, y;
        cin >> x >> y;

        auto [x1, x2] = dim2formula(1, x, y);
        if (isnan(x1)) {
            continue;
        }
        x1 = -x1, x2 = -x2;
        ll rx1 = round(x1), rx2 = round(x2);
        if (abs(rx1 - x1) < EPS and abs(rx2 - x2) < EPS) {
            if (rx1 == rx2) {
                ans[i] = nC2(C[rx1]);
            } else {
                ans[i] = C[rx1] * C[rx2];
            }
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
