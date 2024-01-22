/*
・自力ならず。
・毒入りワイン問題、インタラクティブ、ビットで考える
・N個のジュースをそれぞれビット列にエンコードすると、
　各ビットの状態をどの人に飲ませるかに見立てることができる。
　なんか有名問題らしくて知らなかったんだけど、
　それにしても分かってみればビットとか競プロっぽい考察だし、
　自力でちゃんと導けるべきだったよなぁこれは…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

void solve() {
    ll N;
    cin >> N;
    ll M = bit_length(N - 1);
    cout << M << endl;

    vvl A(M);
    rep(i, N) {
        rep(j, M) {
            if (i >> j & 1) {
                A[j].eb(i);
            }
        }
    }
    rep(i, M) {
        ll K = A[i].size();
        cout << K << ' ';
        A[i]++;
        cout << A[i] << endl;
        A[i]--;
    }

    string S;
    cin >> S;
    ll res = 0;
    rep(i, M) {
        if (S[i] == '1') {
            res |= 1LL << i;
        }
    }
    res++;
    cout << res << endl;
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
