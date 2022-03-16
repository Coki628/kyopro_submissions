/*
参考：https://www.youtube.com/watch?v=D0Op33UL_cA
　　　https://blog.hamayanhamayan.com/entry/2020/09/27/013201
・dojo set_d_5_6
・マッチング、二重階乗、分割統治FFT、包除原理
・むっずい。でも有用なテクが多く含まれてて教育的な良問だと思う。
・まず身長が同じ人達でまとめておいて、ここから色々検討していく。
　最終的に同じ身長の人達同士のペアを無くしたい訳だけど、
　「○○が(1つでも)あったらダメ」は包除みがある、みたいに考えていいのかも。
・で、上記の形で包除を検討すると、身長の同じ人達同士のペアが1個以上,2個以上..N個以上、
　みたいのを網羅できれば、包除の+-で同じペアが1つもない状態を作れそうだ。
・さてここで、各身長毎に「F[h][p] := 身長hの人達同士でp個ペアを作る通り数」だったら求まる。
　この求め方はソース内コメントも参照なんだけど、半分は普通に二項係数で、
　ペアのマッチングはちょっと珍しいやつで二重階乗っていうのが出てくる。
　公式があるので、二項係数ライブラリに組み込んでおいた。
・これを求めれば身長の違う人達同士の集合をマージして、この時にp個「以上の」ペアになるけど、
　それを最後に包除で帳尻合わせればいい訳で、求めたい答えが求まる。
　この集合のマージというのが、DP遷移っぽく言えば、
　dp[i+j] += dp[i]*dp[j] みたいのを全通りやる感じになるので、
　まさに畳み込みになる。これを普通に前からやるのではなく、
　分割統治FFTでやれば、マージ前の配列長の総和にlog乗ったくらいの計算量になる。
・これで「res[p] := 2N人全員でp個以上ペアを作る通り数」が求まったので、
　それぞれの状態で未確定な部分を、これもまた二重階乗で確定させる。
　最後に包除で+-した値を答えとすればOK。長い。。
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
    ll N;
    cin >> N;
    ll N2 = N * 2;
    auto H = LIST(N2);

    const ll M = 1e5;
    ModTools<mint> mt(max(N2, M));
    auto C = Counter(H, M);
    vector<FPS<mint>> F(M+1 ,{1});
    rep(h, 1, M+1) {
        // F[h][p] := 身長hの人達同士でp個ペアを作る通り数
        rep(p, 1, C[h]/2+1) {
            // nCr(身長hの人全員, ペアに使う人数) * 2p人でペアを決める通り数
            F[h].eb(mt.nCr(C[h], p*2) * mt.double_factorial(p*2-1));
        }
    }

    auto rec = [&](auto&& f, ll l, ll r) -> FPS<mint> {
        ll len = r - l;
        if (len == 0) {
            return {1};
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
    // res[p] := 2N人全員でp個以上ペアを作る通り数
    auto res = rec(rec, 0, M+1);
    rep(p, res.size()) {
        // p個ペア以外のマッチングを自由に決める通り数を掛ける
        res[p] *= mt.double_factorial(N2-2*p-1);
    }

    mint ans = 0;
    rep(i, res.size()) {
        ans += res[i] * (i%2 == 0 ? 1 : -1);
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
