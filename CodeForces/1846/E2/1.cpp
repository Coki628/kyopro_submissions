/*
・なんとか自力AC！
・全列挙、にぶたん
・今度は全列挙できない。どうするか。
　とりあえずk<=10^6はE1と同様に列挙できる。
　Nが大きくなっても、各値で増える回数はせいぜい1～2回くらいだと思う。
　残りのkが大きいやつを考えてみる。
　題意より、使うのは実質第3項からだが、何しろ値が大きくなるのが早い。
　10^6でも第4項はk^3が入ってくるので、ここでNの最大10^18を超えてくる。
　つまり、k>10^6の範囲は、第3項だけチェックすればいいことになる。
　項数が決まっているなら、にぶたんで単調性が使えるので、
　ぴったり当たるものがあるかも判定できる。
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

ll M = 1000000;
ll MX = 1e18;
set<ll> exists;
void prep() {
    rep(k, 2, M + 1) {
        ll cur = 1, kk = 1, i = 0;
        while (not mul_overflow(kk, k) and cur + kk * k <= MX) {
            kk *= k;
            cur += kk;
            if (i >= 1) {
                exists.insert(cur);
            }
            i++;
        }
    }
}

void solve() {
    ll N;
    cin >> N;

    if (exists.count(N)) {
        YES();
        return;
    }
    if (N > M) {
        ld x = bisearch_min(0, INF, [&](ld x) {
            return x * x + x + 1 >= N;
        });
        if (x * x + x + 1 == N) {
            YES();
            return;
        }
    }
    NO();
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    prep();

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
