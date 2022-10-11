/*
参考：https://atcoder.jp/contests/abc272/editorial
・むずい。公式解説の広い行間を、miscalcさんが埋めてくれてて助かった。
・suffix array, LCP, 二分探索、辞書順
・この手のSAからのLCPをセグ木に乗せてlcp(l,r)を求めるやつは何回かやってるけど身についてない。
　今回はにぶたんするsaのindexで、右端としてTの0～N-1しか使いたくないので、
　そこだけを取り出した別配列を用意する必要があるあたりが自分的には肝だった。(自分からは出なかった)
　あとにぶたん内で辞書順の大小を判定する時に、sa上でSiよりTjのが前にいれば
　Siのが小さいことないので無条件にNG、とか思ったけど違ってて、
　多分なんだけど、saに乗ってるのはあくまで連結後の文字列Uなので、
　ここでの辞書順がS,Tにも同様に通用するとは限らないのかなー、と思った。
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

#include "acl/string.hpp"
using namespace atcoder;

void solve() {
    ll N;
    cin >> N;
    string S, T;
    cin >> S >> T;

    auto U = S + S + T + T;
    auto sa = suffix_array(U);
    vector<int> rsa(N*4);
    rep(i, N*4) {
        rsa[sa[i]] = i;
    }
    auto lcp = lcp_array(U, sa);
    // P[i] := sa内でi番目にある文字列Tの、saのindex(ややこしい)
    vector<int> P;
    rep(i, N*4) {
        if (N*2 <= sa[i] and sa[i] < N*3) {
            P.eb(i);
        }
    }
    auto seg = get_segment_tree(lcp, [](int a, int b) { return min(a, b); }, MOD);
    ll ans = 0;
    rep(i, N) {
        ll res = bisearch_min(-1, N, [&](ll x) {
            ll l = rsa[i], r = P[x];
            ll j = sa[r];
            // sa上で前にいても辞書順で前とは限らない
            // (多分、UはS,Tをくっつけた列なので、Uの辞書順がS,Tの辞書順とは限らないため)
            if (l > r) swap(l, r);
            ll len = seg.query(l, r);
            if (len >= N) return true;
            return U[i+len] <= U[j+len];
        });
        ans += N - res;
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
