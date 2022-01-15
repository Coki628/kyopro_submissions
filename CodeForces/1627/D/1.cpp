/*
・なんとか自力AC！嘘解法っぽいんだけどね。。
・添字GCD畳み込み
・使える値の候補は増えていって、その時ありうるペアGCDで作れる数はさらに増やせる。
　とはいえ、そう何10回もGCDしないと出てこない数とかなさそう、となる。
・で、雑に「GCD畳み込み20回くらいやって1回でも現れたやつ - N」ってやったら通った。。
　llがオーバーフローしてる可能性に気付いてmintに切り替えるのがもっと早いと良かったね。
・終わってからちょっと改修。新しい値が増えなかった所でbreakするようにした。
　これだと0.23秒とかで余裕でACする。10回で試した時より全然速いので、
　やっぱり回数はかなり少なくてよかったんだろうと思う。
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

#include"../../../_lib/cpp/_src/numbers/gcd_convolution.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    ll M = max(A);
    vector<mint> C(M+1);
    rep(i, N) {
        C[A[i]]++;
    }
    auto has = C;
    bool updated = true;
    while (updated) {
        updated = false;
        C = gcd_convolution(C, C);
        rep(i, M+1) {
            if (C[i] != 0 and has[i] == 0) {
                has[i] = 1;
                updated = true;
            }
        }
    }
    ll cnt = 0;
    rep(i, M+1) {
        if (has[i] == 1) {
            cnt++;
        }
    }
    ll ans = cnt-N;
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
