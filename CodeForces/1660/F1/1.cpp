/*
・きっちり自力AC！
・累積和で前計算、二分探索
・ちゃんと後ろ見て良かった。2乗が効くので、全区間見る。
　予め累積和で各区間の+-の個数は取っとく。
　ぴったりなら即OK、プラスのが少なければ、マイナス減らしてプラス増やす。
　賢い計算ありそうだったけど、単調性はあると思ったのでさっさとにぶたんした。
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
    string S;
    cin >> S;

    Accumulate<ll> acc(N);
    rep(i, N) {
        if (S[i] == '+') {
            acc.set(i, 1);
        }
    }
    acc.build();

    ll ans = 0;
    rep(l, N) {
        rep(r, l+1, N+1) {
            ll plus = acc.query(l, r);
            ll minus = (r-l) - plus;
            if (plus == minus) {
                ans++;
            } elif (plus < minus) {
                ll mxuse = minus / 2;
                ll res = bisearch_min(0, mxuse+1, [&](ll use) {
                    ll curm = minus;
                    ll curp = plus;
                    curm -= use*2;
                    curp += use;
                    return curp >= curm;
                });
                if (res != mxuse+1) {
                    ll use = res;
                    ll curm = minus;
                    ll curp = plus;
                    curm -= use*2;
                    curp += use;
                    if (curp == curm) {
                        ans++;
                    }
                }
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
