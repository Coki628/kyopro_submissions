/*
・なんとか自力AC！
・上位ビットから貪欲。取れるビットでは集合を半分に分ける。
　この回数はせいぜいNのlog回くらいなので間に合う。
　でも集合の空チェックしないと最大で2^30個くらい要素詰めてしまってそうで、
　これ直して残り3分くらいで何とかTLE&MLE取れてAC。
・終了後だけど、よく見たら個別の要素に何があるか見る処理はないので、
　集合管理setじゃなくてvectorでいいよねとなってちょっと書き直した。
　やっぱりかなり速くなって、AC2.26秒→0.83秒。(制約3秒)
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
    const ll M = 30;
    ll N;
    cin >> N;
    auto A = LIST(N);
    auto B = LIST(N);

    vector<int> ng(M), cura(N), curb(N);
    iota(ALL(cura), 0);
    iota(ALL(curb), 0);
    vvi va, vb;
    va.eb(cura), vb.eb(curb);
    rep(k, M-1, -1, -1) {
        vvi vaok, vbok;
        rep(i, va.size()) {
            vector<int> nxta1, nxta2, nxtb1, nxtb2;
            for (auto j : va[i]) {
                if (A[j]>>k & 1) {
                    nxta1.eb(j);
                } else {
                    nxta2.eb(j);
                }
            }
            for (auto j : vb[i]) {
                if (B[j]>>k & 1) {
                    nxtb1.eb(j);
                } else {
                    nxtb2.eb(j);
                }
            }
            if (nxta1.size() == nxtb2.size()) {
                // ここで要素有無チェックしないと空vector詰めまくりでTLE&MLEする
                if (nxta1.size()) {
                    vaok.eb(nxta1), vbok.eb(nxtb2);
                }
                if (nxta2.size()) {
                    vaok.eb(nxta2), vbok.eb(nxtb1);
                }
            } else {
                ng[k] = 1;
                break;
            }
        }
        if (not ng[k]) {
            va = vaok, vb = vbok;
        }
    }

    ll ans = 0;
    rep(k, M) {
        if (not ng[k]) {
            ans += 1LL<<k;
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
