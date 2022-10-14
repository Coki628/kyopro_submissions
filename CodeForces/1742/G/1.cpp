/*
・自力AC！
・最初orじゃなくてxorで考えててタイムロス…。問題よく見よう。。
　ソートして一番でかいの取って使用済ビットを潰した数列で繰り返す、ってやった。
　毎回愚直に全部ソートだけど、1ビット以上必ず減ると思うと、30回くらいしかやらないので大丈夫。
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
    ll N;
    cin >> N;
    auto A = LIST(N);

    vector<pll> B;
    rep(i, N) {
        B.eb(A[i], i);
    }
    vector<ll> ans;
    ll L = 30;
    rep(_, L) {
        sort(ALL(B));
        auto [b, i] = B.back();
        ans.eb(A[i]);
        B.pop_back();
        rep(j, B.size()) {
            rep(k, L) {
                if ((b>>k & 1) && (B[j].first>>k & 1)) {
                    B[j].first ^= 1LL<<k;
                }
            }
        }
        if (B.empty()) break;
    }
    for (auto [b, i] : B) {
        ans.eb(A[i]);
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
