/*
・Mo's algorithm、BIT
・部分点2、BITでやったけど何か速くならなくてこれもTLE。。
・setよりは速いと思ったんだけど、何か全然速くならなかった…。
　前にMoとBITで10万くらいのやつ通ったやつと比べたら、
　その時はadd,eraseではにぶたんしてなかった。そのlogの差かねー。。
・BITにぶたんにlogが乗らなそうなやつを持ってきた。
　部分点2(制約50000)が1個TLEだったけど、QCFiumも使ったら、ギリギリ1.99秒で取れた！
　BITの型intにしたら、さらにちょっと速くなって1.92秒。
・自分のBITにlower_bound組み込んだ。誤差だけどちょっと速くて1.88秒になった。
*/

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);
    rep(i, N) A[i]--;

    assert(N <= 50000 and Q <= 50000);

    vector<ll> B(N, -1);
    rep(i, N-1) {
        B[A[i]] = A[i+1];
    }

    Mo mo(N);
    vector<ll> len(Q);
    rep(i, Q) {
        ll l, r;
        cin >> l >> r;
        l--;
        mo.add(l, r);
        len[i] = r - l;
    }

    BIT<int> bit(N);
    int cnt = 0;
    auto add = [&](int i) -> void {
        bit.add(A[i], 1);
        int sm = bit.query(0, A[i]+1);
        int prv = -1;
        if (sm-1 > 0) {
            prv = bit.lower_bound(sm-1);
        }
        int nxt = bit.lower_bound(sm+1);
        if (nxt >= N) nxt = -1;

        if (prv != -1) {
            if (B[prv] == A[i]) cnt++;
        }
        if (nxt != -1) {
            if (B[A[i]] == nxt) cnt++;
        }
        if (prv != -1 and nxt != -1) {
            if (B[prv] == nxt) cnt--;
        }
    };
    auto erase = [&](int i) -> void {
        int sm = bit.query(0, A[i]+1);
        int prv = -1;
        if (sm-1 > 0) {
            prv = bit.lower_bound(sm-1);
        }
        int nxt = bit.lower_bound(sm+1);
        if (nxt >= N) nxt = -1;

        if (prv != -1) {
            if (B[prv] == A[i]) cnt--;
        }
        if (nxt != -1) {
            if (B[A[i]] == nxt) cnt--;
        }
        if (prv != -1 and nxt != -1) {
            if (B[prv] == nxt) cnt++;
        }
        bit.add(A[i], -1);
    };
    vector<int> ans(Q);
    auto out = [&](int i) -> void {
        ans[i] = len[i] - cnt;
    };
    mo.build(add, erase, out);
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
