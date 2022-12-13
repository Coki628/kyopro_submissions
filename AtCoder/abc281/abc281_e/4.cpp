/*
・BIT2本、座圧してBITにぶたん
・TLでBITで解いたって話も流れてきていて、それ聞いて気付いた方針。
　座圧した上で個数と和をBITで管理すると、出し入れしながら和も取れる。
　自分的には多分これが一番バグらせないでできそう。
・1つ気をつけるのが、個数取った時に同値が同じ位置に重なっていると、
　その中のどこまで和を取ればいいか分かりづらいので、
　indexまで座圧の情報に含めて同値を区別するようにする。
　これならその端数処理を考えなくていいので楽。
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
    ll N, M, K;
    cin >> N >> M >> K;
    vector<ll> A(N);
    cin >> A;

    // 同値を区別できるようにindexの情報を座圧に含める
    vector<pll> AI;
    rep(i, N) {
        AI.eb(A[i], i);
    }
    Compress<pll> cp(AI);
    ll L = cp.size();
    auto cpa = cp.zip(AI);
    BIT<ll> bitcnt(L), bitsm(L);
    rep(i, M) {
        bitcnt.add(cpa[i], 1);
        bitsm.add(cpa[i], A[i]);
    }
    vector<ll> ans;
    ll k = bitcnt.bisearch_fore(0, L-1, K);
    assert(k != -1);
    ans.eb(bitsm.query(0, k+1));
    rep(i, M, N) {
        ll j = i - M;
        bitcnt.add(cpa[i], 1);
        bitsm.add(cpa[i], A[i]);
        bitcnt.add(cpa[j], -1);
        bitsm.add(cpa[j], -A[j]); 
        ll k = bitcnt.bisearch_fore(0, L-1, K);
        assert(k != -1);
        ans.eb(bitsm.query(0, k+1));
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
