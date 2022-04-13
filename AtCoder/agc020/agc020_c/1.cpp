/*
参考：https://www.youtube.com/watch?v=4SLQUMQlVAU
・dojo set_d_6_8
・自力ならず。考察むずい…。
・部分和DP、bitset高速化
・数列Aの総和をSとしておく。考察のため空集合も含める。
　各部分和を、補集合(選ぶ/選ばないを全部逆にしたやつ)とペアにする。
　そうすると、ペアの和は常にSになる。これを踏まえて、部分和の全通りを
　ソートして並べると、各ペアは全部対角線みたいな位置に行くことになり、
　このソート済の列の上半分はS/2以上、下半分はS/2以下のようになる。
　(どのペアも総和がSで変わらないから、真ん中は絶対ちょうど半分になる、
　って感じの考えでいいんだろうか。それにしても思いつくか、これ)
・さて、これが分かれば、S/2以上で最初の値が答え。
　部分和DPで、存在有無だけなのでbitsetで全ビットまとめてor取れば、
　2000^2=400万ビットを2000回回しても間に合う。(AC0.33秒)
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    ll S = sum(A);
    bitset<4000007> dp;
    dp[0] = 1;
    rep(i, N) {
        dp |= dp << A[i];
    }

    ll mid = ceil(S, 2LL);
    vector<ll> V;
    rep(i, S+1) {
        if (dp[i]) {
            V.eb(i);
        }
    }
    ll ans = *lower_bound(ALL(V), mid);
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
