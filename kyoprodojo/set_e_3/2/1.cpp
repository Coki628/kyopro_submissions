/*
・abc062_d
・なんとか自力AC！
・BIT2本で個数と総和
・確か何かプリキュー2,3個持ってうまいことやるんだよなーこれ、
　くらいには覚えていたけどしばらく方針が見えず。
　けど悩んだ後、どこまで左に入れるかみたいなN箇所全探索に気付けた。
　でもプリキューじゃN番目とか和とか取れなくない？ってなって、
　座圧してBITで個数と総和を持つやつで、BITにぶたんしてN番目を見つけて、
　みたいなのを左右でやった。なんとか自力で通せて良かったけど、
　やっぱり想定解はプリキューでもっと賢くやっていて、やっぱりすごいなぁとなった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N*3);

    Compress<ll> cp(A);
    A = cp.zip(A);
    ll M = cp.size();

    BIT<ll> bitlcnt(M), bitlsm(M), bitrcnt(M), bitrsm(M);
    rep(i, N) {
        bitlcnt.add(A[i], 1);
        bitlsm.add(A[i], cp.unzip(A[i]));
    }
    rep(i, N, N*3) {
        bitrcnt.add(A[i], 1);
        bitrsm.add(A[i], cp.unzip(A[i]));
    }

    auto calc = [&]() -> ll {
        // 左側大きい方からN個
        ll i = bitlcnt.bisearch_back(0, M-1, N);
        assert(i != -1);
        ll lcnt = bitlcnt.query(i, M);
        ll lexeed = lcnt-N;
        ll lsm = bitlsm.query(i, M)-cp.unzip(i)*lexeed;
        // 右側小さい方からN個
        ll j = bitrcnt.bisearch_fore(0, M-1, N);
        assert(j != -1);
        ll rcnt = bitrcnt.query(0, j+1);
        ll rexeed = rcnt-N;
        ll rsm = bitrsm.query(0, j+1)-cp.unzip(j)*rexeed;
        return lsm-rsm;
    };
    ll ans = calc();
    rep(i, N, N*2) {
        bitrcnt.add(A[i], -1);
        bitrsm.add(A[i], -cp.unzip(A[i]));
        bitlcnt.add(A[i], 1);
        bitlsm.add(A[i], cp.unzip(A[i]));
        chmax(ans, calc());
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
