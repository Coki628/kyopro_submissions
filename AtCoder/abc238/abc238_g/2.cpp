/*
・自力AC？Moって聞いちゃってたけど、これは気付けた気がする。
・立方数、素因数分解、Mo's algorithm
・まともに積を考えると明らかにでかくなり過ぎる。立方数かどうかだけ分かればいいので、
　今ある全ての素因数が3で割り切れるかどうか、を見ていくことにする。
　すると素因数分解は篩で前計算するやつを使えばNlogくらいで済むし、
　この列挙も前もってやっておけば、Moの伸縮時にはさらに少なくできる。
　(かんプリンさんの記事より、10^6以下なら高々7個だそう。
　思ったより少ない。これがもう少し多い気がしてたから、
　Mo*素因数分解が間に合うって判断を自分では下せなかった可能性は高い…。)
・クエリの判定部分では、NGな個数を持っておけばO(1)で見れる。
　ここで全素因数見ちゃったりすると間に合わなそう。
・最初TLEしたけど、今回最大値が10^6でこれならvectorで持てるので、
　全体の個数持つやつをmapからvectorに持ち替えたら無事AC。2.34秒。(制約3秒)
・素因数分解の中身とかllを全部intにしたら結構変わって1.96秒。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "numbers/Eratosthenes.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);

    Mo mo(N);
    rep(i, Q) {
        ll l, r;
        cin >> l >> r;
        l--;
        mo.add(l, r);
    }

    const int M = 1000000;
    Eratosthenes era(M);
    vector<vector<pii>> fact(N);
    rep(i, N) {
        fact[i] = era.factorize(A[i]);
    }

    int ngcnt = 0;
    vector<int> C(M+1);
    vector<bool> ans(Q);
    auto add = [&](int i) -> void {
        for (auto [k, v] : fact[i]) {
            int cur = C[k];
            int nxt = cur+v;
            if (cur%3 == 0 and nxt%3 != 0) {
                ngcnt++;
            }
            if (cur%3 != 0 and nxt%3 == 0) {
                ngcnt--;
            }
            C[k] = nxt;
        }
    };
    auto erase = [&](int i) -> void {
        for (auto [k, v] : fact[i]) {
            int cur = C[k];
            int nxt = cur-v;
            if (cur%3 == 0 and nxt%3 != 0) {
                ngcnt++;
            }
            if (cur%3 != 0 and nxt%3 == 0) {
                ngcnt--;
            }
            C[k] = nxt;
        }
    };
    auto out = [&](int i) -> void {
        if (ngcnt == 0) {
            ans[i] = true;
        }
    };
    mo.build(add, erase, out);

    rep(i, Q) {
        if (ans[i]) Yes();
        else No();
    }
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
