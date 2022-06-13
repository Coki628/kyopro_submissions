/*
・自力AC！PASTボス問自力は嬉しい。
・数え上げ、主客転倒、FFT
・とりあえずお決まりの主客転倒で考える。何を決めるか考えると、
　Sを決めてA[j]-A[i]=j-iとなる通り数を数えると良さそう。
　条件を満たすあるi,jペアが、N!通りのうち何回使われるか数える感じ。
　indexのj-iはi,jの相対位置が決まるので、この2点をずらせる範囲としては
　S[k]を求める時、N-k通りになる。これでi,jの位置は決まった。
　他の要素についてはどう並べてもいいので、(N-2)!通りになる。
　これで全要素の位置が決まった。あとはここにS[k]とペアの通り数を掛ければいい。
　ペアの通り数は愚直にやるとN^2かかるけど、片方下駄を履かせてやるとFFTに乗る。
・なんか最初重複が出る気がして階乗で割ったりしたんだけど余計だった。。
　それ消したら無事AC。早めに察せたから良かったけど、正確にできるようになりたいね…。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

#include "math/FormalPowerSeries.hpp"

void solve() {
    ll N;
    cin >> N;
    const ll M = 100000;
    auto B = LIST(N);
    auto S = LIST<mint>(N);
    S.insert(S.begin(), 0);
    ModTools<mint> mt(M);

    ll offset = M;
    FPS<mint> F1(M+1), F2(M+1);
    rep(i, N) {
        F1[B[i]]++;
        F2[offset-B[i]]++;
    }
    auto res = F1 * F2;
    // map<ll, ll> C;
    // rep(i, N) {
    //     rep(j, N) {
    //         C[B[j]-B[i]]++;
    //     }
    // }
    mint ans = 0;
    // for (auto [k, v] : C) {
    //     if (1 <= k and k <= N) {
    //         ans += S[k] * mt.fact(N-2) * (N-k) * v;
    //     }
    // }
    rep(k, 1, N+1) {
        mint v = res[k+offset];
        ans += S[k] * mt.fact(N-2) * (N-k) * v;
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
