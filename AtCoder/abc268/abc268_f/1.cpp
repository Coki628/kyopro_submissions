/*
・Upsolved。自力ACではないな。TLでソート(が本質)っていう重大すぎるキーワードを得てしまっていた。
・工夫してソート
・まず、同じS[i]内で得られるスコアは並びによって変化しないので先に計上しておく。
　これで以後、S[i]内での文字の並びを考慮しなくてよくなるので、
　あとは各S[i]で数字の和とXの個数だけを持てばよくなる。
　並び順の決め方について、数字の和が大きいのは前に出したいし、
　Xの個数は少ないやつを前に出したい。ここから何となく、
　「数字の和/Xの個数」がソート条件として有力だなーと考えて、
　実際それで通ったんだけど、ソート貪欲をメインで考察できたのはヒントを得ていたからだし、
　そうでなかったら正しい方針に進めたか分からない。
・公式解説を見ると、ちゃんと式変形して上記条件が正しいことを示してる。
　これがちゃんと自分でできれば、もっと考察の打率が上がるんだけどねぇ…。
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
    ll N;
    cin >> N;
    vector<string> S(N);
    vector<ll> xcnt(N), nmcnt(N);
    vector<pair<ld, ll>> V;
    rep(i, N) {
        cin >> S[i];
        rep(j, S[i].size()) {
            if (S[i][j] == 'X') {
                xcnt[i]++;
            } else {
                nmcnt[i] += toint(S[i][j]);
            }
        }
        V.eb(xcnt[i] == 0 ? INF : nmcnt[i]/(ld)xcnt[i], i);
    }
    ll xtotal = sum(xcnt);
    sort(V.rbegin(), V.rend());

    // 並びで変化しないスコアを先に計上
    ll ans = 0;
    rep(i, N) {
        ll xsub = 0;
        rep(j, S[i].size()-1, -1, -1) {
            if (S[i][j] == 'X') {
                xsub++;
            } else {
                ans += toint(S[i][j]) * (xcnt[i]-xsub);
            }
        }
    }

    // 「数字の和/Xの個数」でソートした順に並べる
    for (auto [_, i] : V) {
        xtotal -= xcnt[i];
        ans += nmcnt[i] * xtotal;
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
