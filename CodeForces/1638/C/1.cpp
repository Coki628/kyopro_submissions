/*
・なんとか自力AC！
・転倒数、BIT、UF
・絶対もっと簡単な方針あった気がする。
・BITとUFを用意。基本は転倒数みたいにBITに値埋め込んでおいて、
　BITにぶたんで自分より右をUFでマージしたいんだけど、全部やると無理なので減らす。
　UFのマージと一緒に連結成分内で(BIT上で)最も左と右な位置を持つ。
　今見ていた要素がそれに該当しなくなったらBITから除く。
　同じ連結成分内で真ん中らへんにあるものは、BITから除いておいても(多分)連結に影響しない。
・ってここまで書いてて、これ左右じゃなくて右端だけでよくない？
　って思って右端だけにして投げてみたらやっぱりちゃんと通った。
　そうだよね、転倒数としてなるべく強く拾ってもらいたい訳だから、最大の値だけ持てばいいね。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define MINT_TO_LL_CAST
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
    rep(i, N) A[i]--;

    UnionFind uf(N);
    BIT<ll> bit(N);
    vector<ll> atoi(N);
    rep(i, N) atoi[A[i]] = i;

    vector<ll> R = A;
    rep(i, N) {
        ll cur = A[i];
        while (1) {
            ll nxt = bit.bisearch_fore(cur+1, N-1, 1);
            if (nxt != -1) {
                ll j = atoi[nxt];
                ll ri = uf.find(i);
                ll rj = uf.find(j);
                ll r = uf.merge(i, j);
                if (r == ri) {
                    chmax(R[ri], R[rj]);
                } else {
                    chmax(R[rj], R[ri]);
                }
                if (A[j] != R[r]) {
                    bit.add(A[j], -1);
                }
                cur = nxt;
            } else {
                break;
            }
        }
        if (A[i] == R[uf.find(i)]) {
            bit.add(A[i], 1);
        }
    }
    ll ans = uf.size();
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
