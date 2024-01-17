/*
参考：https://www.youtube.com/watch?v=K219pPDsZ3A
　　　https://codeforces.com/blog/entry/124757
・自力ならず。むずい。
・MOD累積和、平方分割
・この前のABC(abc335)とかなり本質は近いのに、やっぱりMOD累積和が全然合わず終了…。
　分かっててもむずいMOD累積和。まじでどうにかなんないものか。
　今回はMOD累積和もさることながら、係数Kが乗っているのをどう差し引きするか
　みたいなパートも難しくて、結局自力では何を引けばいいのか分からず…。
　結局、Kのかかってない累積和も取っといてそこからうまく差し引きすると合うというものだった。
　累積和で三角形引く三角形した後に長方形領域も引く、みたいなイメージは他でも出てるけど、
　今回はそれだけじゃうまく解釈できなくて、一旦MOD累積和抜きにしてMOD 1で考えて、
　どこ引けばいいかちゃんと図書いてみてやっと公式解がs/d掛けたりしてる意味が分かった。
　まあでもどこって口で説明するのは大変。(必要であれば自分ノートも参照)
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    cin >> A;

    ll D = ceil(sqrt(N));
    auto sm = listnd(D, N + D, 0LL);
    auto sm2 = listnd(D, N + D, 0LL);
    auto kval = listnd(D, N + D, 0);
    rep(d, 1, D) {
        ll k = 0;
        rep(i, N) {
            if (i % d == 0) k++;
            sm[d][i + d] = sm[d][i] + A[i];
            sm2[d][i + d] = sm2[d][i] + A[i] * k;
            kval[d][i + d] = k;
        }
    }

    vector<ll> ans(Q);
    rep(i, Q) {
        ll s, d, k;
        cin >> s >> d >> k;
        s--;

        if (d < D) {
            ans[i] = sm2[d][s + d * k] - sm2[d][s] - (sm[d][s + d * k] - sm[d][s]) * kval[d][s];
        } else {
            ll kk = 1;
            rep(j, s, min(s + d * k, N), d) {
                ans[i] += A[j] * kk;
                kk++;
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
